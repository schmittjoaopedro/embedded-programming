package weg.research.humanoid.concept;

public abstract class AbstractMovement implements IMovement {
    
    private final ISensors giroscopio;
    private final ISensors acelerometer;

    public AbstractMovement() {
        this.giroscopio = new Giroscopio();
        this.acelerometer = new Acelerometer();
    }
    
    protected boolean isBalance() {
        
        TripleAxys giro = (TripleAxys) this.giroscopio.read();
        TripleAxys acel = (TripleAxys) this.acelerometer.read();
        
        return -100 < giro.getX() && giro.getX() < 100
                && -100 < giro.getY() && giro.getY() < 100
                && -100 < giro.getZ() && giro.getZ() < 100
                && -100 < acel.getX() && acel.getX() < 100
                && -100 < acel.getY() && acel.getY() < 100
                && -100 < acel.getZ() && acel.getZ() < 100;
    };
    
    
    protected abstract void doBalance();
    protected abstract void fast();
    protected abstract void slow();
    protected abstract void increasingCurve();

    public TripleAxys getGiroscopio() {
        return (TripleAxys) giroscopio.read();
    }

    public TripleAxys getAcelerometer() {
        return (TripleAxys) acelerometer.read();
    }
}
