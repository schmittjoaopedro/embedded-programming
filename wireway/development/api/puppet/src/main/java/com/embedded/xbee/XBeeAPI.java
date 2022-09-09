package com.embedded.xbee;

import java.util.HashMap;
import java.util.Map;

import com.digi.xbee.api.RemoteXBeeDevice;
import com.digi.xbee.api.XBeeDevice;
import com.digi.xbee.api.exceptions.XBeeException;
import com.digi.xbee.api.models.XBee64BitAddress;

/**
 * 
 * This abstract class implement a sample interface to receive and communicate with XBee
 * 
 * @author joao
 *
 */
public abstract class XBeeAPI {
	
	private Map<String, RemoteXBeeDevice> xbeeActuatorsAddress;
	 
	
	public XBeeAPI () {
		this.xbeeActuatorsAddress = new HashMap<String, RemoteXBeeDevice>();
	}
	
	
	/**
	 * Return the last line read from the serial
	 * 
	 * @return data
	 */
	public abstract String getLastLine() throws XBeeException;
	
	/**
	 * Write a string data to send to a XBee broadcast
	 * 
	 * @param data
	 */
	public abstract void write(String data) throws XBeeException;
	
	/**
	 * Start serial configuration by configuration
	 * 
	 * @param port
	 * @param baudRate
	 */
	public abstract void open(final String port, final Integer baudRate) throws XBeeException;
	
	/**
	 * 
	 * Attach a listener to receive data that has bee read from serial
	 * 
	 * @param xBeeEventListener
	 */
	public abstract void onReceiveData(XBeeEventListener xBeeEventListener);
	
	/**
	 * Attach a status listener
	 * 
	 * @param xBeeEventListener
	 */
	public abstract void onReceivePacket(XBeePacketListener xBeeEventListener);
	
	/**
	 * 
	 * Close the XBee communication
	 * 
	 */
	public abstract void close() throws XBeeException;
	
	/**
	 * Return raw class that has be implemented
	 * 
	 * @return
	 */
	public abstract XBeeDevice getRawImplementer();

	/**
	 * Add new actuators listeners
	 * 
	 * @param compName
	 * @param macAddress
	 */
	public void addActuator(String compName, String macAddress) {
		this.xbeeActuatorsAddress.put(compName, new RemoteXBeeDevice(this.getRawImplementer(), new XBee64BitAddress(macAddress)));
	}
	
	/**
	 * Send actuator data
	 * 
	 * @param actuator
	 * @param data
	 * @throws Exception
	 */
	public void sendActuatorData(String actuator, String data) throws Exception {
		if(this.xbeeActuatorsAddress.get(actuator) != null)
		this.getRawImplementer().sendData(this.xbeeActuatorsAddress.get(actuator), data.getBytes());
	}

}
