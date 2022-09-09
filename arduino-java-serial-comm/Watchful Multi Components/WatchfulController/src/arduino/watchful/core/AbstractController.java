package arduino.watchful.core;

import arduino.watchful.communicate.SerialPortException;
import java.util.List;

/**
 *
 * @author Joao Pedro Schmitt
 */
public abstract class AbstractController {
    
    public abstract void define() throws DefinitionException, SerialPortException;
    public abstract void connection(String address, int port) throws SerialPortException;
    public abstract void execute() throws DefinitionException, SerialPortException;
    public abstract void analiser() throws DefinitionException, SerialPortException;
    public abstract List controlleds();
    public abstract void addControlled(IControlled controlled);
    
}
