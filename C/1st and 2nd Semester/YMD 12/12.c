/**
* Яковлев Денис Михайлович (С)
* Создание функций ввода элементов массива
* Ввод: i - кол-во элементов массива, набор элементов
* Вывод: массив вещественных или целых чисел
*/

#include<stdio.h>
#include"re.h"

int main()
{
    size_t n;
    printf("Set the length of the xy-arrays: ");
    scanf("%d", &n);
    int x[n];
    arrayint(x, n);
    for(int b = 0; b < n; ++b) printf("%i\n", x[b]);
}
