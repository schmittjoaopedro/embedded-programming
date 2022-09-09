package arduino.watchful.core;

/**
 *
 * @author João Pedro Schmitt
 */
public interface IControlled {
 
    public String definition() throws DefinitionException;
    public String execute();
    public void analiser(String data);
    
}
