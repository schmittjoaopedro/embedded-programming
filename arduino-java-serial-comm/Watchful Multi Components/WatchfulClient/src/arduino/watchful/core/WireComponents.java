package arduino.watchful.core;

import arduino.watchful.communicate.SerialPortException;
import java.util.ArrayList;




public class WireComponents extends ControllerManager {
    
    public WireComponents(String port) throws SerialPortException{
        super.connection(port);
        this.setManualExecutionPattern(new ArrayList());
    }
    
    public void wireComponentToController(EletricalComponent component){
        this.addControlled(component);
    }
    
}
