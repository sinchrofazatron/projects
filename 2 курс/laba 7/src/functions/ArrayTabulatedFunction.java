package functions;

import java.io.Serializable;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class ArrayTabulatedFunction implements TabulatedFunction, Serializable{

	private transient double leftX;
	private transient double rightX;
	private int pointsCount;
	private FunctionPoint[] points;

	public static class ArrayTabulatedFunctionFactory implements TabulatedFunctionFactory{

		@Override
		public TabulatedFunction createTabulatedFunction(double leftX, double rightX, double[] values) {
			return new ArrayTabulatedFunction(leftX, rightX, values);
		}

		@Override
		public TabulatedFunction createTabulatedFunction(double leftX, double rightX, int pointsCount) {
			return new ArrayTabulatedFunction(leftX, rightX, pointsCount);
		}

		@Override
		public TabulatedFunction createTabulatedFunction(FunctionPoint[] points) {
			return new ArrayTabulatedFunction(points);
		}
	}

	public ArrayTabulatedFunction(FunctionPoint[] points) throws IllegalArgumentException {
		if (points.length < 2)
			throw new IllegalArgumentException();
		for (int i = 0; i < points.length - 1; i++) {
			if (points[i].getX() >= points[i + 1].getX())
				throw new IllegalArgumentException();
		}
		pointsCount = points.length;
		leftX = points[0].getX();
		rightX = points[pointsCount - 1].getX();
		this.points = new FunctionPoint[pointsCount];
		System.arraycopy(points, 0, this.points, 0, pointsCount);
	}

	public ArrayTabulatedFunction(double leftX, double rightX, int pointsCount) throws IllegalArgumentException {
		this.leftX = leftX;
		this.rightX = rightX;
		if (leftX >= rightX || pointsCount < 2)
			throw new IllegalArgumentException();
		this.pointsCount = pointsCount;
		double stepX = (rightX - leftX) / (pointsCount - 1);
		this.points = new FunctionPoint[pointsCount * 4];
		for (int i = 0; i < pointsCount; i++) {
			points[i] = new FunctionPoint(leftX, rightX);
			leftX += stepX;
		}
	}

	public ArrayTabulatedFunction(double leftX, double rightX, double[] values) throws IllegalArgumentException {
		this(leftX, rightX, values.length);
		for (int i = 0; i < pointsCount; i++) {
			points[i].setY(values[i]);
		}
	}

	private ArrayTabulatedFunction(ArrayTabulatedFunction f) {
		leftX = f.leftX;
		rightX = f.rightX;
		pointsCount = f.pointsCount;
		points = new FunctionPoint[pointsCount * 2];
		for (int i = 0; i < pointsCount; i++) {
			points[i] = (FunctionPoint) f.points[i].clone();
		}
	}

	public double getLeftDomainBorder() {
		return this.leftX;
	}

	public double getRightDomainBorder() {
		return this.rightX;
	}

	public double getFunctionValue(double x) {
		if (x > rightX || x < leftX)
			return Double.NaN;
		else
			return getY(x);
	}

	private double getY(double x) {

		int firstPoint = indexX(x);
		int secondPoint = firstPoint + 1;

		if (firstPoint < 0 || firstPoint >= pointsCount || secondPoint >= pointsCount) {
			return Double.NaN;
		}

		double deltaY = points[secondPoint].getY() - points[firstPoint].getY();
		double deltaX = x - points[firstPoint].getX();

		double k = deltaY / deltaX;
		double b = points[secondPoint].getY() - k * points[secondPoint].getX();
		return k * x + b;

	}

	public int getPointsCount() {
		return pointsCount;
	}

	public FunctionPoint getPoint(int index) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index > getPointsCount())
			throw new FunctionPointIndexOutOfBoundsException();
		return points[index];
	}

	public void setPoint(int index, FunctionPoint point)
			throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= pointsCount)
			throw new FunctionPointIndexOutOfBoundsException();
		if (point.getX() < leftX || point.getX() > rightX)
			throw new InappropriateFunctionPointException("");
		points[index] = new FunctionPoint(point);
	}

	public double getPointX(int index) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= pointsCount)
			throw new FunctionPointIndexOutOfBoundsException();
		return points[index].getX();
	}

	public void setPointX(int index, double x)
			throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= pointsCount)
			throw new FunctionPointIndexOutOfBoundsException();
		if (x < leftX || x > rightX)
			throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		points[index].setX(x);
	}

	public double getPointY(int index) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= pointsCount)
			throw new FunctionPointIndexOutOfBoundsException();
		return points[index].getY();
	}

	public void setPointY(int index, double y) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= pointsCount)
			throw new FunctionPointIndexOutOfBoundsException();
		points[index].setY(y);
	}

	public void deletePoint(int index) throws IllegalStateException, FunctionPointIndexOutOfBoundsException {
		if (pointsCount < 3)
			throw new IllegalStateException();
		if (index < 0 || index > getPointsCount())
			throw new FunctionPointIndexOutOfBoundsException();
		points[index] = null;
		shiftToLeft(index + 1);
		pointsCount--;
	}

	private void shiftToLeft(int index) {
		for (int i = index; i < pointsCount; i++) {
			if (i == 0)
				continue;
			points[i - 1] = points[i];
			points[i] = null;

		}
	}

	public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException {
		if (pointsCount == points.length) {
			FunctionPoint[] newP = new FunctionPoint[pointsCount * 2];
			System.arraycopy(this.points, 0, newP, 0, pointsCount);
			this.points = newP;
		}
		int index = indexX(point.getX()) + 1;
		for (int i = 0; i < pointsCount; i++) {
			if (points[i].getX() == point.getX())
				throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		}
		shiftToRight(index);
		setPoint(index, point);
		pointsCount++;
		leftX = Math.min(leftX, point.getX());
		rightX = Math.max(rightX, point.getX());
	}

	public int indexX(double x) {

		// if (x < points[0].getX()) {
		// return 0;
		// }
		// if (x >= points[pointsCount - 1].getX()) {
		// return pointsCount - 1; // Возвращаем последний индекс
		// }
		// int i = 0;
		// while (x >= points[i + 1].getX()) {
		// ++i;
		// }
		// return i;

		if (x < points[0].getX())
			return 0;
		int i = 0;
		while (x < points[i + 1].getX())
			++i;

		return i;
	}

	private void shiftToRight(int index) {
		for (int i = pointsCount; i > index; i--) {
			points[i] = points[i - 1];
		}
	}

	public String toString() {
		String s = "{";
		for (int i = 0; i < pointsCount - 1; i++) {
			s += points[i].toString() + ", ";
		}
		return s += points[pointsCount - 1] + "}";

	}

	public Object clone() {
		return new ArrayTabulatedFunction(this);
	}
	
	public boolean equals(Object o) {
		if (this == o) return true;
		if (!(o instanceof TabulatedFunction)) return false;
		if (o instanceof ArrayTabulatedFunction) {
			ArrayTabulatedFunction arr = (ArrayTabulatedFunction)o;
			if (pointsCount != arr.pointsCount) return false;
			for (int i = 0; i < pointsCount; i++){
				if (!points[i].equals(arr.points[i])) return false;
			}
		} else {
			TabulatedFunction tab = (TabulatedFunction)o;
			if (pointsCount != tab.getPointsCount()) return false;
			for (int i = 0; i < pointsCount; i++){
				if (!points[i].equals(tab.getPoint(i))) return false;
			}
		}
		return true;
	}

	public int hashCode(){
		int hash = pointsCount;
		for (int i = 0; i < pointsCount; i++){
			hash ^= points[i].hashCode();
		}
		return hash;
	}

	public Iterator<FunctionPoint> iterator() throws NoSuchElementException, UnsupportedOperationException{
		return new Iterator<FunctionPoint>(){
			private int currentIndex = 0;

			@Override
			public boolean hasNext(){
				return currentIndex < pointsCount;
			}

			@Override
			public FunctionPoint next(){
				if (currentIndex >= pointsCount) {throw new NoSuchElementException();}
				
				else {
					return new FunctionPoint(points[currentIndex++]);
				}
			}

			@Override
			public void remove(){
				throw new UnsupportedOperationException();
			}
		};
	}
}

//return currentIndex < pointsCount && points[currentIndex] != null;
//if (points[currentIndex++]== null) {throw new NoSuchElementException();}
//return points[currentIndex++];