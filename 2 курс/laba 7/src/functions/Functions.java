package functions;

import functions.meta.*;

public class Functions {

    private Functions() {
    }

    public static Function shift(Function f, double shiftX, double shiftY) {
        return new Shift(f, shiftX, shiftY);
    }

    public static Function scale(Function f, double scaleX, double scaleY) {
        return new Scale(f, scaleX, scaleY);
    }

    public static Function power(Function f, double power) {
        return new Power(f, power);
    }

    public static Function sum(Function f1, Function f2) {
        return new Sum(f1, f2);
    }

    public static Function mult(Function f1, Function f2) {
        return new Mult(f1, f2);
    }

    public static Function composition(Function f1, Function f2) {
        return new Composition(f1, f2);
    }

    public static double integral(Function f, double leftX, double rightX, double step){
        if (f.getLeftDomainBorder() > leftX || rightX > f.getRightDomainBorder())
        throw new IllegalArgumentException();
        double square = 0;
        for (double x = leftX; x < rightX; x += step){
            square += ((f.getFunctionValue(x) + f.getFunctionValue(x+step))/2)*step;
            //System.out.println(x + " " + f.getFunctionValue(x) + " " + f.getFunctionValue(x+step) + " " + square);
            if (rightX - x < step){
                square += (f.getFunctionValue(x) + f.getFunctionValue(rightX))/2 * (rightX - x);
            }
        }
        return square;
    }
}
