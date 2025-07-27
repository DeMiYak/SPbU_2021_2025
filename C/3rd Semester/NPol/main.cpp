#include <iostream>
#include "shape.hpp"

using namespace std;

int main() {
    Circle a = Circle(12);
    Circle b = a;
    cout << b << endl;

    Ellipse el  = Ellipse(12, 13);
    cout << el << endl;

    return 0;
}