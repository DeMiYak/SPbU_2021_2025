/**
* Яковлев Денис Михайлович (С)
* Обработка упорядочного массива данных посредством арифметики указателей
* Ввод: массив любого типа из n элементов
* Вывод: указатель на найденный элемент (а);
* индекс элемента, на который следует вставить искомый элемент (б)
*/


#include<stdio.h>
#include<stdlib.h>
#include"head.h"


int main()
{
    size_t n;
    scanf("%ld", &n);
    double *a;
    a = malloc(sizeof(double)*n);
    assigndbl(n, a);
    /* (a) */
    double x;
    scanf("%lf", &x);
    double *g = binsearch(n, a, x);
    printf("\n1 = %lf%p\t", *g ,g);
    /* (a) */
    //
    /* (b) */
    double y;
    scanf("%lf", &y);
    size_t k = binplace(n, a, y);
    printf("\n2 = %ld", k);
    /* (b) */
}
