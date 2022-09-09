package com.embedded;

import java.io.Console;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import org.apache.http.HttpEntity;
import org.apache.http.HttpHost;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.CredentialsProvider;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.BasicCookieStore;
import org.apache.http.impl.client.BasicCredentialsProvider;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HttpCoreContext;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.embedded.interpreter.ScriptInterpreter;
import com.embedded.packet.Header;
import com.embedded.packet.Packet;
import com.embedded.socket.CommunicationService;
import com.embedded.socket.SynchronizerSocket;
import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.engineio.client.Transport;
import com.github.nkzawa.socketio.client.Manager;

public class Run {

	private static Console console;
	private static Context context;
	private static Scanner scanner;
	private static String proxyAuthorization = null;
	private static ScriptInterpreter interpreterThread;
	private static BasicCookieStore cookieStore;
	private static CloseableHttpClient httpclient;
	private static RequestConfig config;
	private static CredentialsProvider credentialsProvider;
	private static HttpHost proxy;
	private static String proxyUser;
	private static String proxyPassword;
	private static String proxyServer;
	private static Integer proxyPort;
	private static Boolean useProxy = false;
	//public static String server = "http://localhost:3000";
	public static String server = "http://192.168.0.110:3000";

	public static void main(String... args) throws Exception {
		
		processParameters(args);
		
		if(useProxy) {
			
			System.setProperty("http.proxyHost", Run.proxyServer);
			System.setProperty("http.proxyPort", Run.proxyPort.toString());
			System.setProperty("https.proxyHost", Run.proxyServer);
			System.setProperty("https.proxyPort", Run.proxyPort.toString());
			System.setProperty("http.proxyUser", Run.proxyUser);
			System.setProperty("http.proxyPassword", Run.proxyPassword);
			
			credentialsProvider = new BasicCredentialsProvider();
			credentialsProvider.setCredentials(new AuthScope(Run.proxyServer, Run.proxyPort), new UsernamePasswordCredentials(Run.proxyUser, Run.proxyPassword));
			proxy = new HttpHost(Run.proxyServer, Run.proxyPort);
			config = RequestConfig.custom().setProxy(proxy).build();
			Run.cookieStore = new BasicCookieStore();
			Run.httpclient = HttpClients.custom().setDefaultCredentialsProvider(credentialsProvider).setDefaultCookieStore(cookieStore).build();
			
		} else {
			
			Run.cookieStore = new BasicCookieStore();
			Run.httpclient = HttpClients.custom().setDefaultCookieStore(cookieStore).build();
			
		}
		
		
		try {
			
			retrieveLoginData();
			prepareScriptListener();
			
		} finally {
			httpclient.close();
		}	
		
	}

	private static void prepareScriptListener() {
		SynchronizerSocket.getSocket().on("client setup", new Emitter.Listener() {
			@Override
			public void call(Object... data) {
				try {
					JSONObject jsonData = (JSONObject) data[0];
					if(context != null)
						context.getSeriais().entrySet().forEach(item -> {
							try {
								item.getValue().close();
							} catch (Exception e) {
								e.printStackTrace();
							}
						});
					prepareDataProcess(jsonData);
					String script = jsonData.getJSONObject("body").getJSONObject("script").getString("content");
					if(interpreterThread != null) {
						interpreterThread.stopScript();
					}
					interpreterThread = new ScriptInterpreter();
					interpreterThread.uploadScript(script, context);
					CommunicationService.getInstance().notifySocketEvents(context);
					interpreterThread.start();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		SynchronizerSocket.getSocket().emit("client setup", Packet.newPacketHeader());
	}

	private static void prepareDataProcess(JSONObject jsonData) throws JSONException {
		if(SynchronizerSocket.getSocket().connected()) {
			context = new Context();
			context.setDashboard(Header.getDashboardName());
			Dashboard dashboard = context.dashboard();
			JSONObject body = jsonData.getJSONObject("body");
			JSONArray components = body.getJSONArray("components"); 
			for(int i = 0; i < components.length(); i++) {
				Component component = new Component();
				component.setId(components.getJSONObject(i).getLong("id"));
				component.setIdName(components.getJSONObject(i).getString("idName"));
				component.setDataType(components.getJSONObject(i).getString("dataType"));
				component.setComponentType(components.getJSONObject(i).getString("componentType"));
				if(components.getJSONObject(i).has("value"))
					component.setRawValue(components.getJSONObject(i).get("value"));
				component.setDescription(components.getJSONObject(i).getString("description"));
				component.setSendWhenChange(components.getJSONObject(i).getBoolean("sendWhenChange"));
				dashboard.getComponentes().put(component.getIdName(), component);
			}
		}
	}

	private static void retrieveLoginData() throws Exception {
		Run.console = System.console();
		if (console != null) {
			Header.setUserName(Run.console.readLine("Login: "));
			Header.setUserPassword(new String(Run.console.readPassword("Password: ")));
		} else {
			Run.scanner = new Scanner(System.in);
			System.out.println("Login:");
			Header.setUserName(Run.scanner.nextLine());
			System.out.println("Passowrd:");
			Header.setUserPassword(Run.scanner.nextLine());
		}
		selectAvailableDashBoard();
		startSocketConnection();
	}
	
	private static void selectAvailableDashBoard() throws Exception {
		
		HttpPost httpPost = new HttpPost(Run.server + "/login");
		if(useProxy) httpPost.setConfig(config);
        List<NameValuePair> urlParameters = new ArrayList<NameValuePair>();
    	urlParameters.add(new BasicNameValuePair("username", Header.getUserName()));
    	urlParameters.add(new BasicNameValuePair("password", Header.getUserPassword()));
    	httpPost.setEntity(new UrlEncodedFormEntity(urlParameters));
        CloseableHttpResponse response1 = httpclient.execute(httpPost);
        if(response1.getFirstHeader("Location").getValue().equals("/")) {
        	System.out.println("Access denied!");
        	System.exit(1);
        }
        try {
            HttpEntity entity = response1.getEntity();
            EntityUtils.consume(entity);
        } finally {
            response1.close();
        }
        
        String availableDashboardsResponse = null;
        HttpGet httpGetHome = new HttpGet(Run.server + "/home/user/dashboards");
        if(useProxy) httpGetHome.setConfig(config);
        HttpResponse dashboardsResponse = httpclient.execute(httpGetHome);
        HttpEntity responseDashboardsEntity = dashboardsResponse.getEntity();
        if(responseDashboardsEntity != null) {
        	availableDashboardsResponse = EntityUtils.toString(responseDashboardsEntity);
        }
        JSONArray availablesDashboards = new JSONArray(availableDashboardsResponse);
        
        System.out.println("Availables: ");
        for(int i = 0; i < availablesDashboards.length(); i++) {
        	System.out.println(i + " = ( " + availablesDashboards.getJSONObject(i).get("name") + " )");
        }
        Integer selected = null;
        if (console != null) {
        	selected = Integer.valueOf(Run.console.readLine("Select one: "));
        } else {
        	System.out.println("Select one: ");
			selected = Run.scanner.nextInt();
        }
        if(selected != null && selected < availablesDashboards.length()) {
        	Header.setDashboardId(availablesDashboards.getJSONObject(selected).getLong("id"));
        	Header.setDashboardName(availablesDashboards.getJSONObject(selected).getString("name"));
        }
        
	}
	
	private static void startSocketConnection() throws Exception {
		
		Long startHandshakeDate = new Date().getTime();
		HttpCoreContext localContext = new HttpCoreContext();
        HttpGet httpGet = new HttpGet(Run.server + "/socket.io/?EIO=3&transport=polling&t=" + startHandshakeDate + "-0");
        CloseableHttpResponse response2 = null;
        if(useProxy) {
        	httpGet.setConfig(config);
        	response2 = httpclient.execute(httpGet, localContext); 
        	proxyAuthorization = localContext.getRequest().getFirstHeader("Proxy-Authorization").getValue();
        } else {
        	response2 = httpclient.execute(httpGet);
        }
        try {
            HttpEntity entity = response2.getEntity();
            EntityUtils.consume(entity);
        } finally {
        	response2.close();
        }
        
		SynchronizerSocket.getSocket().io().on(Manager.EVENT_TRANSPORT, new Emitter.Listener() {
            @Override
            public void call(Object... args) {
                Transport transport = (Transport)args[0];
                transport.on(Transport.EVENT_REQUEST_HEADERS, new Emitter.Listener() {
                    @Override
                    public void call(Object... args) {
                        @SuppressWarnings("unchecked")
                        Map<String, String> headers = (Map<String, String>) args[0];
                        headers.put("Cookie", "io=" + cookieStore.getCookies().get(1).getValue() + "; connect.sid=" + cookieStore.getCookies().get(0).getValue());
                        if(useProxy) {
	                        headers.put("Proxy-Authorization", proxyAuthorization);
	                        headers.put("Proxy-Connection", "Keep-Alive");
                        }
                    }
                });
            }
        });
		SynchronizerSocket.getSocket().open();
		
	}
	
	public static void processParameters(String[] params) {
		for(String param : params) {
			String name = param.split("=")[0];
			switch (name) {
				case "-Server":
					Run.server = param.split("=")[1];
					break;
				case "-ProxyServer":
					Run.proxyServer = param.split("=")[1];
					break;
				case "-ProxyPort":
					Run.proxyPort = Integer.valueOf(param.split("=")[1]);
					break;
				case "-ProxyUser":
					Run.proxyUser = param.split("=")[1];
					break;
				case "-ProxyPassword":
					Run.proxyPassword = param.split("=")[1];
					break;
				case "-Proxy":
					Run.useProxy = true;
					break;
				default:
					break;
			}
		}
	}

}
