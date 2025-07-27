/**
* Яковлев Денис Михайлович(С)
* Нахождение строки с максимальной суммой в двумерном массиве
* Ввод: двумерный массив а[n][m], длина и ширина n и m соответственно
* Вывод: номер строки с максимальной суммой
*/



#include<stdio.h>
#include"s.h"


int main()
{
    size_t n, m;
    scanf("%d%d", &n, &m);
    double a[BUFFER_ARRAY][BUFFER_ARRAY];
    twodimarray(a, n, m);
    printf("%d", maxsumline(a, n, m) + 1);
}
