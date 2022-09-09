package com.embedded.xbee.digi;

import com.digi.xbee.api.listeners.IDataReceiveListener;
import com.digi.xbee.api.models.XBeeMessage;

/**
 * 
 * @author joao
 *
 *	This class implements a IDataReceiveListener that is responsible by 
 *  communicate with all external listeners
 */
public class XBeeDataReceiveListener implements IDataReceiveListener {

	/**
	 * A instance of the component that have communication with serial xbee 
	 */
	private XBeeDigi xbeeDigi;
	
	/**
	 * Constructor really need a instance of xbeeDigi
	 * 
	 * @param xBeeDigi
	 */
	public XBeeDataReceiveListener(XBeeDigi xBeeDigi) {
		super();
		this.xbeeDigi = xBeeDigi;
	}
	
	/**
	 * When receive data from xbeeDigi that has bee passed
	 */
	public void dataReceived(XBeeMessage xbeeMessage) {
		String data = xbeeMessage.getDataString();
		this.xbeeDigi.getListeners().forEach(item -> {
			item.onData(data, xbeeMessage);
		});
	}

}
