/**
* Яковлев Денис Михайлович (С)
* Нахождение квадратного корня по итерационной формуле с погрешностью
* Входные данные: число а, для которого находится квадратный корень; число е - погрешность
* Вывод: квадратный корень от а с погрешностью е
*/

#include<stdio.h>
#include<math.h>

double squaroot(double a, double e){
    if (a == 0){
        return 0;
    }else if (a != a || e != e || a < 0 || e <= 0){
        return 0.0/0.0;
    } else if (a == 1.0/0.0 || e == 1.0/0.0 ){
        return 1.0/0.0;
    } else {
        double x0 = a, x1;
        x1 = 0.5*(x0 + a/x0);
        while (fabs((x1 - x0)/x1)>= e){
                x0 = x1;
                x1 = 0.5*(x0 + a/x0);
        }
        return x1;
    }
}

int main()
{
    double a, b, e;
    printf("a, b, e = ");
    scanf("%lf%lf%lf", &a, &b, &e);
    printf("squaroot(a/b, e) = %lf\n", squaroot(a/b, e));
    printf("%lf %lf", a, e);
}
