package com.embedded.xbee;

/**
 * 
 * @author joao
 * 
 * This class has be implemented by the listeners for serial
 * communication with the embedded.
 *
 */
public interface XBeeEventListener {
	
	/**
	 * This method is call when a data is received in the Serial
	 * sending a data string and a generic packet
	 * 
	 * @param data
	 */
	public void onData(String data, Object packet);

}
