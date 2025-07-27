#include "math2_test.h"
#include <iostream>
#include <assert.h>
using namespace std;
/*
void assert_test_sign()
{

    assert(sign(1.0/0.0)  == 1);
    assert(sign(5)        == 1);
    assert(sign(1)        == 1);
    assert(sign(0.5)      == 1);
    assert(sign(0.0/0.0)  != sign(0.0/0.0));
    assert(sign(0)        == 0);
    assert(sign(-1.0)     == -1);
    assert(sign(-1.0/0.0) == -1);
    assert(sign(-1e10)    == -1);
    cout << "Success\n";

}
*/


void test_sign()
{

    EXCEPT_EQ(sign(1.0/0.0),  1);
    EXCEPT_EQ(sign(5),        1);
    EXCEPT_EQ(sign(1),        1);
    EXCEPT_EQ(sign(0.5),      1);
    EXCEPT_NAN(sign(0.0/0.0));
    EXCEPT_EQ(sign(0),         0);
    EXCEPT_EQ(sign(-1.0),     -1);
    EXCEPT_EQ(sign(-1.0/0.0), -1);
    EXCEPT_EQ(sign(-1e10),    -1);
    cout << "sign: end\n";
}

void test_sqrt()
{

    EXCEPT_EQ(sqrt(1.0/0.0, 1e-5),     1.0/0.0);
    EXCEPT_APPR(sqrt(5, 1e-5)*sqrt(5, 1e-5), 5.0, 1e-5);
    EXCEPT_APPR(sqrt(1, 1e-5)*sqrt(1, 1e-5), 1.0, 1e-5);
    EXCEPT_APPR(sqrt(0.5, 1e-5)*sqrt(0.5, 1e-5), 0.5, 1e-5);
    EXCEPT_APPR(sqrt(1e-4, 1e-5)*sqrt(1e-4, 1e-5), 1e-4, 1e-5);
    EXCEPT_EQ(sqrt(0, 1e-5),         0);
    EXCEPT_NAN(sqrt(-1.0, 1e-5));
    EXCEPT_NAN(sqrt(-1.0/0.0, 1e-5));
    EXCEPT_NAN(sqrt(-1.0/0.0, 1e-5));
    EXCEPT_NAN(sqrt(0.0/0.0, 1e-5));
    EXCEPT_NAN(sqrt(1, 0));
    EXCEPT_NAN(sqrt(1, -1));
    cout << "sqrt: end\n";
}


/*

void test_sign()
{
    double x, y;

    x = 1.0/0.0;  y = sign(x); cout << x << "\t-> " << y << "\t" << (y == 1 ? "YES" : "NO") << endl;
    x = 5.0;      y = sign(x); cout << x << "\t-> " << y << "\t" << (y == 1 ? "YES" : "NO") << endl;
    x = 1.0;      y = sign(x); cout << x << "\t-> " << y << "\t" << (y == 1 ? "YES" : "NO") << endl;
    x = 0.5;      y = sign(x); cout << x << "\t-> " << y << "\t" << (y == 1 ? "YES" : "NO") << endl;
    x = 0.0;      y = sign(x); cout << x << "\t-> " << y << "\t" << (y == 0 ? "YES" : "NO") << endl;
    x = -1.0;     y = sign(x); cout << x << "\t-> " << y << "\t" << (y == -1 ? "YES" : "NO") << endl;
    x = -1.0/0.0; y = sign(x); cout << x << "\t-> " << y << "\t" << (y == -1 ? "YES" : "NO") << endl;
    x = -1e10;    y = sign(x); cout << x << "\t-> " << y << "\t" << (y == -1 ? "YES" : "NO") << endl;
    x = 0.0/0.0;  y = sign(x); cout << x << "\t-> " << y << "\t" << (y != y ? "YES" : "NO") << endl;


}
*/
