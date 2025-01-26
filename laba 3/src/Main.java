import functions.*;

public class Main {
	public static void main(String[] args) throws Exception {
		double[] a = {-2, -1, 0, 1, 2};
		TabulatedFunction function = new LinkedListTabulatedFunction(0, 5, a);
		function.addPoint(new FunctionPoint(6, 5));
		function.deletePoint(3);
		for (int i = 0; i < function.getPointsCount(); i++)
		{
			System.out.print(function.getPointX(i));
			System.out.print("    ");
			System.out.println(function.getPointY(i));
		}
	}
}


		

