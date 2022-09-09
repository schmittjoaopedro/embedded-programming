package com.embedded.xbee.digi;

import com.digi.xbee.api.listeners.IPacketReceiveListener;
import com.digi.xbee.api.packet.XBeePacket;


/**
 * 
 * @author joao
 *
 *	This class implements a IModemStatusReceiveListener that is responsible by 
 *  communicate with all external listeners
 */
public class XbeePacketListener implements IPacketReceiveListener {

	
	/**
	 * A instance of the component that have communication with serial xbee 
	 */
	private XBeeDigi xbeeDigi;
	
	/**
	 * Constructor really need a instance of xbeeDigi
	 * 
	 * @param xBeeDigi
	 */
	public XbeePacketListener(XBeeDigi xBeeDigi) {
		super();
		this.xbeeDigi = xBeeDigi;
	}

	@Override
	public void packetReceived(XBeePacket receivedPacket) {
		this.xbeeDigi.getModenListeners().forEach(item -> {
			item.onPacket(receivedPacket);
		});
	}
	

}
