#define _USE_MATH_DEFINES

#include<cmath>
#include <random>
#include <ctime>
#include <iostream>
#include "R32M.H"

const double limit = M_PI_4;
const double CIRCLEAREA = 4 * M_PI;
const int SQUAREAREA = 16;

// Estimate the area of a circle by Monte-Carlo's method
// Circle radius = 2

int main() {
    rninit(1);

    int N_Square, N_Circle;

    printf("%-3s|%10s|%12s|%13s|\n", "N_Square", "N_Circle",
           "absDelArea", "relDelArea");

    const char *preset = "%-8d|% 10d|% 12.5lf|% 12.5lf%%|\n";

    for (int count = 100, N_Square = 1, N_Circle = 0; N_Square <= 1e6; ++N_Square) {
        double x = rnunif() * 4 - 2, y = rnunif() * 4 - 2;
//        std::cout << x << ' ' << y << std::endl;
        if (x * x + y * y < 4) ++N_Circle;

        if (N_Square == count) {
            double rel = double(N_Circle) / N_Square;
            double absArea = rel * SQUAREAREA;
            double diffArea = fabs(CIRCLEAREA - absArea);
            double relDiffArea = fabs(diffArea / CIRCLEAREA);
            /*double convConst = sqrt(N_Square) * diffArea;*/
            count *= 100;

            printf(preset, N_Square, N_Circle, diffArea, relDiffArea);
        }
    }
}