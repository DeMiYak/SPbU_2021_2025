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
    std::mt19937 gen(0);
    std::uniform_real_distribution<> distr(-2, 2);
    randInit(1333);

    int N_Square, N_Circle;

    printf("%-3s|%10s|%15s|%15s|%12s|%13s|%29s|\n", "N_Square", "N_Circle", "relDel(M_PI_4)", "absDel(M_PI_4)",
           "absDelArea", "relDelArea", "Rate of convergence (const)");

    const char *preset = "%-8d|% 10d|% 14.5lf%%|% 15.5lf|% 12.5lf|% 12.5lf%%|% 29.6lf|\n";

    for (N_Square = 0, N_Circle = 0; N_Square <= 1e6; ++N_Square) {
        double x = randNum() * 4 - 2, y = randNum() * 4 - 2;
//        std::cout << x << ' ' << y << std::endl;
        if (x * x + y * y < 4) ++N_Circle;

        if (N_Square == 1e2 || N_Square == 1e4 || N_Square == 1e6) {
            double rel = double(N_Circle) / N_Square;
            double absDel = limit - rel;
            double relDel = absDel / limit;
            double absArea = rel * SQUAREAREA;
            double diffArea = CIRCLEAREA - absArea;
            double relDiffArea = diffArea / CIRCLEAREA;
            double convConst = sqrt(N_Square) * diffArea;

            printf(preset, N_Square, N_Circle, relDel, absDel, diffArea, relDiffArea, convConst);
        }
    }
}