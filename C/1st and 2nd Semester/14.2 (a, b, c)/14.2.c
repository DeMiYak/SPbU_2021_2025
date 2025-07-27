/**
* Яковлев Денис Михайлович (С)
* Нахождение "промахов измерений в массиве"
* Ввод: массив из n элементов
* Вывод: результаты анализа массива и погрешность e
*/

/* 14.2 (a) */
#include<stdio.h>
#include"head.h"
#include<stdlib.h>

int main()
{
    size_t n;
    scanf("%ld", &n);
    double *a, *sum = 0;
    a = malloc(sizeof(double)*n);
    assigndbl(n, a, &sum);
    double *mar, *msq;
    analysearray(n, a, &mar, &msq, &sum);
    for(p = c, e = p + n; p < e; ++p) printf("%lf", *p);
}
