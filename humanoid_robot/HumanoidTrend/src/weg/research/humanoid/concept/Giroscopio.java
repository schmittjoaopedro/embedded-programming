package weg.research.humanoid.concept;

public class Giroscopio implements ISensors {

    private final TripleAxys tripleAxys;
    
    public Giroscopio(){
        this.tripleAxys = new TripleAxys();
    }
    
    @Override
    public Object read() {
        this.tripleAxys.setX(50);
        this.tripleAxys.setY(90);
        this.tripleAxys.setZ(20);
        return this.tripleAxys;
    }
    
    public TripleAxys getTripleAxys(){
        return this.tripleAxys;
    }
    
}
