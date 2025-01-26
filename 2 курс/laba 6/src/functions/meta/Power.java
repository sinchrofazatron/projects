package functions.meta;

import functions.Function;

public class Power implements Function {

    private Function f1;
    private double n;

    public Power(Function f1, double n) {
        this.f1 = f1;
        this.n = n;
    }

    public double getLeftDomainBorder() {
       return f1.getLeftDomainBorder();
    }

    public double getRightDomainBorder() {
        return f1.getRightDomainBorder();
    }

    public double getFunctionValue(double x) {
        return Math.pow(f1.getFunctionValue(x), n);
    }
}
