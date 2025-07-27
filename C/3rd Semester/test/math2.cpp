#include "math2.h"
#include <cmath>
double sign (double x)
{
    if (x > 0) return 1;
    if (x == 0) return 0;
    if (x < 0) return -1;
    return x;
}

double sqrt (double x, double eps)
{
    if (x == 0 || x != x || x == 1.0/0.0) return x;
    if (x < 0) return 0.0/0.0;
    if (eps <= 0) return 0.0/0.0;

    double x1,x2 = x;
    do
    {
        x1 = x2;
        x2 = 0.5*(x1 + x/x1);
    } while (std::abs(x1 - x2) / x > eps);
    return x2;
}
