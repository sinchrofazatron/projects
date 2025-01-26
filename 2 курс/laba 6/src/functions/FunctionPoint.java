package functions;

import java.io.Serializable;

public class FunctionPoint implements Serializable{

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
	
	public String toString(){
		return "(" + String.valueOf(x) + "; " + String.valueOf(y) + ")";
	}

	public boolean equals(Object o){
		if(this == o){
			return true;
		}
		if(!(o instanceof FunctionPoint)) return false;
		FunctionPoint f = (FunctionPoint) o;
		return x == f.getX() && y == f.getY();

	}

	public Object clone(){
		return new FunctionPoint(this);
	}

	public int hashCode(){
		int hash = ((Long)(Double.doubleToLongBits(x) >>> 32)).intValue();
		hash ^= ((Long)(Double.doubleToLongBits(y) >>> 32)).intValue();
		hash ^= ((Long)(Double.doubleToLongBits(x) & 0xFFFFFFFFL)).intValue();
		hash ^= ((Long)(Double.doubleToLongBits(y) & 0xFFFFFFFFL)).intValue();
		return hash;
	}
}
