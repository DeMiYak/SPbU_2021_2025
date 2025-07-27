#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

/**
* Функция заполнения массива вещественных чисел
* посредством арифметики указателей
*/
void assigndbl(size_t, double *);

/**
* Функция заполнения массива целых чисел
* посредством арифметики указателей
*/
void assignint(size_t, int *);

/**
* Функция выбора чётного элемента
*/
size_t pickeven(size_t, int *);

/**
* Функция вывода целочисленного массива по k элементам
*/
void printarint(size_t, const int *);

/**
* Функция вывода массива вещественных чисел по k элементам
*/
void printardbl(size_t, const double *);

#endif // HEAD_H_INCLUDED
