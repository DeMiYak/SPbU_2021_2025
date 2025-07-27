#include <iostream>
#include"String.h"

int main()
{
    // 1
    cout << "1: Const char* construct and cout" << endl << endl;
    String a("123456789");
    cout << (a += a) << a;
    // 2
    cout << "2: Copy construct and +=" << endl << endl;
    String b(a), m;
    cout << b << (b+=m) << m;
    // 3
    cout << "3: Move construct and concatination 1" << endl << endl;
    String c(move(a));
    cout << c;
    cout << a;
    cout << (c += b += b += b);
    cout << b;
    // 4
    cout << '4' << endl << endl;
    String d("Nursery Rhymes");
    cout << d;
    // 5
    cout << "5: Comparison 1" << endl << endl;
    String e("Nursery Rhymes");
    cout << (d == e) << (d < e) << (d > e) << (d <= e) << (d >= e) << endl;
    cout << (b != c) << (b < c) << (b > c) << endl;
    cout << ((b + b += b) == c) << endl;
    // 6
    cout << "6: Operator=" << endl << endl;
    e = b;
    cout << e;
    e = d;
    cout << e << (d = e);
    // 7
    cout << "7: Operator()" << endl << endl;
    cout << e(2, 6) << e(6, 2) << e(3,3) << endl;
    // cout << e(1, 40); exits with 1;
    // 8
    cout << "8: Arithmetics 2" << endl << endl;
    char* word = e+d += b+d += d+b += b;
    cout << word << endl << b;
    cout << d << endl;
    // 9
    cout << "9: Index" << endl << endl;
    cout << d[(d < e)] + b[(b > c)];
    // cout << m[(m != e)] exits with 3;
    // 10 
    cout << endl << endl << "10: Arithmetics 3" << endl << endl;
    cout << (e = e += e + e += (e = e += e) += e + (e = e + e));
    // 11
    cout << endl << endl << "11: Initiation test" << endl << endl;
    String p(5);
    cout << (p += d + p) << endl;
    // 12
    cout << endl << endl << "12: Printing test" << endl << endl;
    String t;
    cin >> t;
    cout << t << endl;
}