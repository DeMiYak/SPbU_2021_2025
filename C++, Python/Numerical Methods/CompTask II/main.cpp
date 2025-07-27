/**
*
* Яковлев Денис Михайлович (С)
* (16.03.2023 11:16 - ...)
*
* Задача №2: Задача алгебраического интерполирования.
* Интерполяционный многочлен в форме Ньютона и в форме Лагранжа
*
*
* Вариант 7:
* f(x)=exp(-x) - x^2/2
*
* Входные данные:
* a = 0, b = 5, m + 1 = 26, n = 10
*
*
*/

#include"LInt.h"
#include"NInt.h"
#include"Func.h"
#include<locale.h>

using namespace std;

int main()
{

    wcout << fixed;
    wcout.precision(16);
    // Этап -1. Локализация
    _wsetlocale(LC_ALL, L"russian");

    // Этап 0. Подготовительный.
    double a, b;
    size_t m, n;
    double x;
    wcout << L"Задача алгебраического интерполирования:" << endl;
    wcout << L"Интерполяционный многочлен в форме Ньютона и в форме Лагранжа." << endl << endl;

    wcout << L"Вариант 7. Функция f(x) = eps(-x) - x^2/2" << endl << endl;

    wcout << L"Начало отрезка: "; cin >> a;
    wcout << L"Конец отрезка: "; cin >> b;
    while(b<=a)
    {
        wcout << endl << L"Ошибка: конец отрезка меньше-равен начала. Пожалуйста, введите число больше начала отрезка";
        wcout << endl << L"Конец отрезка: "; cin >> b;
    }

    wcout << L"Число аргументов: "; cin >> m;

    // Этап 0.5. Таблица значений
    // Замечание: так как m не изменяется, можно использовать статический массив.
    double* arg = buildup(&f, m, a, b);

    wcout << endl << L"Введите точку интерполяции х: "; cin >> x; wcout << endl;

    wcout << L"Степень интерполяционного многочлена (меньше числа аргументов): "; cin >> n; wcout << endl;
    while(n>=m)
    {
        wcout << endl << L"Ошибка: такого многочлена не существует. Пожалуйста, введите степень меньше числа аргументов: ";
        wcout << endl; cin >> n; wcout << endl;
    }

    // Этап 0.8. Сортировка таблицы
    sortTable(arg, m, n+1, x, &sortArray, &printArray);

    // Этап 1. Построение многочленов

    int p;
    size_t cmp = n + 1, cmpx = x+1;
    wcout << L"Нажмите 1, чтобы начать процесс интерполяции" << endl << L"Нажмите 0, чтобы выйти" << endl;
    wcout << endl; cin >> p;
    while(p!=0 && p!=1)
    {
            wcout << endl << L"Ошибка: неправильные значения. Пожалуйста, введите 0 или 1." << endl << endl;
            cin >> p;
    }

    while(p)
    {
        if(cmp!=n || cmpx!=x)
        {
            cmp = n;
            cmpx = x;
            LagrangeInterpolation(arg, m, n+1, x, &productValue, &f);
            NewtonInterpolation(arg, m, n+1, x, &productValue, &f);
        }
        else wcout << endl << L"Введена та же степень и точка интерполяционного многочлена. Пожалуйста, введите другие значения." << endl;

        wcout << endl << L"Нажмите 1, чтобы начать процесс интерполяции" << endl << L"Нажмите 0, чтобы выйти" << endl;
        wcout << endl; cin >> p;
        while(p!=0 && p!=1)
        {
            wcout << endl << L"Ошибка: неправильные значения. Пожалуйста, введите 0 или 1." << endl << endl;
            cin >> p;
        }
        if(p)
        {
            wcout << L"Введите точку интерполяции х: "; cin >> x; wcout << endl;
            wcout << L"Степень интерполяционного многочлена (меньше числа аргументов): "; cin >> n; wcout << endl;
            while(n>=m)
            {
                wcout << endl << L"Ошибка: такого многочлена не существует. Пожалуйста, введите степень меньше числа аргументов: ";
                wcout << endl; cin >> n; wcout << endl;
            }
            sortTable(arg, m, n+1, x, &sortArray, &printArray);
        }
    }
}

