#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED

#include <iostream>
#include <cmath>

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
protected:
    friend std::ostream& operator<<(std::ostream& os, const Shape& s) {
        os << "Shape[area=" << s.area() << ", perimeter=" << s.perimeter() << "]";
        return os;
    }

    // virtual Shape& operator=(const Shape& s) = 0;
};

class Circle : public Shape {
public:
    Circle(double _r): r(_r) {};
    double area() const override {return M_PI * r * r;}
    double perimeter() const override {return 2 * M_PI * r;}

    Circle& operator=(const Circle& s) {
        r = s.r;
        return *this;
    }
private:
    double r;
};

class Ellipse : public Shape {
public:
    Ellipse(double _a, double _b): a(_a), b(_b) {};
    double area() const override {return M_PI * a * b;}
    double perimeter() const override {return 4 * (area() + a - b)/(a + b);}
private:
    double a, b;
};

class Rect : public Shape {
public:
    Rect(double _w, double _h): w(_w), h(_h) {};
    double area() const override {return w * h;}
    double perimeter() const override {return 2 * (w + h);}

    Rect& operator=(const Rect& s) {
        w = s.w;
        h = s.h;
        return *this;
    }
private:
    double w, h;
};

#endif // SHAPE_INCLUDED
