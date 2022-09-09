package com.embedded.xbee;

import com.digi.xbee.api.packet.XBeePacket;


/**
 * 
 * @author joao
 * 
 * This class has be implemented by the listeners for serial
 * communication with the embedded.
 *
 */

public interface XBeePacketListener {

	/**
	 * Notify when receive a packet from any node
	 * 
	 * @param statusPacket
	 */
	void onPacket(XBeePacket packet);
	
}
