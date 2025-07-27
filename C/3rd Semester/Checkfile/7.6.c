#include<stdio.h>
#include<math.h>

int main()
{
    double x, p, a, b;
    int h, i;
    printf("[a, b]: ");
    scanf("%lf%lf", &a, &b);
    printf("step h: ");
    scanf("%d", &h);
    printf("x, p: ");
    scanf("%lf%lf", &x, &p);
    for(i = 0; x <= b; ++i){
        if(a <= x && x <= b){
            if((x*x - p*p)/(x - p) - p == x){
                printf("%lf = %lf TRUE \n", (x*x - p*p)/(x - p) - p, x);
            } else{
                printf("%lf = %lf FALSE \n", (x*x - p*p)/(x - p) - p, x);
            }
        }
        x += h;
    }
}
