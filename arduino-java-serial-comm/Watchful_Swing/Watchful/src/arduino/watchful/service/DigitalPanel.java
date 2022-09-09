package arduino.watchful.service;

import arduino.watchful.core.Digital;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class DigitalPanel extends ComponentPanel {
    
    private JComboBox value;
    
    public DigitalPanel(JTextField pin, JComboBox method, JComboBox value, JTextArea read, JButton data) {
        super(pin, method, read, data, new Digital());
        this.setValue(value);
        
        this.getValue().removeAllItems();
        this.getMethod().removeAllItems();
        this.getMethod().addItem("INPUT");
        this.getMethod().addItem("OUTPUT");
        
        this.getData().setText("DEFINE");
        this.getData().addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    if(getData().getText().equals("DEFINE")) {

                        if(Integer.parseInt(getPin().getText().toString()) > 0) {
                            defineEletronic(Integer.parseInt(getPin().getText().toString()), getMethod().getSelectedItem().toString());
                        }

                        if(getMethod().getSelectedItem().toString().equals("INPUT")) {
                            getValue().addItem("READ");
                        }else {
                            getValue().addItem("HIGH");
                            getValue().addItem("LOW");
                        }
                        getPin().setEditable(false);
                        getMethod().setEnabled(false);
                        getData().setText("SEND");
                    }else{

                    }
                }catch(IllegalStateException er) {
                    JOptionPane.showMessageDialog(null, "Este pino já esta sendo usado!");
                }catch(NumberFormatException er) {
                    JOptionPane.showMessageDialog(null, "Não são aceitas letras");
                }
            }
        });
        
        this.getValue().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                getEletronic().setValue(getValue().getSelectedItem().toString());
            }
        });
    }
    
    
    @Override
    public void refresh() {
        if(getMethod().getSelectedItem().toString().equals("INPUT") && isDefined == true){
            String data = this.getEletronic().getReading();
            String especificData[] = data.split(",");
            String result = "";
            for(int count = especificData.length - 1; count >= 0; count--) {
                if(especificData[count].contains("D-" + this.getEletronic().getPin() + ":")) {
                    int init = especificData[count].indexOf(":");
                    result += especificData[count].substring(init + 1) + "\n";
                }
            }
            this.getRead().setText(result);
        }
    }
    

    public final JComboBox getValue() {
        return value;
    }

    public final void setValue(JComboBox value) {
        this.value = value;
    }

}
