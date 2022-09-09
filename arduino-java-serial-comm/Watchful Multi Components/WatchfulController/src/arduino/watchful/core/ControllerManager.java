package arduino.watchful.core;

import arduino.watchful.communicate.SerialPortException;
import arduino.watchful.communicate.SerialSession;
import arduino.watchful.communicate.ServerMasterController;
import java.util.ArrayList;
import java.util.List;

/**
 * 
 * @author João Pedro Schmitt
 */
public class ControllerManager extends AbstractController {

    private static final String PARAMETER_DIVISION = ",";
    private boolean isRecordable = false;
    private List<String> manualExecutionPattern;
    private String manualDefinitionPattern;
    private ArrayList controlleds = new ArrayList();
    private SerialSession session;
    
    private String translateData(String data) {
        StringBuilder result = new StringBuilder(data);
        return result.append(PARAMETER_DIVISION).toString();
    }
    
    @Override
    public void define() throws DefinitionException, SerialPortException {
        StringBuilder definitions = new StringBuilder();
        for(Object c : this.controlleds) {
            IControlled ctrl = (IControlled) c;
            definitions.append(ctrl.definition());
        }
        manualDefinitionPattern = definitions.toString();
        this.getSession().write(definitions.toString());
    }

    @Override
    public void execute() throws DefinitionException, SerialPortException {
        StringBuilder definitions = new StringBuilder();
        for(Object c : this.controlleds) {
            IControlled ctrl = (IControlled) c;
            definitions.append(ctrl.execute());
        }
        this.getSession().write(definitions.toString());
        if(this.getManualExecutionPattern() != null && this.isRecordable()) {
            this.getManualExecutionPattern().add(definitions.toString());
        }
        try {
            Thread.sleep(500);
        }catch(InterruptedException er){
            System.out.println(er.getMessage());
        }
    }
    

    @Override
    public void analiser() throws DefinitionException, SerialPortException {
        try {
            for(Object c : this.controlleds) {
            IControlled ctrl = (IControlled) c;
            ctrl.analiser(this.getSession().readMsg());
        }
        }catch(SerialPortException er){
            System.out.println(er.getMessage());
        }
    }
    
    @Override
    public List controlleds() {
        return this.controlleds;
    }
   
    @Override
    public void addControlled(IControlled controlled) {
        boolean notExist = true;
        for(Object c : this.controlleds) {
            IControlled ctrl = (IControlled) c;
            if(controlled.equals(ctrl))
                notExist = false;
        }
        if(notExist) {
            this.controlleds.add(controlled);
        }
    }

    @Override
    public void connection(String address, int port) throws SerialPortException{
        this.session = new ServerMasterController(address, port);
        this.session.open();
    }

    public SerialSession getSession() {
        return session;
    }

    public List<String> getManualExecutionPattern() {
        return manualExecutionPattern;
    }

    public void setManualExecutionPattern(List<String> manualExecutionPattern) {
        this.manualExecutionPattern = manualExecutionPattern;
    }

    public String getManualDefinitionPattern() {
        return manualDefinitionPattern;
    }

    public void setManualDefinitionPattern(String manualDefinitionPattern) {
        this.manualDefinitionPattern = manualDefinitionPattern;
    }
    
    public ArrayList getControlleds() {
        return controlleds;
    }

    public void setControlleds(ArrayList controlleds) {
        this.controlleds = controlleds;
    }
    
    public boolean isRecordable() {
        return this.isRecordable;
    }
    
    public void setRecordable(boolean stat) {
        this.isRecordable = stat;
    }
    
}
