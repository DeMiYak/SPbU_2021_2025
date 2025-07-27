#include <stdio.h>
#include "QuadraticEquation.h"

int main() {
    int a, b, c;
    double x1, x2;
    scanf("%i%i%i", &a, &b, &c);
    enum result res = QuadraticEquationFunc(a, b, c, &x1, &x2);
    switch (res) {
        case TWO_RESULT:
            printf("two results: x1=%lf x2=%lf", x1, x2);
            break;
        case ONE_RESULT:
            printf("one result: x=%lf", x1);
            break;
        case COMPLEX_RESULT:
            printf("complex result");
            break;
        case LINE_RESULT:
            printf("line result: x=%lf", x1);
            break;
        case NO_RESULT:
            printf("no result");
            break;
        case INF_RESULT:
            printf("infinity results");
            break;
        case ERROR:
            printf("ERROR");
    }
}
