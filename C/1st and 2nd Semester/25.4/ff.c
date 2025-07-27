#include<stdio.h>
#include<math.h>
#include"functions.h"

double linear (double x, double* c){
    return x*c[0] + c[1];
}
double square (double x, double* c){
    return x*x*c[0] + x*c[1] + c[2];
}
double cubic (double x, double* c){
    return x*x*x*c[0] + x*x*c[1] + x*c[2] + c[3];
}
double exponential (double x, ...){
    return pow(e, x);
}
double logarithmic (double x, ...){
    return log(x);
}

double sinus(double x, ...){
    return sin(M_PI*x);
}

double cosin(double x, ...){
    return cos(M_PI*x);
}
