/**
* Яковлев Денис Михайлович (С)
* Нахождение минимума и числа цифр у последовательности
* Входные данные: параметр i и целое а, образующее последовательность
* Вывод: минимум последовательности и (опционально) число элементов
* в последовательности
*/

#include<stdio.h>
#include"one.h"

int main()
{
    int a, *k;
    printf("Enter stop number: ");
    scanf("%d", &a);
    printf("Enter numbers (enter %d to stop)", a);
    printf("min = %d\n", minarray(a, &k));
    if(k != NULL) printf("k = %d", k);
}

// +
