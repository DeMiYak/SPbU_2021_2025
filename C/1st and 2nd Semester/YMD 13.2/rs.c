#include<stdio.h>
#include<math.h>
#include"h.h"

void setarray(double* c){
    printf("Enter a, b, c: ");
    for(size_t i = 0; i < 3; ++i){
            scanf("%lf", &c[i]);
    }
}

double assigner(double x, double* a){
    return x*x*a[0] + x*a[1] + a[2];
}

double avrectintegr(double a, double b, double (*pfnc)(double x, double* c), size_t n, double* c){
    double delta = (b - a)/n, value = 0;
    double s = a + delta/2;

    for(size_t i = 0; i < n; ++i){
        value += pfnc(s + delta*i, c);
    }
    return delta*value;
}

double iterintegr(qf_t pfnc, double eps, double a, double b, size_t n, fnc_t d, double *q, double* c){
    double k = pfnc(a, b, d, n, c);
    double z = pfnc(a, b, d, 2*n, c);
    while(fabs((z - k)/z) > eps){
        k = z;
        n *= 2;
        z = pfnc(a, b, d, 2*n, c);
    }
    *q = (z - k)/z;
    return z;
}
