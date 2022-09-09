package weg.research.humanoid.concept;

public class ThinkingAgent {

    private IMovement movement;
    
    
    public ThinkingAgent() {
        this.setMovement(new HumanoidEngine());
    }
    
    public void doMove(){
        try{
            this.getMovement().walkAHead();
            Thread.sleep(1000);
            this.getMovement().stop();
            Thread.sleep(1000);
            this.getMovement().walkBehind();
            Thread.sleep(1000);
            this.getMovement().turnLeft();
            Thread.sleep(1000);
            this.getMovement().turnRight();
            Thread.sleep(1000);
            
        }catch(InterruptedException e){
            System.out.println(e.getMessage());
        }
    }

    private IMovement getMovement() {
        return movement;
    }
    private void setMovement(IMovement movement) {
        this.movement = movement;
    }
}