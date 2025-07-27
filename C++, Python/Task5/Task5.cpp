#define _USE_MATH_DEFINES
#include <iostream>
#include<cmath>
#include <random>

const double limit = M_PI_4;
const double CIRCLEAREA = 4 * M_PI;
const int SQUAREAREA = 16;

// Estimate the area of a circle by Monte-Carlo's method
// Circle radius = 2

double rnunif(void);

void rninit(unsigned long  iufir);

int main()
{
    rninit(1331);

    int N_Square, N_Circle;

    printf("%-3s|%10s|%15s|%15s|%12s|%13s|%29s|\n", "N_Square", "N_Circle", "relDel(M_PI_4)", "absDel(M_PI_4)", "absDelArea", "relDelArea", "Rate of convergence (const)");

    const char* preset = "%-8d|% 10d|% 14.5lf%%|% 15.5lf|% 12.5lf|% 12.5lf%%|% 29.6E|\n";
        
    for (N_Square = 1, N_Circle = 0; N_Square <= 1e6; ++N_Square) {
        double x = rnunif()*4 - 2, y = rnunif()*4 - 2;
        if (x * x + y * y < 4) ++N_Circle;

        if (N_Square == 1e2 || N_Square == 1e4 || N_Square == 1e6) {
            double rel = double(N_Circle) / N_Square;
            double absDel = fabs(limit - rel);
            double relDel = absDel / limit;
            double absArea = fabs(rel * SQUAREAREA);
            double diffArea = fabs(CIRCLEAREA - absArea);
            double relDiffArea = diffArea / CIRCLEAREA;
            double convConst = sqrt(N_Square) * diffArea;

            printf(preset, N_Square, N_Circle, relDel, absDel, diffArea, relDiffArea, convConst);
        }
    }
}

static unsigned long int iu = 0, iuhold = 0, mult = 663608941l;

void rnrest(void)
{
    rninit(iuhold);
}

void rnconst(unsigned long int multnew)
{
    int rest = multnew % 8;
    if ((rest != 5) && (rest != 3))
        mult = multnew - rest + 5;
    else
        mult = multnew;
}

unsigned long int rnlast(void)
{
    return (iu);
}

unsigned long int rnfirst(void)
{
    return (iuhold);
}


double rnunif(void)
{
    const double flt = 0.232830643654e-9;
    iu *= mult;
    return (flt * iu);
}

void rninit(unsigned long  iufir)
{
    iu = ((iufir % 2) ? iufir : iufir + 1);
    iuhold = iu;
}
