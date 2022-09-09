
package arduino.watchful.server;

import java.util.List;



public interface ILoggable {
    
    public void write(String msg);
    public void clients(String client);
    
}
