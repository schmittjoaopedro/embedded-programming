/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 *//*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package arduino.watchful.communicate;

import arduino.watchful.communicate.SerialPortException;
import arduino.watchful.communicate.SerialSession;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

/**
 *
 * @author joao.schmitt
 */
public class ServerMasterController extends Thread implements SerialSession {
    
    private Socket connection;
    private static String address;
    private static int port;
    private String message;
    private PrintStream output;
    private BufferedReader input;
    
    public ServerMasterController(String address, int port) {
        ServerMasterController.address = address;
        ServerMasterController.port = port;
    }

    @Override
    public void close() throws SerialPortException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void open() throws SerialPortException {
        try {
            this.connection = new Socket(ServerMasterController.address, ServerMasterController.port);
            this.input = new BufferedReader(new InputStreamReader(this.connection.getInputStream()));
            this.output = new PrintStream(this.connection.getOutputStream());
        }catch(Exception er) {
            System.out.println(er.getCause());
        }
    }

    @Override
    public void write(String msg) throws SerialPortException {
        System.out.println(msg);
        this.output.println(msg);
    }

    @Override
    public String readMsg() throws SerialPortException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    
    
    @Override
    public void run() {
        
        try {
            String msg;
            while (true)
            {
                msg = this.input.readLine();
                if (msg == null) {
                    System.out.println("Conexão encerrada!");
                    System.exit(0);
                }
                System.out.println();
                System.out.println(msg);
                System.out.print("Responder > ");
            }
        } catch(Exception er) {
            System.out.println(er.getMessage());
        }
    }
    
}
