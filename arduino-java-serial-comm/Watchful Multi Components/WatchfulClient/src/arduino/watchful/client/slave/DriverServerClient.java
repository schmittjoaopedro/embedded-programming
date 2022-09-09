
package arduino.watchful.client.slave;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;


public class DriverServerClient extends Thread {
    
    private Socket connection;
    
    public DriverServerClient(String address, int port) {
        try {
            
            this.connection = new Socket(address, port);
            
        } catch (IOException ex) {
            System.out.println("Error");
        }
    }
    
    
    @Override
    public void run()
    {
        try {
            BufferedReader input = 
                new BufferedReader(new InputStreamReader(this.connection.getInputStream()));
            PrintStream output = new PrintStream(this.connection.getOutputStream());
            int nickname = (int) (Math.random() * 1000);
            output.println(nickname);
            String msg;
            while (true)
            {
                msg = input.readLine();
                if (msg == null) {
                    System.out.println("Conexão encerrada!");
                    System.exit(0);
                }
                System.out.println(msg);
            }
        } catch (IOException e) {
            System.out.println("Ocorreu uma Falha... .. ." + 
                " IOException: " + e);
        }
    }
    
}
