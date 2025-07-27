/**
* Яковлев Денис Михайлович (С)
* Осуществление функций бинарного поиска и места
* Ввод: кол-во элементов, элементы массива, элемент сравнения
* Вывод: указатель на элемент в массиве, совпадающий с элементом сравнения (если есть)
* и порядковый номер для бинарного места
*/
#include<stdio.h>
#include"head.h"
#include<stdlib.h>


int compare(const int *a, const int *b)
{
    // printf("*a = %d, *b = %d\n", *a, *b);
    if(*a == *b) return 0;
    if(*a < *b) return -1;
    return 1;
}


int main()
{
    size_t length;
    printf("Length = ");
    scanf("%Iu", &length);
    int *arr;
    arr = malloc(sizeof(int)*length);
    int target;
    printf("target = ");
    scanf("%d", &target);
    arrFill(arr, length);
    int *ind = BinSearch(arr, &target, sizeof(int), length, compare);
    printf("14.3(A)\n");
    if(ind != NULL) printf("ind = %p\n*ind = %d", ind, *ind);
    else printf("Not found");
    printf("\n\n");

    ind = BinPlace(arr, &target, sizeof(int), length, compare);
    printf("\n14.3(B)\nind = %Iu", ind - arr);
    free(arr);
}
