/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package arduino.watchful.communicate;

import gnu.io.CommPortIdentifier;
import java.util.ArrayList;
import java.util.Enumeration;

public class SerialFactoryUtil {

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static String[] listAvailablesCOM() throws SerialPortException{
            
		ArrayList<String> ports = new ArrayList();
		Enumeration<CommPortIdentifier> allPorts = null;
		try {
			allPorts = CommPortIdentifier.getPortIdentifiers();
		}catch(Exception er){
			throw new SerialPortException(er);
		}
		while (allPorts.hasMoreElements()) {
			CommPortIdentifier currentPortId = (CommPortIdentifier) allPorts
					.nextElement();
			ports.add(currentPortId.getName());
		}
		
		String port[] = new String[ports.size()];
		for(int i = 0; i < ports.size(); i++){
			port[i] = ports.get(i);
		}
		
		return port;
	}
	
}