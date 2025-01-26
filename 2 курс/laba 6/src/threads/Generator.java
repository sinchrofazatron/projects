package threads;

import java.util.concurrent.Semaphore;
import functions.basic.Log;

public class Generator extends Thread{
    private Task task;
    private Semaphore semaphore;
    
    public Generator(Task task, Semaphore semaphore){
        this.task = task;
        this.semaphore = semaphore;
    }

    public void run(){
        for (int i = 0; i < task.getN(); i++){
            try{
                semaphore.acquire();
                task.setFunction(new Log(1+Math.random()*9));
                task.setLeftX(Math.random()*100);
                task.setRightX(100 + Math.random()*100);
                task.setStep(Math.random());
                System.out.println("Source " + task.getLeftX() + " " + task.getRightX() + " " + task.getStep());
            } catch(InterruptedException e){
                e.printStackTrace();
            } finally{semaphore.release();}
            
        }

    }
























   
}
