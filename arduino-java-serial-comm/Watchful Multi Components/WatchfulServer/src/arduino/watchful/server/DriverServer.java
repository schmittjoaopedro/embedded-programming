

package arduino.watchful.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.Vector;

/**
 *
 * @author João Pedro Schmitt
 * @version 1.0.0 
 */
public class DriverServer extends Thread {

    private static Vector clients;
    private final Socket connection;
    private String clientname;
    private static final List clientsIdentification = new ArrayList();
    private static ILoggable loggeable;

    public DriverServer(Socket socket, ILoggable loggables) {
        if(DriverServer.loggeable == null) DriverServer.loggeable = loggables;
        if (DriverServer.clients == null) {
            DriverServer.clients = new Vector();
        }
        this.connection = socket;
    }

    public boolean addClient(String newName) {
        for (int i = 0; i < DriverServer.clientsIdentification.size(); i++) {
            if (DriverServer.clientsIdentification.get(i).equals(newName)) {
                return true;
            }
        }
        DriverServer.clientsIdentification.add(newName);
        return false;
    }

    public void removeClient(String oldName) {
        for (int i = 0; i < DriverServer.clientsIdentification.size(); i++) {
            if (DriverServer.clientsIdentification.get(i).equals(oldName)) {
                DriverServer.clientsIdentification.remove(oldName);
            }
        }
    }

    public void sendToAll(PrintStream output, String msg) throws IOException {
        Enumeration e = DriverServer.clients.elements();
        while (e.hasMoreElements()) {
            PrintStream chat = (PrintStream) e.nextElement();
            if (chat != output) {
                chat.println(this.clientname + "//" + msg);
                logger(this.clientname + "//" + msg);
            }
        }
    }

    @Override
    public void run() {
        try {
            BufferedReader input
                    = new BufferedReader(new InputStreamReader(this.connection.getInputStream()));

            PrintStream output = new PrintStream(this.connection.getOutputStream());
            this.clientname = input.readLine();

            if (addClient(this.clientname)) {
                output.println("This client is already connected! Try again with another name!");
                logger("This client is already connected! Try again with another name!");
                DriverServer.clients.add(output);
                this.connection.close();
                return;
            } else {
                System.out.println(this.clientname + " : is connected to server!");
                logger(this.clientname + " : is connected to server!");
                loggerClient(this.clientname);
            }
            if (this.clientname == null) {
                return;
            }
            DriverServer.clients.add(output);
            String msg = input.readLine();
            while (msg != null && !(msg.trim().equals(""))) {
                sendToAll(output, msg);
                msg = input.readLine();
            }
            removeClient(this.clientname);
            DriverServer.clients.remove(output);
            this.connection.close();
        } catch (IOException e) {
            logger("Connection failed.. .. ." + " IOException: " + e);
        }
    }

    private void logger(String msg) {
        DriverServer.loggeable.write(msg);
    }
    
    private void loggerClient(String msg) {
        DriverServer.loggeable.clients(msg);
    }
    

}
