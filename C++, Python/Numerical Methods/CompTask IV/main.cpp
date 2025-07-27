/**
* Яковлев Денис Михайлович (С++)
*
* 02.05.2023 (21:15) - ...
*
* Решение задач по приближённому вычислению интеграла
* по квадратурным формулам (серия из трёх подзадач)
*
* 1-ая задача: приближённое вычисление интеграла по квадратурным формулам
*
*/



#include<iostream>
#include"Task4.2.h"
#include"Task4.3.h"
#include"RPN.h"
#include"Integrator.h"


int main(){
    _wsetlocale(LC_ALL, L"russian");

    string inputFormula;
    double startingPoint;
    double endingPoint;
    int segmentNum;

    getline(cin, inputFormula);

    Formula formula = Formula(inputFormula);

//    wcout << L"Введите значения:" << endl;
//
//    wcout << "A: ";
//    cin >> startingPoint;
//    wcout << "B: ";
//    cin >> endingPoint;
//    wcout << "m: ";
//    cin >> segmentNum;
//
//    Integrator integrator = Integrator(formula, startingPoint, endingPoint, segmentNum);

//    double integralResultJOne = integrator.JLeftRectangle();
//    wcout << endl << L"Левые прямоугольники: " << integralResultJOne << endl;

//    double integralResultJTwo = integrator.JRightRectangle();
//    wcout << endl << L"Правые прямоугольники: " << integralResultJTwo << endl;
//
//    double integralResultJThree = integrator.JMiddleRectangle();
//    wcout << endl << L"Средние прямоугольники: " << integralResultJThree << endl;
//
//    double integralResultJFour = integrator.JTrapezoid();
//    wcout << endl << L"Трапеция: " << integralResultJFour << endl;
//
//    double integralResultJFive = integrator.JSimpson();
//    wcout << endl << L"Симпсон: " << integralResultJFive << endl;
//
//    double integralResultJSix = integrator.JThreeEighths();
//    wcout << endl << L"Три восьмых: " << integralResultJSix << endl;


    double x;

    cin >> x;
    cout << endl;
    cout << formula.Evaluate(x);

    return 0;
}
