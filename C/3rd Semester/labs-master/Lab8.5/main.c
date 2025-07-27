#include <stdio.h>
#include <math.h>

const double eps = 1e-7;

double CustomSqrt(double x, double a) {
    if (x != x || a != a || x <= 0 || a <= 0) {
        return NAN;
    }
    if (x >= INFINITY || a >= INFINITY) {
        return INFINITY;
    }
    double newX = x;
    do {
        x = newX;
        newX = (x + a / x) / 2;
    } while (fabs((newX - x) / newX) > eps);
    return newX;
}

int main() {
    double a;
    scanf("%lf", &a);
    printf("%lf", CustomSqrt(a, a));
    return 0;
}
