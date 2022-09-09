package com.embedded.serial;

import java.util.ArrayList;
import java.util.List;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class SerialAPIProvider implements SerialAPI {


	private SerialPort serialPort;
	private String serialBuffer;
	private int baudRate = SerialPort.BAUDRATE_9600;
	private List<SerialListener> listeners = new ArrayList<SerialListener>();
	
	public SerialAPIProvider(String port) {
		super();
		this.serialPort = new SerialPort(port);
	}
	
	public SerialAPIProvider(String port, Integer baudRate) {
		super();
		this.serialPort = new SerialPort(port);
		this.baudRate = baudRate;
	}
	
	@Override
	public Boolean open() throws SerialPortException {
		
		try {
			this.serialPort.openPort();
			serialPort.setParams(
					this.baudRate,
					SerialPort.DATABITS_8, 
					SerialPort.STOPBITS_1, 
					SerialPort.PARITY_NONE);
			serialPort.setEventsMask(SerialPort.MASK_RXCHAR);
			
			serialPort.addEventListener(new SerialPortEventListener() {
				
				@Override
				public void serialEvent(SerialPortEvent e) {
					if(e.isRXCHAR()) {
						if(e.getEventValue() > 0) {
							try {
		                        String data = serialPort.readString();
		                        while(!data.contains("\n")) {
		                        	String temp = serialPort.readString();
		                        	if(temp != null) {
		                        		data += temp;
		                        	}
		                        }
		                        if(data != null && data.trim() != "")
		                        	data = data.replace("\n", "");
			        				for(SerialListener item : listeners) {
			        					item.onData(data);
			        				}
		                    }
		                    catch (SerialPortException ex) {
		                        ex.printStackTrace();
		                    }
						}
					}
				}
				
			});
			return true;
		} catch (Exception ex) {
			throw new RuntimeException(ex);
		}
	}

	@Override
	public Boolean close() throws SerialPortException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void write(String data) throws SerialPortException {
		this.serialPort.writeString(data);
	}

	@Override
	public void attachListener(SerialListener listener) {
		if(!this.containsListener(listener)) {
			this.listeners.add(listener);
		}
	}

	@Override
	public Boolean removeListener(SerialListener listener) {
		if(this.containsListener(listener)) {
			this.listeners.remove(listener);
			return true;
		} else {
			return false;
		}
	}

	@Override
	public Boolean containsListener(SerialListener listener) {
		return this.listeners.contains(listener);
	}

	@Override
	public String readBuffer() {
		return this.serialBuffer;
	}

}
