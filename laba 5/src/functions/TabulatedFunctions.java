package functions;
import java.io.*;

public class TabulatedFunctions {
    private TabulatedFunctions() {
    }

    public static TabulatedFunction tabulate(Function function, double leftX, double rightX, int pointsCount) {
        if (leftX < function.getLeftDomainBorder() || rightX > function.getRightDomainBorder())
            throw new IllegalArgumentException();
        FunctionPoint points[] = new FunctionPoint[pointsCount];
        double stepX = (rightX - leftX) / (pointsCount - 1);
        for (int i = 0; i < pointsCount; i++) {
            points[i] = new FunctionPoint(leftX + stepX*i, function.getFunctionValue(leftX + stepX*i));
        }
        return new LinkedListTabulatedFunction(points);
    }

    public static void outputTabulatedFunction(TabulatedFunction function, OutputStream out) {

        try{
            DataOutputStream d = new DataOutputStream(out);
            int count  = function.getPointsCount();
            d.writeInt(count);
            for (int i = 0; i < count; i++){
                d.writeDouble(i);
            }
        }
        catch (IOException e){
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
            for (int i = 0; i < count; i++){
                points[i] = new FunctionPoint(d.readDouble(), d.readDouble());
            }
        return new LinkedListTabulatedFunction(points);

    }

    // public static void writeTabulatedFunction(TabulatedFunction function, Writer out) {
    //     PrintWriter w = new PrintWriter(out);
    //     int count = function.getPointsCount();
    //     w.write(count);
    //     for (int i = 0; i < count; i++){
    //         w.println(function.getPointX(i));
    //         w.println(function.getPointY(i));
    //     }
    // }

    public static void writeTabulatedFunction(TabulatedFunction function, Writer out) {
        PrintWriter w = new PrintWriter(out);
        int count = function.getPointsCount();
        w.write(count + " ");
        for (int i = 0; i < count; i++){
            w.print(function.getPointX(i) + " " + function.getPointY(i) + " ");  
        }
        w.flush();
        w.close();
    }

    public static TabulatedFunction readTabulatedFunction(Reader in) throws IOException{
        
        StreamTokenizer token = new StreamTokenizer(in);
        token.nextToken();
        int count = (int) token.nval;
        double x, y;
        FunctionPoint[] points = new FunctionPoint[count];
        for (int i = 0; i < count; i++){
            token.nextToken();
            x = token.nval;
            token.nextToken();
            y = token.nval;
            points[i] = new FunctionPoint(x, y);
        }
        return new LinkedListTabulatedFunction(points);
    }

}
