package com.embedded.xbee.digi;

import java.io.File;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;

import com.digi.xbee.api.XBeeDevice;
import com.digi.xbee.api.exceptions.XBeeException;
import com.digi.xbee.api.listeners.IDataReceiveListener;
import com.digi.xbee.api.listeners.IPacketReceiveListener;

import com.embedded.xbee.XBeeAPI;
import com.embedded.xbee.XBeeEventListener;
import com.embedded.xbee.XBeePacketListener;

public class XBeeDigi extends XBeeAPI {

	static {
		String path = "";
		try {
			path = new File(".").getCanonicalPath();
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		System.getProperty("java.library.path");
		path = path + "/native";
		System.setProperty("java.library.path", path);
		Field fieldSysPath;
		try {
			fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
			fieldSysPath.setAccessible(true);
			fieldSysPath.set(System.class.getClassLoader(), null);
		} catch (NoSuchFieldException | SecurityException
				| IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
		}
	}

	private XBeeDevice xbeeDevice;
	private final List<XBeeEventListener> dataListener = new ArrayList<XBeeEventListener>();
	private final List<XBeePacketListener> packetListener = new ArrayList<XBeePacketListener>();
	private IDataReceiveListener xBeeEventListener;
	private IPacketReceiveListener xBeePacketListener;

	public String getLastLine() throws XBeeException {
		return null;
	}

	public void write(String data) throws XBeeException {
	}

	public void open(final String port, final Integer baudRate) throws XBeeException {
		this.xbeeDevice = new XBeeDevice(port, baudRate);
		this.xBeeEventListener = new XBeeDataReceiveListener(this);
		this.xBeePacketListener = new XbeePacketListener(this);
		this.xbeeDevice.open();
		this.xbeeDevice.addPacketListener(xBeePacketListener);
		this.xbeeDevice.addDataListener(this.xBeeEventListener);
	}

	@Override
	public void onReceiveData(XBeeEventListener xBeeEventListener) {
		this.dataListener.add(xBeeEventListener);
	}

	@Override
	public void onReceivePacket(XBeePacketListener xBeeEventListener) {
		this.packetListener.add(xBeeEventListener);
	}

	@Override
	public void close() throws XBeeException {
		this.xbeeDevice.close();
	}

	@Override
	public XBeeDevice getRawImplementer() {
		return this.xbeeDevice;
	}

	public List<XBeeEventListener> getListeners() {
		return this.dataListener;
	}
	
	public List<XBeePacketListener> getModenListeners() {
		return this.packetListener;
	}

}
