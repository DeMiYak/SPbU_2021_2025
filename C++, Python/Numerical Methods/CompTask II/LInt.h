#ifndef LINT_H_INCLUDED
#define LINT_H_INCLUDED

// Этап 2.1 Интерполяционный многочлен Лагранжа
#include"Func.h"
#include<math.h>

using namespace std;


void LagrangeInterpolation(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double))
{
    wcout << endl << L"Интерполяция Лагранжа:" << endl;
    double denominator;
    double numerator;
    double total = 0;
    double *ptr = arg;
    for(;ptr < (arg + deg); ptr++)
    {
        denominator = fnc(arg, deg, *ptr, *ptr);
        numerator = fnc(arg, deg, x, *ptr);
        double temp = *(ptr+size)/denominator;
        // cout << "denominator: " << denominator << endl;
        total += numerator*temp;
        // cout << "total: " << total << endl;
        cout << temp;
        for(double *ptrj = arg; ptrj < (arg + deg); ptrj++)
        {
            if(ptrj!=ptr) cout << "(x - " << *ptrj << ")";
        }
        cout << '+';
    }

    /*
    for(size_t i = 0; i < deg; i++)
    {
        double a = 0;
        for(double *ptrj = arg; ptrj <= (arg + i) ; ptrj++)
        {
            denominator = fnc(arg, i, *ptrj, *ptrj);
            a += *(ptrj + size)/denominator;
        }
        cout << a;
        for(size_t j = 0; j < i; j++) cout << "(x - " << arg[j] << ")";
        cout << '+';
    }
    */

    wcout << L"\nЗначение в точке интерполяции x = " << x << ": " << total << endl;
    wcout << L"Абсолютная погрешность: " << fabs(total - f(x)) << endl << endl;
}

#endif // LINT_H_INCLUDED
