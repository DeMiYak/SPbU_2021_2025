/**
* Яковлев Денис Михайлович (С)
* Удаление чётных (нечётных) элементов массива через смещение элементов
* Ввод: n - количество элементов массива
* Вывод: массив, состоящий из нечётных (чётных) элементов
*/


#include<stdio.h>
#include"pp.h"
#include<stdlib.h>


int main()
{
    size_t n;
    printf("Set the length of the x-array: ");
    scanf("%d", &n);
    int x[n];
    arrayint(x, n);
    printf("\n%d\n", arrayintcountk(x, n));
    for(size_t i = 0; i < n; i++) printf("%d\t", x[i]);
}

