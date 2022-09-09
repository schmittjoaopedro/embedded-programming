
package arduino.watchful.service;

import arduino.watchful.communicate.SerialPortException;
import arduino.watchful.core.ControllerManager;
import arduino.watchful.core.EletricalComponent;
import java.util.ArrayList;

/**
 *
 * @author João Pedro Schmitt
 */
public class WireComponents extends ControllerManager {
    
    
    public WireComponents(String address, int port) throws SerialPortException{
        super.connection(address, port);
        this.setManualExecutionPattern(new ArrayList());
    }
    
    public void wireComponentToController(EletricalComponent component){
        this.addControlled(component);
    }
    
}
