#include<stdio.h>
#include<math.h>
// Line
void findabLine(double xy, double xx, double xi, double yi, size_t n, double* a, double* b){
    double d = xx*n - xi*xi; // Детерминант (замечание: не равен 0 при n >= 2)
    *b = (xx*yi - xy*xi)/d;
    *a = (xy*n - xi*yi)/d;
}

void deltaCalcLine(double dela, double delb, size_t n, double *delta, double *wrvala, double *wrvalb, double *wrvaleq){
    for(int k = 1; k <= n; ++k) *delta += (dela*k + delb)*(dela*k + delb);
    *wrvala += dela*dela;   // Квадрат разности коэффициентов а
    *wrvalb += delb*delb;   // Квадрат разности коэффициентов b
    *wrvaleq += *delta;     // Среднеквадратическая сумма разностей нового и старого линейных уравнений
};

void getFullAnswerLine(double delta, double dela, double delb, double anew, double bnew){
    printf("New coefficients: anew = %.10lf, bnew = %.10lf\n", anew, bnew);                                                     // Вывод новых коэффициентов
    printf("Delta = %.10lf\n", delta);                                                                                          // Вывод средней арифметической суммы квадратов разности
    printf("Square difference of anew and a, bnew and b: delta of a's = %.10lf, delta of b's = %.10lf\n", dela*dela, delb*delb);// Вывод квадрата разницы новых и старых коэффициентов
    printf("//\n\n");
}

// Square
void findabSquare(double x2yC, double xxC, double xx2C, double xyC, double x2x2C, double *a, double *b)
{
    double det = x2x2C*xxC - pow(xx2C, 2);
    *a = (x2yC*xxC - xx2C*xyC)/det;
    *b = (x2x2C*xyC - x2yC*xx2C)/det;
}

void deltaCalcSquare(double dela, double delb, double delc, size_t n, double *delta, double *wrvala, double *wrvalb, double *wrvalc, double *wrvaleq)
{
    for(int k = 1; k <= n; ++k) *delta += pow(dela*k*k + delb*k + delc, 2);
    *wrvala += dela*dela;
    *wrvalb += delb*delb;
    *wrvalc += delc*delc;
    *wrvaleq += *delta;
}

void getFullAnswerSquare(double delta, double dela, double delb, double delc, double anew, double bnew, double cnew)
{
    printf("New coefficients: anew = %.10lf, bnew = %.10lf, cnew = %.10lf\n", anew, bnew, cnew);
    printf("Delta = %.10lf\n", delta);
    printf("Square difference of anew and a, bnew and b, cnew and c: delta a's = %.10lf, delta of b's = %.10lf, delta of c's = %.10lf\n", dela*dela, delb*delb, delc*delc);
    printf("//\n\n");
}

void findabcQ(double a, double b, size_t n, double *aQ, double *bQ, double *cQ)
{
    double det = n*(n-2)*(n-1)/4;
    *aQ = (double) (n-1)/det;
    *bQ = a - *aQ*(n+1);
    *cQ = b + *aQ*n;
}

int cmp(const double *a, const double *b)
{
    if(*a > *b) return 1;
    if(*a == *b) return 0;
    return -1;
}
