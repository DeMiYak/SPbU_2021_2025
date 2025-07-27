#include<stdio.h>
#include<math.h>

int main()
{
    int n = 0;
    double x;
    printf("x = ");
    scanf("%lf", &x);
    while(x != 0)
    {
        if(x < 1){
            x *= 10;
            n += floor(x);
            x -= floor(x);
        } else {
            int d;
            d = floor(x);
            n += d % 10;
            x /= 10;
            x = floor(x);
        }
        printf("n = %d, x = %lf \n", n, x);
    }
    printf("n = %d", n);
}
