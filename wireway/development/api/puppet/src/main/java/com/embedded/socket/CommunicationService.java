package com.embedded.socket;

import org.json.JSONObject;

import com.embedded.Component;
import com.embedded.Context;
import com.embedded.packet.Packet;
import com.github.nkzawa.emitter.Emitter;

public final class CommunicationService {

	private static final CommunicationService COMMUNICATION_SERVICE = new CommunicationService();
	
	private CommunicationService() { }
	
	public static CommunicationService getInstance() {
		return CommunicationService.COMMUNICATION_SERVICE;
	}
	
	public synchronized void sendComponent(Component component) {
		try {
			SynchronizerSocket.getSocket().emit("cloud_data", Packet.newPacket(component));
		} catch (Exception ex) {
			ex.printStackTrace();
			SynchronizerSocket.getSocket().emit("cloud_data", Packet.newErroPacket(ex));
		}
	}
	
	public synchronized void notifySocketEvents(final Context context) {

		SynchronizerSocket.getSocket().off("cloud_data");
		SynchronizerSocket.getSocket().on("cloud_data", new Emitter.Listener() {
			@Override
			public synchronized void call(Object... args) {
				context.onReceiveSocket((JSONObject) args[0]);
			}
		});
		
	}
	
}
