/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package arduino.watchful.service;

import arduino.watchful.core.Analog;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 *
 * @author joao.schmitt
 */
public class AnalogPanel extends ComponentPanel {

    private JTextField value;

    public AnalogPanel(JTextField pin, JComboBox method, JTextField value, JTextArea read, JButton data) {
        super(pin, method, read, data, new Analog());
        this.setValue(value);
        
        this.getMethod().removeAllItems();
        this.getMethod().addItem("READ");
        this.getMethod().addItem("WRITE");
        
        this.getData().setText("DEFINE");
        this.getData().addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    if(getData().getText().equals("DEFINE")) {

                        if(Integer.parseInt(getPin().getText().toString()) > 0) {
                            defineEletronic(Integer.parseInt(getPin().getText().toString()), getMethod().getSelectedItem().toString());
                        }

                        if(getMethod().getSelectedItem().toString().equals("READ")) {
                            getValue().setText("READ");
                            getEletronic().setValue("READ");
                            getValue().setEditable(false);
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
    }
    
    
    @Override
    public void refresh() {
        if(getMethod().getSelectedItem().toString().equals("READ") && isDefined == true){
            String data = this.getEletronic().getReading();
            String especificData[] = data.split(",");
            String result = "";
            for(int count = especificData.length - 1; count >= 0; count--) {
                if(especificData[count].contains("A-" + this.getEletronic().getPin() + ":")) {
                    int init = especificData[count].indexOf(":");
                    result += especificData[count].substring(init + 1) + "\n";
                }
            }
            this.getRead().setText(result);
        }
    }

    public final JTextField getValue() {
        return value;
    }

    public final void setValue(JTextField value) {
        this.value = value;
    }
    
}
