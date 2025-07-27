/*
Класс "вектор над полем T^n", где T - некоторый шаблонный тип (в первом приближении - double или int).
Обеспечить необходимыми конструкторами, операциями (сложение, скалярное произведение, умножение на число, сравнение),
методами (норма), выбрасывание исключений и др. STL не использовать.
*/

#include<iostream>
#include"constructor.h"
using namespace std;

int main()
{
    double _a1, _a2;

    cout << "Enter the length of v: ";
    cin >> _a1;

    cout << "Enter the length of u: ";
    cin >> _a2;

    array<double> v(_a1), u(_a2);

    cout << "Enter coordinates of v: ";
    cin >> v;

    cout << "Enter coordinates of u: ";
    cin >> u;


    cout << "v: "<< v << ' ' << "u: " << u << endl;


    array<double> a3 = v, a4 = u;
    cout << a3 << a4 << v << endl;


    cout << v << ' ' << 4*v << v*4 << v << endl;
    double sc = v*u;
    cout << sc << endl;
    cout << (v*=4) << v << endl;
    return 0;
}
