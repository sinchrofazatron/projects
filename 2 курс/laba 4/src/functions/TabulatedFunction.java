package functions;

public interface TabulatedFunction extends Function{
	public int getPointsCount();
	public FunctionPoint getPoint(int index) throws FunctionPointIndexOutOfBoundsException;
	public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException;
	public double getPointX(int index) throws FunctionPointIndexOutOfBoundsException;
	public void setPointX(int index, double x) throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException;
	public double getPointY(int index) throws FunctionPointIndexOutOfBoundsException;
	public void setPointY(int index, double y) throws FunctionPointIndexOutOfBoundsException;
	public void deletePoint(int index) throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException;
	public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException;

}
