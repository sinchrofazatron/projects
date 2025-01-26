package functions;

import java.io.*;
import java.lang.reflect.Constructor;

public class TabulatedFunctions {

    private static TabulatedFunctionFactory factory = new ArrayTabulatedFunction.ArrayTabulatedFunctionFactory();

    public static void setTabulatedFunctionFactory(TabulatedFunctionFactory f) {
        factory = f;
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, double[] values) {
        return factory.createTabulatedFunction(leftX, rightX, values);
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, int pointsCount) {
        return factory.createTabulatedFunction(leftX, rightX, pointsCount);
    }

    public static TabulatedFunction createTabulatedFunction(FunctionPoint[] points) {
        return factory.createTabulatedFunction(points);
    }





    public static TabulatedFunction createTabulatedFunction(Class<? extends TabulatedFunction> c, double leftX, double rightX, double[] values) throws IllegalArgumentException{
        try{
            Constructor<? extends TabulatedFunction> constructor = c.getConstructor(double.class, double.class, double[].class);
            return constructor.newInstance(leftX, rightX, values);
           
        }catch(Exception e){
            throw new IllegalArgumentException(e);
        }
    }

    public static TabulatedFunction createTabulatedFunction(Class<? extends TabulatedFunction> c, double leftX, double rightX, int pointsCount) throws IllegalArgumentException{
        try{
            Constructor<? extends TabulatedFunction> constructor = c.getConstructor(double.class, double.class, int.class);
            return constructor.newInstance(leftX, rightX, pointsCount);
        }catch(Exception e){
            throw new IllegalArgumentException(e);
        }
    }

    public static TabulatedFunction createTabulatedFunction(Class<? extends TabulatedFunction> c, FunctionPoint[] points) throws IllegalArgumentException{
        try{
            Constructor<? extends TabulatedFunction> constructor = c.getConstructor(FunctionPoint[].class);
            return constructor.newInstance((Object)points);
        } catch(Exception e){
            throw new IllegalArgumentException(e);
        }
    }

    public static TabulatedFunction tabulate(Function function, double leftX, double rightX, int pointsCount) {
        if (leftX < function.getLeftDomainBorder() || rightX > function.getRightDomainBorder())
            throw new IllegalArgumentException();
        FunctionPoint points[] = new FunctionPoint[pointsCount];
        double stepX = (rightX - leftX) / (pointsCount - 1);
        for (int i = 0; i < pointsCount; i++) {
            points[i] = new FunctionPoint(leftX + stepX * i, function.getFunctionValue(leftX + stepX * i));
        }
        return createTabulatedFunction(points);
    }

    public static TabulatedFunction tabulate(Class<? extends TabulatedFunction> c, Function function, double leftX, double rightX, int pointsCount) {
        if (leftX < function.getLeftDomainBorder() || rightX > function.getRightDomainBorder())
            throw new IllegalArgumentException();
        FunctionPoint points[] = new FunctionPoint[pointsCount];
        double stepX = (rightX - leftX) / (pointsCount - 1);
        for (int i = 0; i < pointsCount; i++) {
            points[i] = new FunctionPoint(leftX + stepX * i, function.getFunctionValue(leftX + stepX * i));
        }
        return createTabulatedFunction(points);
    }

    public static void outputTabulatedFunction(TabulatedFunction function, OutputStream out) {

        try {
            DataOutputStream d = new DataOutputStream(out);
            int count = function.getPointsCount();
            d.writeInt(count);
            for (int i = 0; i < count; i++) {
                d.writeDouble(i);
            }
        } catch (IOException e) {
            System.out.println("File not open");
        }

        finally {
            try {
                out.close();
            } catch (IOException e) {
                System.out.println("Error closing");
            }
        }

    }

    public static TabulatedFunction inputTabulatedFunction(InputStream in) throws IOException {

        DataInputStream d = new DataInputStream(in);
        int count = d.readInt();
        FunctionPoint[] points = new FunctionPoint[count];
        for (int i = 0; i < count; i++) {
            points[i] = new FunctionPoint(d.readDouble(), d.readDouble());
        }
        return createTabulatedFunction(points);

    }

    public static TabulatedFunction inputTabulatedFunction(Class<? extends TabulatedFunction> c, InputStream in) throws IOException {

        DataInputStream d = new DataInputStream(in);
        int count = d.readInt();
        FunctionPoint[] points = new FunctionPoint[count];
        for (int i = 0; i < count; i++) {
            points[i] = new FunctionPoint(d.readDouble(), d.readDouble());
        }
        return createTabulatedFunction(c, points);

    }

    public static void writeTabulatedFunction(TabulatedFunction function, Writer out) {
        PrintWriter w = new PrintWriter(out);
        int count = function.getPointsCount();
        w.write(count);
        for (int i = 0; i < count; i++) {
            w.println(function.getPointX(i));
            w.println(function.getPointY(i));
        }
    }

    public static TabulatedFunction readTabulatedFunction(Reader in) throws IOException {

        StreamTokenizer token = new StreamTokenizer(in);
        token.nextToken();
        int count = (int) token.nval;
        double x, y;
        FunctionPoint[] points = new FunctionPoint[count];
        for (int i = 0; i < count; i++) {
            token.nextToken();
            x = token.nval;
            token.nextToken();
            y = token.nval;
            points[i] = new FunctionPoint(x, y);
        }
        return createTabulatedFunction(points);
    }

}
