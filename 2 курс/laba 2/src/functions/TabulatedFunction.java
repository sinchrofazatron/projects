package functions;

public interface TabulatedFunction {
	public double getLeftDomainBorder();
	public double getRightDomainBorder();
	public double getFunctionValue(double x);
	public int getPointsCount();
	public FunctionPoint getPoint(int index);
	public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException;
	public double getPointX(int index);
	public void setPointX(int index, double x) throws InappropriateFunctionPointException;
	public double getPointY(int index);
	public void setPointY(int index, double y);
	public void deletePoint(int index) throws InappropriateFunctionPointException;
	public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException;

}
