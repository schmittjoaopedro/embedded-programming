package com.embedded;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONObject;

import com.embedded.packet.Header;
import com.embedded.socket.SynchronizerSocket;

public class Dashboard {
	
	private String name;
	
	private Map<String, Component> componentes;
	
	public Dashboard(String name) {
		this.setName(name);
	}
	
	public void process(JSONObject data) {
		System.out.println(data);
	}
	
	public void send(String component, String message) {
		try {
			JSONObject dataToSend = new JSONObject();
			dataToSend.put("login", Header.getUserName());
			dataToSend.put("dashboard", this.getName());
			dataToSend.put("component", component);
			dataToSend.put("message", message);
			SynchronizerSocket.getSocket().emit("cloud_data", dataToSend);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public Map<String, Component> getComponentes() {
		if(this.componentes == null) this.setComponentes(new HashMap<String, Component>());;
		return componentes;
	}
	public void setComponentes(Map<String, Component> componentes) {
		this.componentes = componentes;
	}
	
}
