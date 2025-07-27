/**
* Яковлев Денис Михайлович(С)
* Реализация функции численного интегрирования 13.2
* на разных промежутках и функциях
* Ввод: отрезок a, b; число точек n, погрешность eps
* Вывод: результаты подсчёта интегралов различных функций
*/


#include<stdio.h>
#include"functions.h"
#include"integrals.h"



int main()
{
    double l, r, eps, q, (*func)(double x, double *c);
    size_t n;
    printf("Enter n, l, r: ");
    scanf("%Iu%lf%lf", &n, &l, &r);
    printf("Enter eps: ");
    scanf("%lf", &eps);
    double c[5];
    int d;
    printf("1 = linear \n2 = square \n3 = cubic \n4 = exponential \n5 = logarithmic \n6 = sinus \n7 = cosin \nEnter from 1 to 7 to choose a function: ");
    scanf("%d", &d);
    switch (d)
    {
    case(1):
        func = &linear;
        assigner(2, c);
        break;
    case(2):
        func = &square;
        assigner(3, c);
        break;
    case(3):
        func = &cubic;
        assigner(4, c);
        break;
    case(4):
        func = &exponential;
        break;
    case(5):
        func = &logarithmic;
        break;
    case(6):
        func = &sinus;
        break;
    case(7):
        func = &cosin;
        break;
    default:
        break;
    }
    if(d < 1 || d > 7) return 0;
    //printf("%lf\n", func(2,c));
    printf("Integral = %lf\n", iterintegr(&avrectintegr, eps, l, r, n, func, &q, c));
    printf("Difference = %lf\n", q);
}
