#include<stdio.h>

int main()
{
    double a, b;
    int h, k = 0, i;
    printf("[a, b]: ");
    scanf("%lf%lf", &a, &b);
    printf("step h: ");
    scanf("%d", &h);
    printf("f(x) = x**2 \n");
    for(i = 0; k*k <= b; ++i){
        if(a <= k*k && k*k <= b){
            printf("%lf <= [%d] <= %lf \n", a, k*k, b);
        }
        k += h;
    }
}
