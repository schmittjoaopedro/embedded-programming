package weg.research.humanoid.concept;

public class HumanoidEngine extends AbstractMovement {

    private final Servo footerRight;
    private final Servo footerLeft;
    private final Servo shinRight;
    private final Servo shinLeft;
    private final Servo thigRight;
    private final Servo thigLeft;
    
    
    public HumanoidEngine(){
        super();
        this.footerLeft = new Servo("Left Foot");
        this.footerRight = new Servo("Right Foot");
        this.shinLeft = new Servo("Left Shin");
        this.shinRight = new Servo("Right Shin");
        this.thigLeft = new Servo("Left Thig");
        this.thigRight = new Servo("Right Thig");
        
        this.footerLeft.setAngulation(90);
        this.footerRight.setAngulation(90);
        this.shinLeft.setAngulation(90);
        this.shinRight.setAngulation(90);
        this.thigLeft.setAngulation(90);
        this.thigRight.setAngulation(90);
    }
    
    
    @Override
    protected boolean isBalance() {
        return super.isBalance();
    }

    @Override
    protected void doBalance() {
        System.out.println("Balancing!!! waiting..... ");
        this.stop();
        this.getAcelerometer().setX(50).setY(50).setZ(50);
        this.getGiroscopio().setX(50).setY(50).setZ(50);
        System.out.println("Balanced");
    }

    @Override
    protected void fast() {
        System.out.println("Increasing speeding to 7.2V....");
    }

    @Override
    protected void slow() {
        System.out.println("Decreasing speeding to 5V....");
    }

    @Override
    protected void increasingCurve() {
        this.getGiroscopio().setX(250).setY(50).setZ(50);
        this.doBalance();
    }

    @Override
    public void walkAHead() {
        if(!this.isBalance()) this.doBalance();
        System.out.println("\nInit Walking ahead.... ");
        //1º step
        footerLeft.setAngulation(70);
        thigRight.setAngulation(140);
        shinRight.setAngulation(30);
        thigLeft.setAngulation(70);
        shinRight.setAngulation(90);
        footerRight.setAngulation(120);
        thigRight.setAngulation(90);
        thigLeft.setAngulation(90);
        footerRight.setAngulation(90);
        //2º step
        footerRight.setAngulation(70);
        thigLeft.setAngulation(140);
        shinLeft.setAngulation(30);
        thigRight.setAngulation(70);
        shinLeft.setAngulation(90);
        footerLeft.setAngulation(120);
        thigLeft.setAngulation(90);
        thigRight.setAngulation(90);
        footerLeft.setAngulation(90);
        System.out.println("End Walking ahead...");
    }

    @Override
    public void walkBehind() {
        if(!this.isBalance()) this.doBalance();
        System.out.println("\nInit Walking a behind....");
        //1º step
        footerLeft.setAngulation(140);
        thigRight.setAngulation(70);
        shinRight.setAngulation(150);
        thigLeft.setAngulation(140);
        shinRight.setAngulation(90);
        footerRight.setAngulation(60);
        thigRight.setAngulation(90);
        thigLeft.setAngulation(90);
        footerRight.setAngulation(90);
        //2º step
        footerRight.setAngulation(140);
        thigLeft.setAngulation(70);
        shinLeft.setAngulation(150);
        thigRight.setAngulation(120);
        shinLeft.setAngulation(90);
        footerLeft.setAngulation(70);
        thigLeft.setAngulation(90);
        thigRight.setAngulation(90);
        footerLeft.setAngulation(90);
        System.out.println("End Walking a behind....");
    }

    @Override
    public void turnRight() {
        if(!this.isBalance()) this.doBalance();
        System.out.println("\nInit Turning a right....");
        //1º step
        footerLeft.setAngulation(140);
        thigRight.setAngulation(70);
        shinRight.setAngulation(150);
        thigLeft.setAngulation(140);
        shinRight.setAngulation(90);
        footerRight.setAngulation(60);
        thigRight.setAngulation(90);
        thigLeft.setAngulation(90);
        footerRight.setAngulation(90);
        //2º step
        footerRight.setAngulation(40);
        thigLeft.setAngulation(120);
        shinLeft.setAngulation(30);
        thigRight.setAngulation(70);
        shinLeft.setAngulation(90);
        footerLeft.setAngulation(140);
        thigLeft.setAngulation(90);
        thigRight.setAngulation(90);
        footerLeft.setAngulation(90);
        System.out.println("End Turning a right....");
    }

    @Override
    public void turnLeft() {
        if(!this.isBalance()) this.doBalance();
        System.out.println("\nInit Turning a left....");
        //1º step
        footerLeft.setAngulation(70);
        thigRight.setAngulation(140);
        shinRight.setAngulation(30);
        thigLeft.setAngulation(60);
        shinRight.setAngulation(90);
        footerRight.setAngulation(130);
        thigRight.setAngulation(90);
        thigLeft.setAngulation(90);
        footerRight.setAngulation(90);
        //2º step
        footerRight.setAngulation(140);
        thigLeft.setAngulation(70);
        shinLeft.setAngulation(150);
        thigRight.setAngulation(120);
        shinLeft.setAngulation(90);
        footerLeft.setAngulation(70);
        thigLeft.setAngulation(90);
        thigRight.setAngulation(90);
        footerLeft.setAngulation(90);
        System.out.println("End Turning a left....");
        //Deve ser removido depois
        this.increasingCurve();
    }

    @Override
    public void stop() {
        if(!this.isBalance()) this.doBalance();
        System.out.println("\nInit stopping....");
        //1º step
        footerLeft.setAngulation(90);
        thigRight.setAngulation(90);
        shinRight.setAngulation(90);
        thigLeft.setAngulation(90);
        shinRight.setAngulation(90);
        footerRight.setAngulation(90);
        thigRight.setAngulation(90);
        thigLeft.setAngulation(90);
        footerRight.setAngulation(90);
        //2º step
        footerRight.setAngulation(90);
        thigLeft.setAngulation(90);
        shinLeft.setAngulation(90);
        thigRight.setAngulation(90);
        shinLeft.setAngulation(90);
        footerLeft.setAngulation(90);
        thigLeft.setAngulation(90);
        thigRight.setAngulation(90);
        footerLeft.setAngulation(90);
        System.out.println("End stopping....");
    }
    
}