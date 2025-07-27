#include <stdio.h>

#define pow2(x) ((x)*(x))

double func(double x, double p) {
    return (pow2(x) - pow2(p)) / (x - p) - p;
}

int main() {
    double a, b, p;
    double h;
    char s[] = "-------------------\n";
    scanf("%lf%lf%lf%lf", &a, &b, &h, &p);
    printf("%s|x       |y       |\n%s", s, s);

    for (double i = a; i <= b; i += h) {
        printf("| %.4le | %.4le |\n%s", i, func(i, p), s);
    }
}
