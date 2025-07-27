#include <iostream>
#include "String.h"

int main()
{
    cout << "Testing constructors" << endl;
    String a;
    cout << "a:" << a << endl;
    String b(5);
    cout << "b:" << b << endl;
    String c("vadim");
    cout << "c:" << c << endl;
    String d(c);
    cout << "d:" << d << endl;
    String e("danil");
    cout << "e:" << e << endl;
    String f(move(c));
    cout << "f:" << f << endl;
    cout << "c:" << c << endl;
    String g("");
    cout << "g:" << g << endl;

    cout << "Assignment testing" << endl;
    a = d;
    cout << "a:" << a << endl;
    c = d;
    cout << "c:" << c << endl;
    f = f;
    cout << "f:" << f << endl;
    c = move(a);
    cout << "c:" << c << endl;
    cout << "a:" << a << endl;
    d = move(d);
    cout << "d:" << d << endl;


    cout << "Addition testing" << endl;
    c += e;
    cout << "c:" << c << endl;
    a += c;
    cout << "a:" << a << endl;
    f += d;
    cout << "f:" << f << endl;
    f += g;
    cout << "f:" << f << endl;
    
    cout << "d + a:" << d + a << endl;
    cout << "f + e:" << f + e << endl;
    cout << "g + g:" << g + g << endl;
    cout << "g + e:" << g + e << endl;

    cout << "Indexing test" << endl;
    const String h("abcd");
    cout << "f[0]: " << f[0] << endl;
    f[0] = 'd';
    cout << "f[0]: " << f[0] << endl;
    cout << "d[4]: " << d[4] << endl;
    d[4] = 'p';
    cout << "d[4]: " << d[4] << endl;
    cout << "a[7]: " << a[7] << endl;
    cout << "h[0]: " << h[0] << endl;
    cout << "h[3]: " << h[3] << endl;

    cout << "Substring testing" << endl;
    cout << f(2, 40) << endl;
    cout << f(4, 6) << endl;
    cout << c(3, 3) << endl;
    cout << g(0, 0) << endl;

    cout << "Testing the input" << endl;
    cin >> g;
    cout << g;
}


