#include<stdio.h>


int main()
{
    size_t n;
    scanf("%ld", &n);
    double *c;
    c = malloc(sizeof(double) * n);
    assigner(n, c);
    for(size_t i = 0; i < n; ++i) printf("%lf\n", c[i]);
    free(c);
}
