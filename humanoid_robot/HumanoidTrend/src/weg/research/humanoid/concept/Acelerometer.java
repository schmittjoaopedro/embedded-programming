package weg.research.humanoid.concept;

public class Acelerometer implements ISensors {

    private final TripleAxys tripleAxys;
    
    public Acelerometer(){
        this.tripleAxys = new TripleAxys();
    }
    
    @Override
    public Object read() {
        this.tripleAxys.setX(50);
        this.tripleAxys.setY(-10);
        this.tripleAxys.setZ(0);
        return tripleAxys;
    }
    
    public TripleAxys getTripleAxys(){
        return this.tripleAxys;
    }
    
}
