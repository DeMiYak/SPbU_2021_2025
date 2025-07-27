#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include<iostream>

using namespace std;

double f(double x);

double productValue(double *arg, size_t size, double x, double c);

double* buildup(double(*f)(double), size_t size, double a, double b);

void sortTable(double *arg, size_t size, size_t deg, double x, void (*fnc1)(double*, double*, size_t, size_t), void (*fnc2)(double*, double*, size_t));

void sortArray(double *temp, double *arg, size_t size, size_t deg);

void printArray(double *tmp, double *temp, size_t size);

#endif // FUNC_H_INCLUDED
