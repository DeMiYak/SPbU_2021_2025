#include<stdio.h>

void fa(double *a, size_t n){
    for(size_t i = 0; i < n; ++i){
        scanf("%lf", &a[i]);
    }
}

size_t partition (double *a, size_t l, size_t r)
{
    size_t i = l, j = r;
    double x = a[(l + r)/2];

    while (i < j)
    {
        while(a[i] < x) i++;
        while(a[j] > x) j--;

        if(i < j)
        {
            double d;
            d = a[i];
            a[i] = a[j];
            a[j] = d;
            i++;
            j--;
        }
        for(size_t i = 0; i <= r; ++i) printf("%lf ", a[i]);
        printf("\n");
    }

    return a[i] >= x ? i : i+1;
}

int main()
{
    size_t n;
    scanf("%ld", &n);
    double a[n];
    fa(a, n);
    size_t e = partition(a, 0, n-1);
    printf("%ld\n%lf\n", e, a[e]);
    for(size_t i = 0; i < n; ++i) printf("%lf ", a[i]);
}
