
import arduino.watchful.client.slave.DriverServerClient;





public class TesteConcept {

    
    public static void main(String... args) {
        
        Thread thread = new DriverServerClient("127.0.0.1", 5000);
        thread.start();
    }
    
    
}
