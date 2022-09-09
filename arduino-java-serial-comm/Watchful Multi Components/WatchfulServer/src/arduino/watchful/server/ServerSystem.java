
package arduino.watchful.server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;


/**
 * 
 * @author joao.schmitt
 * @version 1.0.0
 */
public class ServerSystem extends Thread {
    
    private Socket connection;
    private static int PORT;
    private List<ILoggable> loggables;
    
    public ServerSystem(int port) {
        ServerSystem.PORT = port;
        loggables = new ArrayList();
         try {
            ServerSocket server = new ServerSocket(PORT);
            System.out.println("ServidorSocket rodando na porta 5555");
            while (true) {
                connection = server.accept();
                //Thread t = new DriverServer(connection, );
                //t.start();
            }
        } catch (IOException e) {
            System.out.println("IOException: " + e);
        }
    }
    
    public List<ILoggable> getLoggables() {
        return loggables;
    }

    public void setLoggables(List<ILoggable> loggables) {
        this.loggables = loggables;
    }
    
}
