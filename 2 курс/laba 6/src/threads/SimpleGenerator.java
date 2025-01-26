package threads;

import functions.basic.Log;

public class SimpleGenerator implements Runnable{
    private Task t;
    public SimpleGenerator(Task t){
        this.t = t;
    }
    @Override
    public synchronized void run(){
        for (int i = 0; i < t.getN(); i++){
			t.setFunction(new Log(1 + Math.random()*9));
			t.setLeftX(Math.random()*100);
			t.setRightX(100 + Math.random()*100);
			t.setStep(Math.random());
			System.out.println("Source" + " " + t.getLeftX() + " " + t.getRightX() + " " + t.getStep());
		}	
    }
    
}
