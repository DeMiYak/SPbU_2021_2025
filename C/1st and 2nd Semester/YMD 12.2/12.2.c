/**
* Яковлев Денис Михайлович (С)
* Определение числа изменений знака элементов
* в массиве ненулевых целочисленных значений
* Ввод: длина массива i, целочисленные значения a
* Вывод: k - число знакоперемен
*/


#include<stdio.h>
#include"sip.h"

int main()
{
    size_t n;
    printf("Set the length of the x-array: ");
    scanf("%d", &n);
    int x[n];
    arrayint(x, n);
    printf("%d", arrayintcountk(x, n));
}

// +
