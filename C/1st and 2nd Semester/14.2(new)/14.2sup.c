#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"head.h"


/**
* Функция заполнения массива вещественных чисел
* посредством арифметики указателей
*/

void assignDbl(size_t length, double *array)
{
    double *arrayEnd = array + length;
    for(double *pointOne = array; pointOne < arrayEnd; ++pointOne){
        scanf("%lf", pointOne);
    }
}

/**
* Функция, определяющая значения среднего арифметического
* и несмещённой оценки среднеквадратичного отклонения
*/

void analyseArray(size_t length, double *array, double *meanArith, double *meanSq){
    double *arrayEnd = array + length, tempSum = 0, sum = 0;
    for(double *pointOne = array; pointOne < arrayEnd; ++pointOne) sum += *pointOne;
    *meanArith = (1.0/length)*sum;

    for(double *pointOne = array; pointOne != arrayEnd; ++pointOne)
        tempSum += ((*pointOne) - (*meanArith))*((*pointOne) - (*meanArith));
    *meanSq = sqrt((double) tempSum/(length - 1));
    printf("\n14.2(A):\nmeanArith = %lf\nmeanSq = %lf\n", *meanArith, *meanSq);
}

/**
* Функция-указатель, возвращающая ссылку
* на первый элемент в массиве, удовлетворяющий
* условиям задачи
*/
double *pointValue(size_t length, double *array, double x, double eps){
    double *arrayEnd = array + length;
    for(double *pointOne = array; pointOne < arrayEnd; ++ pointOne)
        if(*pointOne > x + eps || *pointOne < x - eps)
            return pointOne;
    return NULL;
}

/**
* Функция нахождения и вывода всех "промахов" в массиве
*/
void missAr(size_t length, double *array, double meanArith, double meanSq, double *pointValue(size_t, double *, double, double)){
    double *ptr = array, *arrayEnd = array + length, upNum = meanArith + meanSq, lowNum = meanArith - meanSq;
    printf("Upper threshold number = %lf\nLower threshold number = %lf\n\n", upNum, lowNum);
    while((ptr = pointValue(arrayEnd-ptr, ptr, meanArith, meanSq)) != NULL){
        //ptr = pointValue(arrayEnd-ptr, ptr, meanArith, meanSq);
        printf("%lf %p\n", *ptr, ptr);
        ptr += 1;
    }
}

/**
* Вывод элементов массива
*/
void printArDbl(size_t length, const double *array){
    const double *arrayEnd = array + length;
    for(const double *pointOne = array; pointOne < arrayEnd; ++pointOne) printf("%lf %p\n", *pointOne, pointOne);
}
