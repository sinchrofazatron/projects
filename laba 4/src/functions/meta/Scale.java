package functions.meta;

import functions.Function;

public class Scale implements Function {

    private Function f1;
    private double kx, ky;

    public Scale(Function f1, double kx, double ky) {
        this.f1 = f1;
        this.kx = kx;
        this.ky = ky;
    }

    public double getLeftDomainBorder() {
        return f1.getLeftDomainBorder() * kx;
    }

    public double getRightDomainBorder() {
        return f1.getRightDomainBorder() * kx;
    }

    public double getFunctionValue(double x) {
        return f1.getFunctionValue(x * kx) * ky;

    }

}
