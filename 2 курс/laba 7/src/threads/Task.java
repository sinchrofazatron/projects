package threads;
import functions.*;

public class Task {
    private Function f;
    private double leftX, rightX, step;
    private int n;

    public Task(int n){
       this.n = n;
    }

    public synchronized int getTask(){
        return n;
    }

    public synchronized Function getFunction(){
        return f;
    }

    public synchronized void setFunction(Function f){
        this.f = f;
    }

    public int getN(){
        return n;
    }

    public synchronized double getLeftX(){
        return leftX;
    }

    public synchronized void setLeftX(double leftX){
        this.leftX = leftX;
    }

    public synchronized double getRightX(){
        return rightX;
    }

    public synchronized void setRightX(double rightX){
        this.rightX = rightX;
    }

    public synchronized double getStep(){
        return step;
    }

    public synchronized void setStep(double step){
        this.step = step;
    } 
}
