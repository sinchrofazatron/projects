package functions.meta;

import functions.Function;

public class Mult implements Function {
    private Function f1, f2;

    public Mult(Function f1, Function f2) {
        this.f1 = f1;
        this.f2 = f2;
    }

    public double getLeftDomainBorder() {
        if (f1.getRightDomainBorder() < f2.getLeftDomainBorder()
                || f2.getRightDomainBorder() < f1.getLeftDomainBorder())
            return Double.NaN;
        return f1.getLeftDomainBorder() < f2.getLeftDomainBorder() ? f2.getLeftDomainBorder()
                : f1.getLeftDomainBorder();
    }

    public double getRightDomainBorder() {
        if (f1.getRightDomainBorder() < f2.getLeftDomainBorder()
                || f2.getRightDomainBorder() < f1.getLeftDomainBorder())
            return Double.NaN;
        return f1.getRightDomainBorder() < f2.getRightDomainBorder() ? f1.getRightDomainBorder()
                : f2.getRightDomainBorder();
    }

    public double getFunctionValue(double x) {
        return f1.getFunctionValue(x) * f2.getFunctionValue(x);
    }
}
