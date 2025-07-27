#include"Task3.2.h"

double f2(double x)
{
    return exp(4.5*x);
}

double* buildup(double(*f)(double), size_t size, double a, double *h)
{
    double *temp = new double[2*size];
    double *ptr = temp;
    wcout << "x" << setw(27) << "f(x)" << endl;
    for(;ptr < (temp + size); ptr++, a+=*h)
    {
        *ptr = a;
        *(ptr + size) = f(a);
        wcout << *ptr << setw(24) << *(ptr+size) << endl;
    }
    return temp;
};

double* firstDer(double(*f)(double), double const* arg, size_t size, double h)
{
    double *temp = new double[2*size];
    double *ptr = temp;
    size_t t = 0;
    // 1 2 3 4
    // 4 3 2 1
    // 1 2 3 4 4 3 2 1
    *ptr = (-3*arg[size] + 4*arg[size + 1] - arg[size + 2])/(2*h);
    *(ptr + size) = fabs(4.5*f(arg[0]) - *ptr);
    ptr++; t++;
    for(; ptr < (temp + size - 1); ptr++, t++){
        *ptr = (arg[size + t + 1] - arg[size + t - 1])/(2*h);
        *(ptr + size) = fabs(4.5*f(arg[t]) - *ptr);
    }
    *ptr  = (3*arg[size + t] - 4*arg[t + size - 1] + arg[t + size - 2])/(2*h);
    *(ptr + size) = fabs(4.5*f(arg[t]) - *ptr);
    return temp;
}

double* secondDer(double(*f)(double), double const* arg, size_t size, double h)
{
    double *temp = new double[2*size];
    double *ptr = temp;
    double const *ptrTemp = arg;
    *ptr = (*(ptrTemp + size) - 2**(ptrTemp + size + 1) + *(ptrTemp + size + 2))/(h*h);
    *(ptr + size) = 0/0.;
    ptr++; ptrTemp++;
    for(; ptr < (temp + size - 1); ptr++, ptrTemp++){
        *ptr = (*(ptrTemp + size + 1) - 2**(ptrTemp + size) + *(ptrTemp + size - 1))/(h*h);
        *(ptr + size) = fabs(20.25*f(*ptrTemp) - *ptr);
    }
    *ptr  = (*(ptrTemp + size - 2) - 2**(ptrTemp + size - 1) + *(ptrTemp + size))/(h*h);
    *(ptr + size) = 0/0.;
    return temp;
}

void printTable(double *arg, double *fD, double *sD, size_t size)
{
    wcout << "x" << setw(27) << "f(x)" << setw(27) << L"f'(x)ЧД" << setw(27);
    wcout << L"|f'(x)ЧД - f'(x)Т|" << setw(27) << L"f''(x)ЧД" << setw(27) << L"|f''(x)ЧД - f''(x)Т|" << endl;
    double *tempA = arg;
    double *tempB = fD;
    double *tempC = sD;
    for(; tempA < (arg + size); tempA++, tempB++, tempC++)
    {
        wcout << *tempA << setw(24) << *(tempA + size) << setw(24) << *tempB << setw(24) << *(tempB + size);
        wcout << setw(24) << *tempC << setw(24) << *(tempC + size) << endl;
    }
}


void introTwo(){
    wcout << L"Задание №3.2\nНахождение производных таблично-заданной функции\n";
    wcout << L"по формулам численного дифференцирования" << endl << endl;
    wcout << L"Вариант 7: f(x) = exp(4.5*x)" << endl << endl;
}

void procedureThree(){

    size_t m;
    double a, h;
    int flag = 1;
    while(!(flag - 1))
    {
        wcout << L"Введите начало отрезка: "; cin >> a;
        wcout << L"Введите длину шага h (> 0): "; cin >> h;

        while(h<=0)
        {
            wcout << L"Ошибка: отрицательный шаг. Пожалуйста, введите положительное значение шага.";
            wcout << endl << "h = "; cin >> h;
        }
        wcout << L"Введите число аргументов: "; cin >> m;

        while(m <= 3)
        {
            wcout << L"Ошибка: недостаточное число аргументов. Пожалуйста, введите положительное значение более трёх.";
            wcout << endl << "(m + 1) = "; cin >> m;
        }

        double *arg = buildup(f2, m, a, &h);
        double *firstDerivative = firstDer(f2, arg, m, h);
        double *secondDerivative = secondDer(f2, arg, m, h);
        printTable(arg, firstDerivative, secondDerivative, m);
        wcout << endl << endl;
//        for(size_t tt = 0; tt < m; tt++)
//        {
//            wcout << 4.5*f2(arg[tt]) << setw(24) << firstDerivative[tt] << endl;
//        }

        wcout << L"Хотите начать снова? Введите 1, чтобы продолжить и 0, чтобы прекратить." << endl;
        cin >> flag;
    }

}

