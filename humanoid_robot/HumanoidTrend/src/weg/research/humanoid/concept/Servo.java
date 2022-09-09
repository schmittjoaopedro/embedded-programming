package weg.research.humanoid.concept;

public class Servo {

    private Integer pin;
    private Integer angulation;
    private final String name;
    
    public Servo(String name){
        this.name = name;
    }
    
    public Integer getPin() {
        return pin;
    }

    public void setPin(Integer pin) {
        this.pin = pin;
    }

    public Integer getAngulation() {
        return angulation;
    }

    public void setAngulation(Integer angulation) {
        this.angulation = angulation;
        System.out.println(name + " in: \t\t\t\t" + this.angulation);
    }

}