package functions;

import java.io.Externalizable;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import java.io.Serializable;

public class LinkedListTabulatedFunction implements TabulatedFunction, Externalizable{
	private class FunctionNode implements Serializable {
		public FunctionPoint data;
		public FunctionNode next;
		public FunctionNode prev;

		public FunctionNode() {
			this.data = new FunctionPoint();
			this.next = this.prev = this;
		}
	}

	private FunctionNode head = new FunctionNode();
	private int size = 0;
	private FunctionNode last = head;
	private int lastIndex = 0;

	public LinkedListTabulatedFunction(){}

	public LinkedListTabulatedFunction(FunctionPoint[] points) throws IllegalArgumentException {
		if (points.length < 2)
			throw new IllegalArgumentException();
		for (int i = 0; i < points.length - 1; i++) {
			if (points[i].getX() >= points[i + 1].getX())
				throw new IllegalArgumentException();
		}
		for (int i = 0; i < points.length; i ++){
			addNodeToTail();
			last.data = new FunctionPoint(points[i]);
		}
		last = head.next;
	}

	public LinkedListTabulatedFunction(double leftX, double rightX, int pointsCount) throws IllegalArgumentException {
		if (leftX >= rightX || pointsCount < 2)
			throw new IllegalArgumentException();
		double stepX = (rightX - leftX) / (pointsCount - 1);
		for (int i = 0; i < pointsCount; i++) {
			addNodeToTail();
			head.prev.data.setX(leftX + stepX * i);//head
			head.prev.data.setY(0);
		}
		last = head.next;
	}

	public LinkedListTabulatedFunction(double leftX, double rightX, double[] values) throws IllegalArgumentException {
		this(leftX, rightX, values.length);
		FunctionNode node = head.next;
		for (int i = 0; i < values.length; ++i, node = node.next) {
			node.data.setY(values[i]);
		}
	}

	private FunctionNode getNodeByIndex(int index) {
		if ((size - index < size / 2 ? size - index : index + 1) < Math.abs(lastIndex - index)) {
			last = head;
			if (size - index < size / 2) {
				for (int i = 0; i < size - index; i++) {
					last = last.prev;
				}
			} else {
				for (int i = 0; i < index + 1; i++) {
					last = last.next;
				}

			}
		} else {
			if (lastIndex < index) {
				for (int i = 0; i < index - lastIndex; ++i) {
					last = last.next;
				}
			} else {
				for (int i = 0; i < lastIndex - index; ++i) {
					last = last.prev;
				}
			}
		}
		lastIndex = index;
		return last;
	}

	private void addNode(FunctionNode node) {
		last = new FunctionNode();

		last.next = node;
		last.prev = node.prev;

		node.prev.next = last; 
		node.prev = last; 

		++size;

		// last = new FunctionNode();

		// last.next = head;
		// last.prev = head.prev;

		// head.prev.next = last; 
		// head.prev = last; 

		// ++size;

	}

	private FunctionNode addNodeToTail() {
		


		addNode(head);
		return last;
	}

	private FunctionNode addNodeByIndex(int index) {
		FunctionNode node = getNodeByIndex(index);
		addNode(node);
		return last;
	}

	private FunctionNode deleteNodeByIndex(int index) {
		getNodeByIndex(index);
		FunctionNode node = last;
		last = last.next;
		node.next.prev = node.prev;
		node.prev.next = node.next;
		node.prev = node.next = node;
		size--;
		return node;
	}

	public double getLeftDomainBorder() {
		return head.next.data.getX();
	}

	public double getRightDomainBorder() {
		return head.prev.data.getX();
	}

	public double getFunctionValue(double x) {
		if (x > getRightDomainBorder() || x < getLeftDomainBorder())
			return Double.NaN;
		return getY(x);
	}

	private double getY(double x) {

		int secondPoint = indexX(x);
		int firstPoint = secondPoint - 1;

		if (firstPoint < 0 || last == head) {
			return Double.NaN;
		}

		double deltaY = last.data.getY() - last.prev.data.getY();
		double deltaX = last.data.getX() - last.prev.data.getX();

		double k = deltaY / deltaX;
		double b = last.data.getY() - k * last.data.getX();
		return k * x + b;
	}

	public int getPointsCount() {
		return size;
	}

	public FunctionPoint getPoint(int index) throws FunctionPointIndexOutOfBoundsException{
		if (index < 0 || index > getPointsCount())
			throw new FunctionPointIndexOutOfBoundsException();
		return getNodeByIndex(index).data;
	}

	public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException {
		getNodeByIndex(index);
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		if (point.getX() >= last.prev.data.getX() || point.getX() <= last.next.data.getX())
			throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		last.data = new FunctionPoint(point);
	}

	public double getPointX(int index) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		return getNodeByIndex(index).data.getX();
	}

	public void setPointX(int index, double x) throws InappropriateFunctionPointException, FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		if (x < head.prev.data.getX() || x > head.next.data.getX())
			throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		getNodeByIndex(index).data.setX(x);
	}

	public double getPointY(int index) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		return getNodeByIndex(index).data.getY();
	}

	public void setPointY(int index, double y) throws FunctionPointIndexOutOfBoundsException {
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		getNodeByIndex(index).data.setY(y);
	}

	public void deletePoint(int index) throws FunctionPointIndexOutOfBoundsException, IllegalStateException {
		if (size < 3)
			throw new IllegalStateException();
		if (index < 0 || index >= getPointsCount())
			throw new FunctionPointIndexOutOfBoundsException();
		deleteNodeByIndex(index);
	}

	public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException {

		int index = indexX(point.getX());
		getNodeByIndex(index);
		if (last.data.getX() == point.getX())
			throw new InappropriateFunctionPointException("Абсцисса точки совпадает с абсциссой добавляемой точки");
		addNodeByIndex(index);
		last.data.setX(point.getX());
		last.data.setY(point.getY());
	}

	int indexX(double x) {

		if (x < getLeftDomainBorder())
			return 0;
		int i = 0;
		last = head.next;
		while (last != head && last.data.getX() < x) {
			last = last.next;
			i++;
		}

		return i;
	}

	@Override
	public void writeExternal(ObjectOutput out) throws IOException {
		out.writeObject(size);
		out.writeObject(head);
	}

	@Override
	public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
		size = (int)in.readObject();
		head = (FunctionNode)in.readObject();
		lastIndex = 0;
		last = head.next;
	}

	public String toString(){
		last = head.next;
		String s = "{";
		while (last.next != head){
			s += last.data.toString() + ", ";
			last = last.next;
		}

		return s += head.prev.data.toString() + "}";

	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (!(o instanceof TabulatedFunction)) return false;
		if (o instanceof LinkedListTabulatedFunction) {
			LinkedListTabulatedFunction arr = (LinkedListTabulatedFunction)o;
			if (size != arr.size) return false;
			last = head.next;
			FunctionNode arrLast = arr.head.next;
			while(last != head){
				if (!last.data.equals(arrLast.data)) return false;
				last = last.next;
				arrLast = arrLast.next;
				
			}
		} else {
			TabulatedFunction tab = (TabulatedFunction)o;
			if (size != tab.getPointsCount()) return false;
			for (int i = 0; i < size; i++){
				if (!this.getPoint(i).equals(tab.getPoint(i))) return false;
			}
		}
		return true;
	}
	
	public Object clone(){
		FunctionPoint[] point = new FunctionPoint[this.getPointsCount()];
		for (int i = 0; i < this.getPointsCount(); i++){
			point[i] = (FunctionPoint) this.getPoint(i).clone();
		}
		return new LinkedListTabulatedFunction(point);
	}

	public int hashCode(){
		int hash = size;
		last = head.next;
		while(last != head){
			last = last.next;
			hash ^= last.data.hashCode();
		}
		return hash;
	}
}
