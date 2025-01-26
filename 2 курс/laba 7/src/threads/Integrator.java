package threads;

import java.util.concurrent.Semaphore;
import functions.Functions;

public class Integrator extends Thread {

    private Task task;
    private Semaphore semaphore;
   

    public Integrator(Task task, Semaphore semaphore){
        this.task = task;
        this.semaphore = semaphore;
    }

    public void run(){
        
        for (int i = 0; i < task.getN(); i++){
            try{
                semaphore.acquire();
                if (task.getFunction() != null){
                    System.out.println("Result" + " " + i + " " + task.getLeftX() + " " + task.getRightX() + " " + task.getStep() + " " + Functions.integral(task.getFunction(), task.getLeftX(), task.getRightX(), task.getStep()));
                }  
            } catch(InterruptedException e){
                e.printStackTrace();
            } finally{
                semaphore.release();
            }
			
		}	
    }

    
}
