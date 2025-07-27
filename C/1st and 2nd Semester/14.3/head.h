#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

/**
* Функция заполнения массива вещественных чисел
* посредством арифметики указателей
*/
void assigndbl(size_t, double *);

/**
* Функция бинарного поиска, реализованная
* посредством арифметики указателей
*/
void *binsearch(size_t, double *, double);

/**
* Функция бинарного места, реализованная
* посредством арифметики указателей
*/
size_t binplace(size_t, double *, double);

#endif // HEAD_H_INCLUDED
