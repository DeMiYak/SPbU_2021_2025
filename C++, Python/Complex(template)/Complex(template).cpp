// Complex(template).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
template<typename T>
class complex {
    T _re;
    T _im;
public:
    complex(T re = 0, T im = 0);
    complex(const complex<T>& a) : _re(a._re), _im(a._im) {};
    complex(complex<T>&& a) {

    }
    void set(T re = 0, T im = 0);
    complex<T>& add(const complex<T>& b);
    void print() {
        if (_im > 0) {
            std::cout << _re << " + " << _im << "i" << std::endl;
        }
        else std::cout << _re << " - " << -_im << "i" << std::endl;
    }
    complex& assign(const complex& b) {
        _re = b._re;
        _im = b._im;
        return *this;
    }

    T getIm() const;

    T getRe() const;
};

template<typename T>
complex<T>::complex(T re, T im) : _re(re), _im(im) {};

template<typename T>
T complex<T>::getRe() const{
    return _re;
}

template<typename T>
T complex<T>::getIm() const {
    return _im;
}

template<typename T>
complex<T>& complex<T>::add(const complex<T>& b) {
    _re += b._re;
    _im += b._im;
    return *this;
}

template<typename T>
complex<T> sum(const complex<T>& a, const complex<T>& b) {
    complex<T> c(a);
    return c.add(b);
}

template<typename T>
void complex<T>::set(T re, T im) {
    _re = re;
    _im = im;
}
int main()
{
    complex<double> a(1,2);
    a.add(a);
    a.print();

    complex<double> c = sum(a, a);
    c.print();
    c.set(5, -6);
    c.print();
}