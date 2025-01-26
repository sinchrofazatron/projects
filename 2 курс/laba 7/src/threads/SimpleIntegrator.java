package threads;

import functions.Functions;

public class SimpleIntegrator implements Runnable{
    private Task t;
    public SimpleIntegrator(Task t){
        this.t = t;
    }

    @Override
    public synchronized void run(){
        for (int i = 0; i < t.getN(); i++){
            if(t.getFunction() != null){
                System.out.println("Result" + " " + t.getLeftX() + " " + t.getRightX() + " " + t.getStep() + " " + Functions.integral(t.getFunction(), t.getLeftX(), t.getRightX(), t.getStep()));
            }
		}	
    }   
}
