#include<stdio.h>
#include"head.h"
#include<math.h>
#include<stddef.h>

/**
* Функция заполнения массива вещественных чисел
* посредством арифметики указателей
*/
void assignDbl(size_t length, double *arrayPoint, double *sum){
    double *pointOne, *pointTwo;
    for(pointOne = arrayPoint, pointTwo = arrayPoint + length; pointOne < pointTwo; ++pointOne){
        scanf("%lf", pointOne);
        *sum += *pointOne;
    }
}

/**
* Функция, определяющая значения среднего арифметического
* и несмещённой оценки среднеквадратичного отклонения
*/
void analyseArray(size_t length, double *pointArray, double *meanArith, double *meanSq, double *sum){
    *meanArith = (1.0/length)*(*sum);
    double *pointOne, *pointTwo, tempSum = 0;
    for(pointOne = pointArray, pointTwo = pointOne + length; pointOne < pointTwo; ++pointOne){
        tempSum += ((*pointOne) - (*meanArith))*((*pointOne) - (*meanArith));
    }
    *meanSq = sqrt((double) tempSum/(length-1));
}

/**
* Функция-указатель, возвращающая ссылку
* на первый элемент в массиве, удовлетворяющий
* условиям задачи
*/
double *pointValue(size_t length, double *arrayPoint, double x, double eps, size_t newLength){
    double *pointOne, *pointTwo;
    for(pointOne = arrayPoint + (newLength - 1), pointTwo = arrayPoint + length; pointOne < pointTwo; ++pointOne)
    {
        if(*pointOne > x + eps || *pointOne < x - eps){
            return pointOne;
        }
    }
    return NULL;
}

/**
* Функция нахождения и вывода всех "промахов" в массиве
*/
void missAr(size_t length, double *arrayPoint, double *meanArith, double *meanSq){
    double *pointOne, *pointTwo;
    printf("mar = %lf\nmsq = %lf\nUpper threshold value = %lf\nLower threshold value = %lf\n", *meanArith, *meanSq, *meanArith + *meanSq, *meanArith - *meanSq);
    for(pointOne = arrayPoint, pointTwo = pointOne + length; pointOne < pointTwo; ++pointOne){
        if(*pointOne > *meanArith + *meanSq || *pointOne < *meanArith - *meanSq)
            printf("%lf %d\t\n", *pointOne, pointOne - arrayPoint);
    }
}

/**
* Вывод элементов массива
*/
void printArDbl(size_t newLength, const double *arrayPoint){
    const double *pointOne;
    for(pointOne = arrayPoint; pointOne < arrayPoint + newLength; ++pointOne) printf("%lf %p\t\n", *pointOne, pointOne);
}
