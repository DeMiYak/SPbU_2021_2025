/**
* Яковлев Денис Михайлович (С)
* Нахождение "промахов измерений в массиве"
* Ввод: массив из n элементов, погрешность e
* Вывод: результат анализа массива, дополнительные данные
*/

#include<stdio.h>
#include<assert.h>
#include<math.h>
#include<stdlib.h>
#include"head.h"


int main()
{
    size_t length;
    printf("length = ");
    scanf("%Iu", &length);
    double *array;
    //
    array = malloc(sizeof(double)*length);
    assignDbl(length, array);
    // A
    double meanArith, meanSq;
    analyseArray(length, array, &meanArith, &meanSq);
    // B
    printf("// \n\n14.2(B)\n");
    /*
    double x, eps;
    printf("\nx = ");
    scanf("%lf", &x);
    printf("\neps = ");
    scanf("%lf", &eps);
    double *point = pointValue(length, array, x, eps);
    if(point != NULL) printf("\nx' = %lf\npoint = %p\n", *point, point);
    else printf("\nNULL\n // \n");
    // C
    printf("\n14.2(C):\n");
    if(point != NULL) missAr(length, array, point, meanArith, meanSq);
    printf("// \n\n");
    */
    printf("\n\n14.2(C):\n");
    missAr(length, array, meanArith, meanSq, pointValue);
    printf("\n");
    printArDbl(length, array);
    free(array);
}
