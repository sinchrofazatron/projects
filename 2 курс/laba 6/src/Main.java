import static java.lang.Double.toString;

import java.io.*;
import functions.*;
import functions.basic.*;
import threads.*;
import java.util.Random;
import java.util.concurrent.Semaphore;


public class Main {

	public static void nonThread(){
		Task t = new Task(100);
		for (int i = 0; i < t.getN(); i++){
			t.setFunction(new Log(1 + Math.random()*9));
			t.setLeftX(Math.random()*100);
			t.setRightX(100 + Math.random()*100);
			t.setStep(Math.random());
			System.out.println("Source " + t.getLeftX() + " " + t.getRightX() + " " + t.getStep());
			System.out.println("Result " + t.getLeftX() + " " + t.getRightX() + " " + t.getStep() + " " + Functions.integral(t.getFunction(), t.getLeftX(), t.getRightX(), t.getStep()));
		}	
	}

	public static void simpleThreads(){
		Task t = new Task(100);
		Thread generate = new Thread(new SimpleGenerator(t));
		generate.setPriority(Thread.MIN_PRIORITY);
		generate.start();
		Thread integrate = new Thread(new SimpleIntegrator(t));
		integrate.setPriority(Thread.MAX_PRIORITY);
		integrate.start();
	}

	public static void complicatedThreads() throws InterruptedException{
		Task t = new Task(100);
		Semaphore semaphore = new Semaphore(1, true);
		Generator generate = new Generator(t, semaphore);
		generate.start();
		Integrator integrate = new Integrator(t, semaphore);
		integrate.start();
	}



	public static void main(String[] args) throws IOException, ClassNotFoundException, InappropriateFunctionPointException, CloneNotSupportedException, InterruptedException {
		TabulatedFunction sin = TabulatedFunctions.tabulate(new Sin(), 0, Math.PI, 5);
		System.out.println(Functions.integral(new Sin(), 0, Math.PI, Math.PI/4));
		//Functions.integral(new Sin(), 0, 2*Math.PI, 10);
		//nonThread();
		//simpleThreads();
		complicatedThreads();
	}

	



}
