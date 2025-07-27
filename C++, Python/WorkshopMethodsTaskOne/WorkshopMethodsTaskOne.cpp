// WorkshopMethodsTaskOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/// Задача Дирихле для эллиптического уравнения без смешанной производной 

//1.1 Метод простой итерации.

//1.2 Метод итерации с оптимальным параметром.

//1.3.Метод Зейделя.

//1.4.Метод верхней релаксации.

//1.5.Итерационный метод с чебышевским набором параметров.

//1.6.Попеременно треугольный итерационный метод.

//1.7.Попеременно - треугольный итерационный метод с чебышевским набором параметров.



//Нестационарные уравнения с двумя пространственными переменными

//2.1 Метод переменных направлений.

#include <iostream>
// Принтер для вывода результатов
#include"Printer.h"

// Резольвер как шаблон для методов
#include"Resolver.h"
// База методов
#include"BaseMethodGenerator.h"
// Чебышёвские параметры
#include"ChebyschevMethod.h"
// Попеременно-треугольный с чебышёвскими параметрами
#include"ChebyschevTriangleMethod.h"
// Простая итерация
#include"SimpleIterationMethod.h"
// Простая итерация с оптимальным параметром
#include"OptimalParameterMethod.h"
// Зайдель
#include"SeidelMethod.h"
// Верхняя релаксация (Nirvana)
#include"OverRelaxationMethod.h"
// Попеременно-треугольный
#include"TriangleMethod.h"
// Схема переменных направлений
#include"AlternateDirectionMethod.h"

double solution(double x, double y);

double solPolynomial(double x, double y);

/// <summary>
/// Перечислим основные требования к сдаче задачи, помимо
/// знания теоретических основ методов (некоторые совсем не понятны,
/// ну да ладно)
/// </summary>
/// <returns>
/// Список требований, исходя из
/// примера задачи 3 в Teams:
/// 1. Название метода, вариант задачи
/// 2. Число сегментов по оси X (N) и по оси Y (M)
/// 3. Степень точности eps
/// 4. Мера аппроксимации ||F-AU^*||
/// 5. Норма разности для U^0: ||F-AU^0||
/// 6. Число итераций iter_num
/// 7. Спектральный радиус матрицы H (rho_H) (как считать?)
/// 8. Квадрат спектрального радиуса
/// 9. Параметр тау
/// 
/// Затем идёт таблица в которой слева-направо указаны:
/// 1. Номер итерации k
/// 2. Мера аппроксимации при k
/// 3. ...
/// 4. Мера разности ||U^k-U^*||
/// 5. Относительная погрешность
/// 6. ||U^k-U^{k-1}||
/// 7. Апостериорная оценка
/// 8. Спектральный радиус матрицы (какой-то)
/// 
/// А также таблицы приближённого и точного решений
/// </returns>
int main()
{
    cout.precision(3);

    double lx = 1, ly = M_PI;
    //sizetype Nx = 15, My = 6;
    sizetype Nx = 6, My = 15;
    //sizetype Nx = 17, My = 5;
    double hx = lx / Nx, hy = ly / My;
    double xstar = 0, ystar = ly;
    SOLUTION SOL = SOL_0;
    RESOLVER resolver(lx, ly, Nx, My, SOL);
    // Вектор U со звёздочкой, будет использоваться для сравнения
    cout << endl << "U^* values: " << endl;
    vector<vector<double>> Ustar(Nx+1, vector<double>(My+1, 0));
    cout << fixed;
    for (int i = My; i >= 0; --i) {
        xstar = 0;
        for (int j = 0; j <= Nx; ++j) {
            //Ustar[j][i] = solPolynomial(xstar, ystar);
            Ustar[j][i] = solution(xstar, ystar);
            xstar += hx;
            cout << Ustar[j][i] << setw(7);
        }
        cout << endl;
        ystar -= hy;
    }
    cout << endl;

    // Проверка на корректный вывод
    resolver.PrintData();

    // Основной вывод.

    // 1. Метод простых итераций
    BaseMethodGenerator* sim = new SimpleIterationMethod(100, resolver);
    sim->PrintData();
    PRINTER printer(resolver, sim, Ustar);
    printer.PrintTable();
    delete sim;

    //1.2 Метод итерации с оптимальным параметром.
    BaseMethodGenerator* opm = new OptimalParameterMethod(100, resolver);
    PRINTER opm_printer(resolver, opm, Ustar);
    opm_printer.PrintTable();
    delete opm;
    //1.3.Метод Зейделя.
    BaseMethodGenerator* sdm = new SeidelMethod(100, resolver);
    PRINTER sdm_printer(resolver, sdm, Ustar);
    sdm_printer.PrintTable();
    delete sdm;
    //1.4.Метод верхней релаксации.
    BaseMethodGenerator* ovrm = new OverRelaxationMethod(100, resolver);
    PRINTER ovrm_printer(resolver, ovrm, Ustar);
    ovrm_printer.PrintTable();
    delete ovrm;
    //1.5.Итерационный метод с чебышевским набором параметров.
    BaseMethodGenerator* chm = new ChebyschevMethod(13, resolver);
    PRINTER chm_printer(resolver, chm, Ustar);
    chm_printer.PrintTable();
    delete chm;
    //1.6.Попеременно треугольный итерационный метод.
    BaseMethodGenerator* trm = new TriangleMethod(100, resolver);
    PRINTER trm_printer(resolver, trm, Ustar);
    trm_printer.PrintTable();
    delete trm;
    //1.7.Попеременно - треугольный итерационный метод с чебышевским набором параметров.
    BaseMethodGenerator* chtrm = new ChebyschevTriangleMethod(100, resolver);
    PRINTER chtrm_printer(resolver, chtrm, Ustar);
    chtrm_printer.PrintTable();
    delete chtrm;
    //2.1.Схема переменных направлений
    BaseMethodGenerator* adm = new AlternateDirectionMethod(100, resolver);
    PRINTER adm_printer(resolver, adm, Ustar);
    adm_printer.PrintTable();
    delete adm;
    std::cout << "\nHello World!\n";
}