/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package arduino.watchful.service;

import arduino.watchful.core.Servo;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 *
 * @author Joao
 */
public class ServoPanel extends ComponentPanel {

    private JTextField value;
    
    public ServoPanel(JTextField pin, JTextField value, JTextArea read, JButton data){
        super(pin, null, read, data, new Servo());
        this.setValue(value);
        
        this.getData().setText("DEFINE");
        this.getData().addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    if(getData().getText().equals("DEFINE")) {
                        if(Integer.parseInt(getPin().getText().toString()) > 0) {
                            defineEletronic(Integer.parseInt(getPin().getText().toString()), getValue().getText().toString());
                        }
                        getPin().setEditable(false);
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
        
        this.getValue().addFocusListener(new FocusListener() {

            @Override
            public void focusGained(FocusEvent e) {
                
            }

            @Override
            public void focusLost(FocusEvent e) {
                int value = Integer.parseInt(getValue().getText().toString());
                if(value >= 0 && value <= 180)
                    getEletronic().setValue(getValue().getText().toString());
                else
                    JOptionPane.showMessageDialog(null, "Insira um valor entre 0 - 180");
            }
        });
        
    }
    
    
    @Override
    public void refresh() {
        if(isDefined == true){
            String data = this.getEletronic().getReading();
            String especificData[] = data.split(",");
            String result = "";
            for(int count = especificData.length - 1; count >= 0; count--) {
                if(especificData[count].contains("S-" + this.getEletronic().getPin() + ":")) {
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
