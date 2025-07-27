/**
* Яковлев Денис Михайлович (С)
* Нахождение НОД и НОК
* Входные данные: а и b - произвольные натуральные числа
* Вывод: НОД и НОК
*/


#include<stdio.h>
#include<math.h>
#include"support.h"

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n%d\n%d", iterEuclid(a, b), recuEuclid(a, b), NOK(a, b));
    return 0;
}
