#ifndef TASK3_1_H_INCLUDED
#define TASK3_1_H_INCLUDED

#include<locale.h>
#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;


void LagrangeInterpolation(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double));

double LagrangeInterpolationVar(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double));

void NewtonInterpolation(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double));

double productValue(double *arg, size_t size, double x, double c);

double* buildup(double(*f)(double), size_t size, double a, double b);

void sortTable(double *arg, size_t size, size_t deg, double x, void (*fnc1)(double*, double*, size_t, size_t), void (*fnc2)(double*, double*, size_t));

void sortArray(double *temp, double *arg, size_t size, size_t deg);

void printArray(double *tmp, double *temp, size_t size);

double f(double x);

double df(double x);

double ddf(double x);

double fi(double x);

double dfi(double x);

double secf(double x, double y, double node, double* arg, size_t N);

void BiSect(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t));

void NewtonApprox(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double), double(*fi)(double, double));

void ModNewtonApprox(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t), double(*df)(double));

void SecantApprox(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t), double(*secf)(double, double, double, double*, size_t));

void introOne();

void swapColumns(double *arg, size_t size, double x);

void procedureOne();

void procedureTwo();

double fMod(double x, double node, double* arg, size_t N);

#endif // TASK3_1_H_INCLUDED
