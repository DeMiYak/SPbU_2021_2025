//
// 1 C2
// 2 C2
// 3 =
// 4 C0
// 5 CC
// CC
// D
// =
// D
// 6 =
// 5. + i 4. 
// D
// D
// D

#include <iostream>

class complex {
    double _re;
    double _im;
public:
    complex(double re = 0, double im = 0) : _re(re), _im(im) {};
    complex(const complex& a) : _re(a._re), _im(a._im) {};
    complex(complex&& a) {
        
    }
    void set(double re = 0, double im = 0) {
        _re = re;
        _im = im;
    }
    complex& add(const complex& b) {
        _re += b._re;
        _im += b._im;
        return *this;
    }
    complex sum(const complex& b) {
        complex c(*this);
        return c.add(b);
    }
    void print() {
        if (_im > 0) {
            std::cout << _re << " + " << _im << "i" << std::endl;
        }
        else std::cout << _re << " - " << _im << "i" << std::endl;
    }
    complex& assign(const complex& b) {
        _re = b._re;
        _im = b._im;
        return *this;
    }

    double getIm() const{
        return _im;
    }

    double getRe() const{
        return _re;
    }
};

void print(const complex& a) {
    std::cout << a.getRe();
    if(a.getIm() > 0) {
        std::cout << " + " << a.getIm();
    }
    else {
        std::cout << " - " << a.getIm();
    }
    std::cout << "i" << std::endl;
}

complex sum(const complex& a, const complex& b) {
    complex c(a);
    return c.add(b);
}

struct node {
    int info;
    node* prev;
    node* next;
    void insert_after(node& nnew);
};

void node::insert_after(node& nnew) {
    nnew.prev = this;
    nnew.next = next;
    if(next) next->prev = &nnew;
    next = &nnew;
}

int main()
{
    complex a, b, c;
    a.set(1, 2);
    c.assign(b.assign(a)).print(); // assign(assign(c, b), a)
    a.print();
    b.print();
    c.add(b.add(a)).print(); // add(add(c, b), a)
    b.print();
    a.print();
    c.sum(b).print(); // sum(c, b)

}

//void complex::set(double re, double im) {
//    this->_re = re;
//    this->_im = im;
//}
//
//complex& complex::add(const complex& b) {
//    this->_re += b._re;
//    this->_im += b._im;
//    return *this;
//}
//
//complex complex::sum(const complex& a, const complex& b) {
//    complex c(a);
//    return c.add(b);
//}
//
//void complex::print() {
//    if (this->_im > 0) {
//        std::cout << this->_re << " + " << this->_im << "i" << std::endl;
//    }
//    else std::cout << this->_re << " - " << this->_im << "i" << std::endl;
//}
//
//complex& complex::assign(const complex& b) {
//    this->_re = b._re;
//    this->_im = b._im;
//    return *this;
//}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
