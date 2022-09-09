package com.embedded;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONObject;

import com.digi.xbee.api.exceptions.XBeeException;
import com.embedded.exception.DashboardNotExistException;
import com.embedded.exception.EmbeddedException;
import com.embedded.serial.SerialAPI;
import com.embedded.serial.SerialAPIProvider;
import com.embedded.utils.JSONUtils;
import com.embedded.xbee.XBeeAPI;
import com.embedded.xbee.XBeeAPIFactoryProvider;
import com.embedded.xbee.digi.XBeeDigi;

public class Context extends Scope {

	private Dashboard dashboard;
	private Map<String, SerialAPI> seriais;
	private Map<String, XBeeAPI> xbees; 
	
	/**
	 * 	METHODS USED BY USER IN API 
	 */
	
	/**
	 * Return dashboard instance, if the dashboard not exist then thrwo a runtime exception
	 * 
	 * @param name
	 * @return {@link Dashboard}
	 */
	public Dashboard dashboard() {
		if(this.dashboard == null) throw new DashboardNotExistException();
		return this.dashboard;
	}
	
	/**
	 * Stop thread for a defined type
	 * 
	 * @param delay
	 */
	public void delay(Long delay) {
		try {
			Thread.sleep(delay);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Create serial with BaudRate with 9600
	 * 
	 * @param port
	 * @return {@link Serial}
	 */
	public SerialAPI serial(String port) {
		return this.serial(port, 9600);
	}
	
	/**
	 * Create serial with custom BaudRate
	 * 
	 * @param port
	 * @return {@link Serial}
	 */
	public SerialAPI serial(String port, Integer baudRate) {
		if(this.getSeriais().get(port) == null) {
			this.getSeriais().put(port, new SerialAPIProvider(port, baudRate));
		}
		return this.getSeriais().get(port);
	}
	
	
	/**
	 * Create a xbee instance
	 * 
	 * @param port
	 * @return
	 * @throws XBeeException 
	 */
	public XBeeAPI xbee(String port) throws XBeeException {
		if(this.getXbees().get(port) == null) {
			this.getXbees().put(port, XBeeAPIFactoryProvider.getProvider(XBeeDigi.class));
			this.getXbees().get(port).open(port, 9600);
		}
		return this.getXbees().get(port);
	}
	
	
	/**
	 * 
	 * Return component by name
	 * 
	 * @param name
	 * @return component
	 */
	public synchronized Component getCmp(String name) {
		if(this.dashboard().getComponentes().get(name) == null) {
			throw new EmbeddedException("Component: " + name + " does not exist!");
		} else {
			return this.dashboard().getComponentes().get(name);
		}
	}
	
	/**
	 * Internal method, is called when socket received data from server
	 * @param object
	 */
	public synchronized void onReceiveSocket(JSONObject object) {
		JSONUtils.getComponents(object).forEach(item -> {
			try {
				this.getCmp(item.getString("idName")).setAndNotify(item.get("value"));
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		});
	}
	
	
	
	/**
	 * PRIVATE METHODS
	 */
	public void setDashboard(String name) {
		this.dashboard = new Dashboard(name);
	}
	public Map<String, SerialAPI> getSeriais() {
		if(this.seriais == null) this.seriais = new HashMap<String, SerialAPI>();
		return seriais;
	}
	public Map<String, XBeeAPI> getXbees() {
		if(this.xbees == null) this.xbees = new HashMap<String, XBeeAPI>();
		return this.xbees;
	}
	
}
