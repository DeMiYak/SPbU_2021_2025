#include <iostream>

#include "shape.h"

void print_commands() {
    std::cout << "\nList of commands:\n";
    std::cout << "  0) Exit\n";
    std::cout << "  1) Add shape\n";
    std::cout << "  2) Set shape location\n";
    std::cout << "  3) Set shape parameters\n";
    std::cout << "  4) Delete shape\n";
    std::cout << "  5) Print list of shapes\n";
    std::cout << "  6) Switch show/hide state of a shape\n";
}

int main()
{
    auto window = Window();
    window.update();
    std::size_t i1, i2;
    double d1, d2, d3;

    print_commands();
    std::cout << "Enter command: ";
    std::cin >> i1;
    while (i1) {
        switch (i1) {


        case 1:
            std::cout << "\nChoose a shape:\n";
            std::cout << "  1) Circle\n";
            std::cout << "  2) Rectangle\n";
            std::cin >> i1;
            switch (i1) {
                case 1:
                    std::cout << "\nEnter radius: ";
                    std::cin >> d1;
                    window.add_shape(new Circle(d1));
                    break;
                case 2:
                    std::cout << "\nEnter width and height: ";
                    std::cin >> d1 >> d2;
                    window.add_shape(new Rect(d1, d2));
                    break;
                default:
                    std::cout << "\nUnknown shape, please, try again.\n";
            }
            break;

        case 2:
            window.print_shapes();
            std::cout << "\nEnter shape number and coordinates: ";
            std::cin >> i1 >> d1 >> d2;
            window.set_shape_pos(i1, d1, d2);
            break;

        case 3:
            window.print_shapes();
            std::cout << "\nEnter shape number: ";
            std::cin >> i1;

            window.print_shape_params(i1);
            std::cout << "\nEnter parameter number and value: ";

            std::cin >> i2 >> d1;
            window.set_shape_param(i1, i2, d1);
            break;

        case 4:
            window.print_shapes();
            std::cout << "\nEnter shape number: ";
            std::cin >> i1;
            window.delete_shape(i1);
            std::cout << "\nShape " << i1 << " has been deleted\n";
            break;

        case 5:
            window.print_shapes();
            break;

        case 6:
            window.print_shapes();
            std::cout << "\nEnter shape number: ";
            std::cin >> i1;
            window.switch_shape_shown(i1);
            break;

        default:
            std::cout << "\nUnknown command, please, try again.\n";
        }


        window.update();
        print_commands();
        std::cout << "Enter command: ";
        std::cin >> i1;
    }


    window.close();
    return 0;
}
