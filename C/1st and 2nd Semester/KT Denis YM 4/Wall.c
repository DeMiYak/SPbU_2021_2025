#include<stdio.h>


double RecurCheb(double x, int n){
    if (n == 0){
        return 1;
    } else if (n == 1){
        return 2*x;
    } else return 2*x*RecurCheb(x, n-1) - RecurCheb(x, n-2);
}

double IterCheb(double x, int n){
    int i = 2;
    double u0 = 1, u1 = 2*x;
    if(n == 0){
        return u0;
    } else while(i <= n){ // создаём цепочку из 2 чисел, присваивая каждому новое значение
        double q = u1;
        u1 = 2*x*u1 - u0;
        u0 = q;
        i += 1;
    }
    return u1;
}
