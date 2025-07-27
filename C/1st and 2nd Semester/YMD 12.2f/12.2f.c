/**
* Яковлев Денис Михайлович (С)
* Нахождение второго по величине элемента массива (по убыванию)
* Ввод: длина массива i, целочисленные значения a
* Вывод: k - второе по величине число
* (если max1 или max2 неопределены - выводится 0)
*/


#include<stdio.h>
#include"QQ.h"

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
