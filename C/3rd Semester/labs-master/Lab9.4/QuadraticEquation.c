#include "QuadraticEquation.h"
#include <math.h>
#include <windef.h>

enum result QuadraticEquationFunc(int a, int b, int c, double *x1, double *x2) {
    if (a != a || b != b || c != c || a >= INFINITY || b >= INFINITY || c >= INFINITY) {
        return ERROR;
    }
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                return INF_RESULT;
            }
            return NO_RESULT;
        }
        if (x1 != NULL)
            *x1 = -1.0 * c / b;
        return LINE_RESULT;
    }
    double D = sqrt(b * b - 4 * a * c);
    if (D < 0) {
        return COMPLEX_RESULT;
    }
    double a2 = a * 2;
    if (D == 0) {
        if (x1 != NULL)
            *x1 = -b / a2;
        return ONE_RESULT;
    }

    if (x1 != NULL)
        *x1 = (-b - D) / a2;

    if (x2 != NULL)
        *x2 = (-b + D) / a2;

    return TWO_RESULT;
}

