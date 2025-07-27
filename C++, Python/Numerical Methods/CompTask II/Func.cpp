#include<math.h>
#include<iostream>

using namespace std;

double f(double x)
{
    return exp(-x) - x*x/2;
};

double productValue(double *arg, size_t size, double x, double c)
{
    double value = 1; double* ptr = arg;
    for(;ptr < (arg + size); ptr++) {if(c!=*ptr) value *= (x-*ptr);}
    // cout << "value: " <<  value << endl;
    return value;
}

double* buildup(double(*f)(double), size_t size, double a, double b)
{
    double *temp = new double[2*size];
    double *ptr = temp;
    double h;
    if(size==1) h = (a+b)/2;
    else h = (b-a)/(size-1);
    double x = a;
    wcout << "x  " << "f(x)" << endl;
    for(;ptr < (temp + size); ptr++, x+=h)
    {
        *ptr = x;
        *(ptr + size) = f(x);
        wcout << *ptr << "  " << *(ptr+size) << endl;
    }
    return temp;
};

void sortTable(double *arg, size_t size, size_t deg, double x, void (*fnc1)(double*, double*, size_t, size_t), void (*fnc2)(double*, double*, size_t))
{

    double temp[size];
    for(size_t i = 0; i < size; i++) temp[i]=fabs(x-arg[i]);
    fnc1(temp, arg, size, deg);
    fnc2(temp, arg, size);
};

void sortArray(double *temp, double *arg, size_t size, size_t deg)
{
    for(size_t i = 0; i < deg; i++)
    {
        size_t min = i;
        for(size_t j = i + 1; j < size; j++)
        {
            if(temp[j] < temp[min]) min = j;
        }
        if(min!=i)
        {
            double temp1 = temp[min], temp2 = arg[min], temp3 = arg[min+size];
            temp[min] = temp[i];
            temp[i] = temp1;
            arg[min] = arg[i];
            arg[i] = temp2;
            arg[min+size] = arg[i+size];
            arg[i+size] = temp3;
        }
    }
};

void printArray(double *tmp, double *temp, size_t size)
{
    double *ptr = temp;
    double *val = tmp;
    wcout << "#   " << "x   " << "f(x)" << endl;
    for(;ptr < (temp + size); ptr++, val++)
    {
        wcout << *val << "   " << *ptr << "   " << *(ptr + size) << endl;

    }
}
