
package arduino.watchful.communicate;

public class SerialPortException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public SerialPortException(String message) {  
        super(message);  
    }  
	
	public SerialPortException(Exception ex) {  
        super(ex);  
    }
	
}