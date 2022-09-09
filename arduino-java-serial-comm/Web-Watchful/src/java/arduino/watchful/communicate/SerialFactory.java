/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package arduino.watchful.communicate;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;

/*
 * 
 *	Desenvolvido por: João Pedro Schmitt 
 * 
 *  Este código contém a implementação da API que faz
 *  a comunicação com o Arduíno, porém pode-se usar
 *  esta API com qualquer dispositivo que se comunique
 *  serial
 *  
 */

public class SerialFactory implements SerialSession {

	/*
	 *  Variável objeto porta
	 */
	SerialPort port;
	
	/*
	 *  Variável que será lido pela Serial
	 */
	private String msg = "";

	/*
	 *  Variavel para tempo de vida da thread de leitura
	 */
	private final int TIME_ALIVE;

	/* 
	 * Nome da porta que escutará a comunicação
	 */
	private final String PORT_NAME;

	/*
	 * Serviço de Buffer para leitura da serial
	 */
	private BufferedReader input;
	
	/* 
	 * Serviço de Buffer para escrita na serial
	 */
	private OutputStream output;

	/* 
	 * Variável de time-out para espera da conexão
	 */
	private static final int TIME_OUT = 2000;
	
	/* 
	 * Variável que armazena o taxa de transmissão (normalmente 9600 bauds)
	 */
	private final int DATA_RATE;

	/* 
	 * Iniciação pelo construtor de variáveis chaves para comunicação
	 */
	public SerialFactory(String SERIAL_PORT, int DATA_RATE,
			int TIME_ALIVE_THREAD) {
		this.PORT_NAME = SERIAL_PORT;
		this.DATA_RATE = DATA_RATE;
		this.TIME_ALIVE = TIME_ALIVE_THREAD;
	}

	/* 
	 * Metodo para fechar a conexão atual
	 */
	@Override
	public synchronized void close() throws SerialPortException {
		if (port != null) {
			port.removeEventListener();
			port.close();
			try{
				input.close();
				output.close();
			}catch(IOException er){
				throw new SerialPortException("Error do close output and input");
			}
		}
	}
	
	
	/* 
	 * Método de abertura da conexão
	 */
	@SuppressWarnings("unchecked")
	@Override
	public void open() throws SerialPortException {

		/* 
		 * Busca todas portas disponíveis no computador
		 */
		CommPortIdentifier portId = null;
		Enumeration<CommPortIdentifier> portEnum = null;
		try {
			portEnum = CommPortIdentifier.getPortIdentifiers();
		} catch (Exception er) {
			throw new SerialPortException(er);
		}
		/* 
		 * Verifica se alguma porta corresponde a porta especificada como sendo do Arduíno
		 */
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currentPortId = (CommPortIdentifier) portEnum
					.nextElement();
			if (currentPortId.getName().equals(PORT_NAME)) {
				portId = currentPortId;
				break;
			}
		}
		/* 
		 * Se não houver nenhuma lança uma exceção aplicada a esta
		 * de porta não encontrada
		 */
		if (portId == null) {
			throw new SerialPortException("Could not find COM port");
		}
		/* 
		 * Tenta abrir a comunicação com a porta Serial
		 */
		try {
			// open serial port, and use class name for the appName.
			port = (SerialPort) portId
					.open(this.getClass().getName(), TIME_OUT);

			/* 
			 * Definições para porta (PARITY_NONE permite comunicação bidirecional)
			 */
			port.setSerialPortParams(DATA_RATE, SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

			/* 
			 * Inicia o objeto de leitura
			 */
			input = new BufferedReader(new InputStreamReader(
					port.getInputStream()));
			/* 
			 * Inicia o objeto de escrita
			 */
			output = port.getOutputStream();

			/* 
			 * Adiciona ao eventListener para escutar as leituras
			 */
			port.addEventListener(this);
			/* 
			 * Define que deve-se notificar quando ter dados a serem lidos
			 */
			port.notifyOnDataAvailable(true);
			
		} catch (Exception er) {
			throw new SerialPortException(er);
		}
		Thread t = new Thread() {
			public void run() {
				/*
				 * Define o tempo de vida da escuta para porta serial
				 */
				try {
					Thread.sleep(TIME_ALIVE);
				} catch (InterruptedException ie) {
					ie.printStackTrace();
				}
			}
		};
		/* 
		 * Inicia a thread de escuta
		 */
		t.start();
		System.out.println("Started");
	}

	/* 
	 * Método para enviar informações via serial
	 */
	@Override
	public synchronized void write(String msg) throws SerialPortException {
		try{
                        System.out.println(msg);
			//output.write(Integer.parseInt(msg));
			output.write(msg.getBytes());
			output.flush();
		}catch(Exception e){
			throw new SerialPortException(e);
		}
	}

	/* 
	 * Método para ler as mensagens recebidas
	 */
	@Override
	public String readMsg() throws SerialPortException {
		return this.msg;
	}

	/* 
	 * Evento de escuta da interface serial
	 */
	@Override
	public synchronized void serialEvent(SerialPortEvent oEvent) {
		/* 
		 * Se há dados disponíveis faz a leitura
		 */
		if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				this.msg += input.readLine();
			} catch (Exception er) {
				System.out.print(er.getMessage());
			}
		}
	}

}
