package arduino.watchful.service;

import arduino.watchful.core.EletricalComponent;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public abstract class ComponentPanel {

    private static List<Integer> pinsAddicted = new ArrayList();
    JButton data;
    JTextField pin;
    JComboBox method;
    JTextArea read;
    EletricalComponent eletronic;
    boolean isDefined = false;
    
    public ComponentPanel(JTextField pin, JComboBox method, JTextArea read, JButton data, EletricalComponent eletronic) {
        this.setData(data);
        this.setMethod(method);
        this.setPin(pin);
        this.setRead(read);
        this.setEletronic(eletronic);
        
    };
    
    public abstract void refresh();
    

    public JTextField getPin() {
        return pin;
    }

    public final void setPin(JTextField pin) {
        this.pin = pin;
    }

    public JComboBox getMethod() {
        return method;
    }

    public final void setMethod(JComboBox method) {
        this.method = method;
    }

    public JTextArea getRead() {
        return read;
    }

    public final void setRead(JTextArea read) {
        this.read = read;
        this.read.setAutoscrolls(false);
    }

    public final JButton getData() {
        return data;
    }

    public final void setData(JButton data) {
        this.data = data;
    }

    public EletricalComponent getEletronic() {
        return eletronic;
    }

    public final void setEletronic(EletricalComponent eletronic) {
        this.eletronic = eletronic;
    }
    
    protected void defineEletronic(int pin, String method) {
        if(!this.contains(pin)) {
            this.getEletronic().setPin(pin);
            this.getEletronic().setCommand(method);
            this.defined();
            this.addPin(pin);
        }else{
            throw new IllegalStateException("Value exist");
        }
    }
    
    protected boolean contains(Integer pin) {
        return ComponentPanel.pinsAddicted.contains(pin);
    }
    
    protected void addPin(int pin) {
        ComponentPanel.pinsAddicted.add(pin);
    }
    
    public boolean isDefined() { return this.isDefined; }
    
    public void defined() { this.isDefined = true; }
    
}
