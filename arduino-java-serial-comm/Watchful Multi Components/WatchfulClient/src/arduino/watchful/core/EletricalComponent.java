package arduino.watchful.core;

/**
 *
 * @author João Pedro Schmitt
 */
public abstract class EletricalComponent implements IControlled {
    
    private int pin;
    private String command;
    private String value;
    private String reading;
    private boolean isReading;

    public int getPin() {
        return pin;
    }

    public void setPin(int pin) {
        this.pin = pin;
    }

    public String getCommand() {
        return command;
    }

    public void setCommand(String command) {
        this.command = command;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public String getReading() {
        return reading;
    }

    public void setReading(String reading) {
        this.reading = reading;
    }

    public boolean isIsReading() {
        return isReading;
    }

    public void setIsReading(boolean isReading) {
        this.isReading = isReading;
    }
    
}
