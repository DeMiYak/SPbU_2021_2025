#include <stdio.h>

double func(double x) {
    return x/2;
}

int main() {
    double a, b, h;
    char s[] = "---------------\n";
    scanf("%lf%lf%lf", &a, &b, &h);
    printf("%s|x     |y     |\n%s", s, s);
    for (double i = a; i <= b; i += h) {
        printf("|%.4lf|%.4lf|\n%s", i, func(i), s);
    }
}
