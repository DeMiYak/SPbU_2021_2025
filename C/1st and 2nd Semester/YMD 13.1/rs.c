/**
* Аргументом функции должны выступать границы промежутка, указатель на функцию
*(одного аргумента типа double с возр значением типа double и входного массива параметров double*) и число точек разбиения промежутка.
*/

#include<stdio.h>
#include"pp.h"

void setarray(double* c){
    printf("Enter a, b, c: ");
    for(size_t i = 0; i < 3; ++i){
            scanf("%lf", &c[i]);
    }
}


double assigner(double x, double* a){
    return x*x*a[0] + x*a[1] + a[2];
}

double avrectintegr(double l, double d, double (*pfnc)(double x, double* c), size_t n, double* c){
    double delta = (d - l)/n, value = 0;
    double start = l + delta/2;

    for(size_t i = 0; i < n; ++i){
        value += pfnc(start + delta*i, c);
    }
    return delta*value;
}


double parabintegr(double l, double d, double (*pfnc)(double x, double* c), size_t n, double* c){
    double delta = (d - l)/(3*n), value = pfnc(l, c) + pfnc(d, c);
    if(n == 2) return value*delta;
    for(size_t i = 1; i < n; ++i){
        if(i%2){
            value += 4*pfnc(l + (d - l)*i/n, c);
        } else value += 2*pfnc(l + (d - l)*i/n, c);
    }
    return value*delta;
}
