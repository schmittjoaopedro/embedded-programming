package arduino.watchful.core;

/**
 *
 * @author João Pedro Schmitt
 */
public class Servo extends EletricalComponent {

    @Override
    public String definition() throws DefinitionException {
        if(this.getPin() >= 0 && this.getCommand() != null) {
            StringBuilder definition = new StringBuilder();
            definition.append("S-").append(this.getPin()).append(":").append(this.getCommand()).append(",");
            return definition.toString();
        }
        else 
            throw new DefinitionException("Eletricat component " + this.getPin() + " - " + this.getCommand() + " Servo Not initialized");
    }

    @Override
    public String execute() {
        StringBuilder execute = new StringBuilder();
        execute.append("S-").append(this.getPin()).append(":").append(this.getValue()).append(",");
        return execute.toString();
    }

    @Override
    public void analiser(String data) { 
        this.setIsReading(true);
        this.setReading(data);
    }

}
