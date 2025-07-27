// statvirtual.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// Создать классы с наследованиями так, чтобы:
// - для любого типа есть счётчик (static)
// - интерфейс (класс с virtual функциями)
// - классы-наследники выводить area, name, counter
// - пример вывода: "I'm a rectangle #2 of area 2 "

// Добавить:
// 1. функцию печати внешнюю
// 2. упорядочение по функции, которой параметр сортировки
// 3. печать отсортированного массива

// Замечания 2:
// 1. Полиморфизм функции print()
// 2. virtual ~Shape() в Shape, все деструкторы наследников
// автоматически станут virtual (без указания)
// 3. Объяснить inline static
// 4. перестроить virtual char*... -> virtual const char*...
//

#include<iostream>

class Shape {
protected:
    int counter;
public:
    void print();
    virtual double area() const = 0;
    virtual const char* name() = 0;
    virtual ~Shape();
};

void Shape::print() {
    std::cout << "I'm a " << name() << " #" << counter << " of S: " << area() << std::endl;
}

Shape::~Shape()
{
    counter = 0;
}

class Rectangle : public Shape {
public:
    Rectangle(double _a = 0, double _b = 0) : a(_a), b(_b) { counter = rect_c++; };
    virtual double area() const override {
        return a * b;
    }
    virtual const char* name() override{
        return "rectangle";
    }
    ~Rectangle() { a = 0; b = 0; --rect_c; }
private:
    double a, b;
    inline static int rect_c = 1;
};

class Circle : public Shape {
public:
    Circle(double _r = 0) : r(_r) { counter = circ_c++; };
    virtual double area() const override {
        return r * r * 3.1415;
    }
    virtual const char* name() override{
        return "circle";
    }
    ~Circle() { r = 0; --circ_c; }
private:
    double r;
    inline static int circ_c = 1;
};

void print(Shape** s, int k) {
    for (int i = 0; i < k; ++i) {
        s[i]->print();
    }
}

int cmpArea(Shape* a, Shape* b) {
    if (a->area() < b->area())
        return -1;
    if (a->area() > b->area())
        return 1;
    return 0;
}

void sort(Shape** s, int size, int cmp(Shape* a, Shape* b)) {
    for (int i = 1; i < size-1; ++i){
        for (int d = 0; d <= size-1-i; ++d) {
            if (cmp(s[d], s[d+1]) == 1) {
                Shape* temp;
                temp = s[d + 1];
                s[d + 1] = s[d];
                s[d] = temp;
            }
        }
    }
}

int main()
{
    int k = 8;
    Shape* s[8];
    s[0] = new Rectangle(3, 2);
    s[1] = new Circle(5);
    s[2] = new Rectangle(2, 1);
    s[3] = new Circle(3);
    s[4] = new Rectangle(10, 9);
    s[5] = new Rectangle(8, 7);
    s[6] = new Circle(4);
    s[7] = new Circle(2);
    std::cout << "Pre-sorted array: " << std::endl;
    print(s, k);
    sort(s, k, cmpArea);
    std::cout << std::endl << "Sorted array: " << std::endl;
    print(s, k);
    for (int i = 0; i < k; i++) {
        delete s[i];
    }
}