package com.embedded.serial;

import jssc.SerialPortException;

/**
 * 
 * This class contains the basic methods used to communicate with a serial port
 * 
 * @author joao
 *
 */
public interface SerialAPI {

	/**
	 * Open connection, case the port is block or not found a SerialPortException occur
	 *  
	 * @return isSuccess
	 */
	public Boolean open() throws SerialPortException;
	
	/**
	 * Close connection, case the port cannot be closed, a exception occur
	 * 
	 * @return isSuccess
	 */
	public Boolean close() throws SerialPortException;
	
	/**
	 * Write a string data
	 * 
	 * @param data
	 * 
	 */
	public void write(String data) throws SerialPortException;
	
	/**
	 * Attach a simple listener that implement SerialListener to receive a copy
	 * of the data received from the serial
	 * 
	 * @param listener
	 * 
	 */
	public void attachListener(SerialListener listener);
	
	/**
	 * Remove a attached listener, return true if this was removed or false if 
	 * the list do not contains the listener
	 * 
	 * @param listener
	 * @return
	 */
	public Boolean removeListener(SerialListener listener);
	
	/**
	 * Return true if the listeners contais the listener
	 * 
	 * @param listener
	 * 
	 * @return contains
	 */
	public Boolean containsListener(SerialListener listener);
	
	/**
	 * Read the copy of the current buffer in serial
	 * 
	 * @return buffer
	 */
	public String readBuffer();
	
}
