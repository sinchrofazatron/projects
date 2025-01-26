package functions;

public class FunctionPoint {

	private double x;
	private double y;
	
	public FunctionPoint(double x, double y){
		this.x = x;
		this.y = y;
	}
	
	public FunctionPoint(FunctionPoint Point){
		this.x = Point.getX();
		this.y = Point.getY();
	}
	
	public FunctionPoint(){
		this.x = 0;
		this.y = 0;
	}
	
	public double getX() {
		return x;
	}
	
	public double getY() {
		return y;
	}
	
	public void setX(double x) {
		this.x = x;
	}
	
	public void  setY(double y) {
		this.y = y;
	}
	
	
}
