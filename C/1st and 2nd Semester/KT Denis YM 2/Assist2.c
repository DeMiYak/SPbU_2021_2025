#include<stdio.h>
#include<math.h>
#include"Assist.h"


double cosum(double x, double eps){
    double sum = 1, t = M_PI*M_PI*x*x;
    int n = 0;
    double el = -1*t/((2*n+1)*(2*n + 2));
    while(fabs(el) > eps){
        sum += el;
        n += 1;
        el *= -1*t/((2*n+1)*(2*n + 2));
    }
    return sum;
}
