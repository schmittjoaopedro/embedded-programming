package com.embedded.socket;

import java.net.URISyntaxException;

import com.embedded.Run;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

public final class SynchronizerSocket {

	private static Socket socket;
	
	public static Socket getSocket() {
		if(SynchronizerSocket.socket == null) {
			try {
				IO.Options opts = new IO.Options();
				SynchronizerSocket.socket = IO.socket(Run.server, opts);
			} catch (URISyntaxException e) {
				e.printStackTrace();
			}
		}
		return SynchronizerSocket.socket;
	}
	
}
