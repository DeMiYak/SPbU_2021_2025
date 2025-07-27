/**
* ������� ����� ���������� (�)
* (������ ������ ���: 28.02.2023 8:50 - ...)
*
* �������� ������ �20
*
* ����:
* f(x) = sqrt(x) - 2*cos(pi*x/2),
* [A,B]=[0,4.5]
* eps = 1e-8
* N >= 2 (������, ���� ��������)
*
* ����� ������� ������:
* 1. ��������� ��������� ������ ��������� (1) �� ������� [A, B];
* 2. ��������� ������ ��������� (1) �� �������� �������� ����� ���� [ai, bi]
* a. ������� ����������� ������� (������� ��������);
* b. ������� ������� (������� �����������);
* c. ���������������� ������� �������;
* d. ������� �������
* � �������� ��������� eps>0 (eps � �������� ������).
*
*
*/



#include"Task1.h"
#include"Task2.h"
#include<math.h>
#include<assert.h>
#include<iostream>
#include<locale.h>

using namespace std;

int main()
{
    wcout.precision(12);
    wcout << fixed;
    _wsetlocale(LC_ALL, L"russian");

    wcout << "����: ����������� ������� ���������� ���������" << endl;
    wcout << L"f(x) = sqrt(x) - 2*cos(pi*x/2)" << endl;
    //double A = 0, B = 4.5;
    //double eps = 1e-8;
    double A, B;
    double eps;
    size_t N;


    /* 0. Entering data and checking-in */
    wcout << "A = ";cin >> A;
    wcout << "B = ";cin >> B;
    wcout << "eps = ";cin >> eps;
    wcout << "N = "; cin >> N; wcout << endl;
    assert(N>=2 || eps>0);

    /* 1. Decoupling roots on [A, B] */

    double h = (B-A)/N;

    // 1.1 Bisection Method
    wcout << '\n' << '\n' << "����� ��������: " << endl;
    BiSect(A, B, h, eps, f);

    // 1.2 Tangent Method
    wcout << '\n' << '\n' << "����� �������: " << endl;
    NewtonApprox(A, B, h, eps, f, fi);


    // 1.3 Modified Tangent Method (MoTangeM)
    wcout << '\n' << '\n' << "���������������� ����� �������: " << endl;
    ModNewtonApprox(A, B, h, eps, f, df);


    // 1.4 Secant Method
    wcout << '\n' << '\n' << "����� �������: " << endl;
    SecantApprox(A, B, h, eps, f, secf);
}
