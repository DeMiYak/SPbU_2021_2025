#ifndef SUP_H_INCLUDED
#define SUP_H_INCLUDED

/**
* Функция loadup находит суммы xn*xn, xn, yn, xn*yn, где n = 0, 1, ..., i - 1
* i - изначально заданное число координатных точек
*/
void loadup(double *xy, double *xx, double *xi, double *yi, int i, double x[], double y[]);

/**
* Функция arrayx заполняет массивы x, y посредством ручного ввода
* Вводится точка (x, y) через пробел
* (как сделать случайный шум, пока не знаю)
*/
void arrayx(double x[], double y[], int i);

/**
* Функция findsolution выводит на экран получившееся линейное приближение
* значения а и b рассчитаны по методу Крамера
*/
void findsolution(double xy, double xx, double xi, double yi, int i);

#endif // SUP_H_INCLUDED
