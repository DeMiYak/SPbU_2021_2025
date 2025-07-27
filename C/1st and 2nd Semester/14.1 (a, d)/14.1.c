/**
* Яковлев Денис Михайлович (С)
* Функции обработки и анализа одномерных массивов посредством арифметики указателей
* Ввод: массив а с n элементами
* Вывод: элементы сформированного посредством арифметики указателей
*/

/**
* 14.1(a)
* Ввод с клавиатуры и вывод на экран массивов
* целых и вещественных чисел заданной пользователем длины

#include<stdio.h>
#include"head.h"
#include<stdlib.h>

int main()
{
    size_t n;
    scanf("%Iu", &n);
    double *a;
    a = malloc(sizeof(double)*n);
    //
    assigndbl(n, a);
    //
    printardbl(n, a);
    //
    free(a);
}
*/


/**
* 14.1 (d)
* Удаление всех чётных или нечётных элементов из массива целых чисел
*/

#include<stdio.h>
#include"head.h"
#include<stdlib.h>

int main()
{
    size_t n;
    scanf("%Iu", &n);
    int *a;
    a = malloc(sizeof(int)*n);
    assignint(n, a);
    //
    size_t k = pickeven(n, a);
    printarint(k, a);
    free(a);
}
