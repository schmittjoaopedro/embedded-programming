/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package arduino.watchful.service;

import arduino.watchful.core.PWM;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 *
 * @author joao.schmitt
 */
public class PWMPanel extends ComponentPanel {

    private JTextField value;
    
    public PWMPanel(JTextField pin, JComboBox method, JTextField value, JTextArea read, JButton data) {
        super(pin, method, read, data, new PWM());
        
        this.setValue(value);
        this.getMethod().removeAllItems();
        this.getMethod().addItem("WRITE");
        this.getMethod().addItem("READ");
        
        this.getData().setText("DEFINE");
        this.getData().addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    
                    if(getData().getText().equals("DEFINE")) {
                        if(Integer.parseInt(getPin().getText().toString()) > 0) {
                            defineEletronic(Integer.parseInt(getPin().getText().toString()), getMethod().getSelectedItem().toString());
                        }
                        if(getMethod().getSelectedItem().toString().equals("READ")) {
                            getValue().setText("READ");
                            getValue().setEditable(false);
                        }

                        getPin().setEditable(false);
                        getMethod().setEnabled(false);
                        getData().setText("SEND");
                    }else{ }
                    
                }catch(IllegalStateException er) {
                    JOptionPane.showMessageDialog(null, "Este pino já esta sendo usado!");
                }catch(NumberFormatException er) {
                    JOptionPane.showMessageDialog(null, "Não são aceitas letras");
                }
            }
        });
        
        
        this.getValue().addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) { }
            @Override
            public void focusLost(FocusEvent e) {
                int value = Integer.parseInt(getValue().getText().toString());
                if(value >= 0 && value <= 255)
                    getEletronic().setValue(getValue().getText().toString());
                else
                    JOptionPane.showMessageDialog(null, "Insira um valor entre 0 - 255");
            }
        });
        
    }
    
    
    @Override
    public void refresh() {
        if(getMethod().getSelectedItem().toString().equals("READ") && isDefined == true){
            this.getRead().setText("NOT IMPLEMENTED");
        }
    }

    public final JTextField getValue() {
        return value;
    }

    public final void setValue(JTextField value) {
        this.value = value;
    }
    
}
