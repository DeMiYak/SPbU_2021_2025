/**
*
*
*
*/

#include<stdio.h>
#include<math.h>

double fabs(double x);

double squaroot(double a, double e){
    double x0 = a, x1;
    if(a == a && e == e){
        x1 = 1/2*(x0 + a/x0);
        while(fabs((x1-x0)/x1) >= e){
            x0 = x1;
            x1 = 1/2*(x0 + a/x0);
        }
        return x1;
    } else return 0.0/0.0;
}

int main()
{
    double a, e;
    printf("a, e = ");
    scanf("%lf%lf", &a, &e);
    printf("squaroot(a, e) = %lf", squaroot(a, e));
    printf("%lf%lf", a, e);
}
