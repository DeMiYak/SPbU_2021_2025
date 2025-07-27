#include <iostream>

using namespace std;

class A {
protected:
    int i;
public:
    A(int _i = 0) : i(_i) { cout << endl << "Aconstruct"; }
    A& operator=(const A& a) {
        i = a.i;
        cout << endl << "Aoperator=copy";
        return *this;
    }
    A& operator=(A&& a) {
        i = a.i;
        a.i = 0;
        cout << endl << "Aoperator=move";
        return *this;
    }
    A(const A& a) : i(a.i) { cout << endl << "Acopy"; }
    A(A&& a) : i(a.i) { a.i = 0; cout << endl << "Amove"; }
    ~A() { cout << endl << "Adestruct: " << i; i = 0; }

    void print() { cout << endl << "A: " << i; }
};

class B : public A {
protected:
    int j;
public:
    B(int _j = 0) : A(), j(_j) { cout << endl << "Bconstruct"; }
    B(int _j, int _i) : A(_i), j(_j) { cout << endl << "Bconstruct"; }
    B& operator=(const B& b) {
        A::operator=(b);
        j = b.j;
        cout << endl << "Boperator=copy";
        return *this;
    }
    B& operator=(B&& b){
        A::operator=(move(b));
        j = b.j;
        b.j = 0;
        cout << endl << "Boperator=move";
        return *this;
    }
    B(const B& b) : A(b), j(b.j) { cout << endl << "Bcopy"; }
    B(B&& b) : A(move(b)), j(b.j) { b.j = 0; cout << endl << "Bmove"; }
    ~B() { cout << endl << "Bdestruct: " << j; i = 0; j = 0; }

    void print() { cout << endl << "B: " << j; A::print(); };
};


int main()
{
    A a1;
    a1.print();
    B b1;
    b1.print();

    A a2(3);
    a2.print();
    B b2(4);
    b2.print();

    A a3(a2);
    a3.print();
    B b3(b2);
    b3.print();

    A a4;
    a4 = a3;
    a4.print();
    B b4;
    b4 = b3;
    b4.print();

    A a5(move(a4));
    a5.print();
    B b5(move(b4));
    b5.print();

    B b6(2, 3);
    b6.print();

    A a6;
    a6 = move(a3);
    a6.print();
    B b7;
    b7 = move(b3);
    b7.print();

}

// Отправить после пар