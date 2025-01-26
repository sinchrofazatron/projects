package functions;

public class LinkedListTabulatedFunction implements TabulatedFunction{
	private class FunctionNode{
		public FunctionPoint data;
		public FunctionNode next;
		public FunctionNode prev;
		
		FunctionNode(){
			this.data = new FunctionPoint();
			this.next = this.prev = this;
		}
		
		FunctionNode(FunctionPoint data){
			this.data = new FunctionPoint(data);
			this.next = this.prev = this;
		}
		
	}
	
	private FunctionNode head = new FunctionNode();
	private int size = 0;
	
	public LinkedListTabulatedFunction(double leftX, double rightX, int pointsCount) throws IllegalArgumentException{
		if (leftX >= rightX || pointsCount < 2) 
			throw new IllegalArgumentException();
		double stepX = (rightX - leftX) / (pointsCount-1);
		for (int i = 0; i < pointsCount; i++) {
			addNodeToTail();
			head.prev.data.setX(leftX + stepX * i);
			head.prev.data.setY(0);
		}
	}
	
	public LinkedListTabulatedFunction(double leftX, double rightX, double[] values) throws IllegalArgumentException{
		this(leftX, rightX, values.length);
		FunctionNode node = head.next;
		for (int i = 0; i < values.length; ++i, node = node.next) {
			node.data.setY(values[i]);
		}
	}
	
	private FunctionNode getNodeByIndex(int index) {
		FunctionNode result = null;
		int half = this.size/2;
		int count = index < half? index : this.size - index - 1;
		for (FunctionNode node = index < half? this.head.next : this.head.prev; node!=this.head; node = (index < half? node.next : node.prev)) {
			if (count-- == 0) {
				result = node;
				break;
			}
		}
		return result;
	}    
	
	private FunctionNode addNodeToTail(){
		FunctionNode newNode = new FunctionNode(new FunctionPoint());
		
		newNode.next = head;
		newNode.prev = head.prev;
		
		head.prev.next = newNode;
		head.prev = newNode;
		
		++ size;
		return newNode;
	}
	
	private FunctionNode addNodeToHead() {
		FunctionNode newNode = new FunctionNode(new FunctionPoint());
		
		newNode.next = head.next;
		newNode.prev = head;
		
		head.next.prev = newNode;
		head.next = newNode;
		
		++size;
		return newNode;
	}
	
	private FunctionNode addNodeByIndex(int index) {
		if (index == 0)
			return addNodeToHead();
		if (index == size)
			return addNodeToTail();
		++size;
		FunctionNode oldNode = getNodeByIndex(index);
		FunctionNode newNode = new FunctionNode(new FunctionPoint());
		newNode.next = oldNode;
		newNode.prev = oldNode.prev;
		oldNode.prev.next = newNode;
		oldNode.prev = newNode;
		return newNode;
	}
	
	private void deleteNodeByIndex(int index) {
		--size;
		FunctionNode deleteNode = getNodeByIndex(index);
		if (index == 0)
			head.next = deleteNode.next;
		if (index == size-1)
			head.prev = deleteNode.prev;
		deleteNode.prev.next = deleteNode.next;
		deleteNode.next.prev = deleteNode.prev;
	}
	
	/*public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException{
		if (head.prev.data.getX() < point.getX())
			addNodeToTail().data = new FunctionPoint(point);
		else
			throw new InappropriateFunctionPointException("Абсцисса точки совпадает с абсциссой добавляемой точки");
	}
	*/
	
	public double getLeftDomainBorder(){
		return head.next.data.getX();
	}
	
	public double getRightDomainBorder(){
		return head.prev.data.getX();
	}
	
	public double getFunctionValue(double x){
		if (x > this.head.next.data.getX() || x < this.head.prev.data.getX())
			return Double.NaN; 
		else
			return getY(x);
	}
	
	private double getY(double x) { 
		
		int firstPoint = indexX(x);
		int secondPoint = firstPoint + 1;
		
		if (firstPoint < 0 || firstPoint >= size || secondPoint >= size) {
			return Double.NaN;
		}
		
		double deltaY = head.next.data.getY() - head.prev.data.getY();
		double deltaX = head.next.data.getX() - head.prev.data.getX();
		
		double k = deltaY / deltaX;
		double b = head.prev.data.getY() - k*head.prev.data.getX();
		return k*x + b;  

	}
	
	public int getPointsCount(){
		return size;
	}
	
	public FunctionPoint getPoint(int index){ 
		if (index < 0 || index > getPointsCount()) 
			throw new FunctionPointIndexOutOfBoundsException();
		return getNodeByIndex(index).data;
	}
	
	public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException{
		FunctionNode n = getNodeByIndex(index);
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		if (point.getX() >= n.prev.data.getX() || point.getX() <= n.next.data.getX()) 
			throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		n.data = point;
	}
	
	public double getPointX(int index) {
		if (index < 0 || index >= size) 
			throw new FunctionPointIndexOutOfBoundsException();
		return getNodeByIndex(index).data.getX();
	}
	
	public void setPointX(int index, double x) throws InappropriateFunctionPointException{
		if (index < 0 || index >= size)
			throw new FunctionPointIndexOutOfBoundsException();
		if (x < head.prev.data.getX() || x > head.next.data.getX()) 
			throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		getNodeByIndex(index).data.setX(x);
	}

	public double getPointY(int index) {
		if (index < 0 || index >= size) 
			throw new FunctionPointIndexOutOfBoundsException();
		return getNodeByIndex(index).data.getY();
	}
		
	public void setPointY(int index, double y) {
		if (index < 0 || index >= size)  
			throw new FunctionPointIndexOutOfBoundsException();
		getNodeByIndex(index).data.setY(y);
	}	
	
	public void deletePoint(int index) throws InappropriateFunctionPointException{
		if (size < 3)
			throw new IllegalStateException();
//		if (points[index].getX() < leftX || points[index].getX() > rightX) 
//			throw new InappropriateFunctionPointException();
		if (index < 0 || index > getPointsCount())
			throw new FunctionPointIndexOutOfBoundsException();
//		points[index] = null;
//		shiftToLeft(index+1);
//		size--;
		deleteNodeByIndex(index);
	}
	
//	private void shiftToLeft(int index) {
//		for (int i = index; i < pointsCount; i++) {
//			if (i == 0)
//				continue;
//			points[i-1] = points[i];
//			points[i] = null;
//			
//		}
//	}
	
	public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException{
		
		int index = indexX(point.getX());
		FunctionNode n = getNodeByIndex(index);
		if (n.data.getX() == point.getX())
			throw new InappropriateFunctionPointException("Абсцисса точки совпадает с абсциссой добавляемой точки");
		addNodeByIndex(index);
		n = n.prev;
		n.data.setX(point.getX());
		n.data.setY(point.getY());
		
		
		/*FunctionNode n = addNodeByIndex(index);
		if (size == index && head.prev.data.getX() < point.getX())
			n.data = point;
		else if (index == 0 && head.next.data.getX() > point.getX())
			n.data = point;
		else if (n.prev.data.getX() <= point.getX() && point.getX() <= n.next.data.getX())
			n.data = point;
		else
			throw new InappropriateFunctionPointException("Координата x задаваемой точки лежит вне интервала");
		*/
	}
	
	int indexX(double x) {
		
		if (x < head.next.data.getX())
			return 0;
		int i = 0;
		FunctionNode n = head.next;
		while(n != head && n.data.getX() < x) {
			n = n.next;
			i++;
		}
		//return i-1;
		
		return i;
	}
	
//	private void shiftToRight(int index) {
//		for (int i = pointsCount; i > index; i--) {
//			points[i] = points[i-1];
//		}
//	}

}
