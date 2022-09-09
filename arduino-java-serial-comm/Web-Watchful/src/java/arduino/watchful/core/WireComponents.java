/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package arduino.watchful.core;

import arduino.watchful.communicate.SerialPortException;

public class WireComponents extends ControllerManager {
    
    
    public WireComponents(String port) throws SerialPortException{
        super.connection(port);
    }
    
    public void wireComponentToController(EletricalComponent component){
        this.addControlled(component);
    }
    
}