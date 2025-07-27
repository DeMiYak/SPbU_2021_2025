#include<iostream>
#include<math.h>
#include<locale.h>
using namespace std;

double f(double x)
{
    return sqrt(x) - 2*cos(M_PI_2*x);
}

double df(double x)
{
    return 1.0/(2*sqrt(x)) + M_PI*sin(M_PI_2*x);
}

double ddf(double x)
{
    return -1.0/(4*sqrt(x*x*x)) + M_PI*M_PI_2*cos(M_PI_2*x);
}

double fi(double x)
{
    return x - f(x)/df(x);
}

double dfi(double x)
{
    return f(x)*ddf(x)/(df(x)*df(x));
}

double secf(double x, double y)
{
    return x - f(x)/(f(x) - f(y))*(x - y);
}

void BiSect(double beg, double end, double h, double eps, double (*f)(double))
{
    size_t counter = 0;
    double x = beg, xNext = beg + h;
    while(x < end)
    {
        double a = x, b = xNext;
        double c, delta, fappr=(a+b)/2;
        size_t m = 0;
        if(f(a)*f(b)<=0)
        {
            counter++;
            while(b - a >= 2*eps){
                m++;
                c = (a+b)/2;
                if(f(b)*f(c)<=0)
                {
                    a = c;
                } else b = c;
            }
            delta = (b-a)/2;

            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}

void NewtonApprox(double beg, double end, double h, double eps, double (*f)(double), double (*fi)(double)){
    size_t counter = 0;
    double x = beg, xNext = beg + h;
    while(x < end)
    {
        double a = x, b = xNext;
        double c = (a+b)/2, delta, fappr=(a+b)/2;
        size_t m = 0;
        if(f(a)*f(b) <= 0){
            counter++;
            while(fabs(c - a) >= eps){
                m++;
                a = c;
                c = fi(c);
                if(c > xNext || c < x){
                    wcout << L"Между "<< x << L" и " << xNext << L": Ошибка: корень не может быть вычислен (попробуйте взять N побольше)" << endl;
                    m = 0;
                    break;
                }
            }
        }
        if(m){
            delta = fabs(c-a);

            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}

void ModNewtonApprox(double beg, double end, double h, double eps, double (*f)(double), double (*df)(double)){
    size_t counter = 0;
    double x = beg, xNext = beg + h;
    while(x < end)
    {
        double a = x, b = xNext;
        double c = (a+b)/2, delta, fappr=(a+b)/2;
        double cf = df(c);
        size_t m = 0;
        if(f(a)*f(b) <= 0){
            counter++;
            while(fabs(c - a) >= eps){
                m++;
                a = c;
                c = c - f(c)/cf;
                if(c > xNext || c < x){
                    wcout << L"Между "<< x << L" и " << xNext << L": Ошибка: корень не может быть вычислен (попробуйте взять N побольше)" << endl;
                    m = 0;
                    break;
                }
            }
        }
        if(m){
            delta = fabs(c-a);

            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}

void SecantApprox(double beg, double end, double h, double eps, double (*f)(double), double (*secf)(double, double)){
     size_t counter = 0;
     double x = beg, xNext = beg + h;
     while(x < end){
        double a = x, b = xNext;
        double c = secf(b, a), delta, fappr=secf(b, a);
        size_t m = 0;
        if(f(a)*f(b)<=0){
            counter++;
            while(fabs(c - b) >= eps){
                m++;
                a = b;
                b = c;
                c = secf(c, a);
                if(c < x || c > xNext){
                    wcout << L"Между "<< x << L" и " << xNext << L": Ошибка: корень не может быть вычислен (попробуйте взять N побольше)" << endl;
                    m = 0;
                    break;
                }
            }
        }
        if(m){
            delta = fabs(c - b);
            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}
