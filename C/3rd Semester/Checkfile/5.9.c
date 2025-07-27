/**
* Нахождение корней уравнения ax**2 + bx + c = 0 при произвольных a, b, c
* Вводные данные: вещественные числа a, b, c
* Вывод: от нуля корней до всего вещественного множества и комплексных чисел
*/

#include<stdio.h>
#include<locale.h>
#include<math.h>


int main()
{
    setlocale(LC_ALL, "rus");
    double a, b, c, sqrt(double x);
    printf("Введите коэффициенты а, b, c (через чёрточку /) ");
    scanf("%lf/%lf/%lf", &a, &b, &c);
    if(a==0){
        if(b==0){
            if(c==0){
                printf("Любое вещ.число");
            } else{
                printf("Нет решений");
            }
        } else{
            printf("x = %lf", -1*c/b);
        }
    } else{
        if(b==0){
            if(-1*c/a < 0){
                printf("x = +-i*%lf", sqrt(c/a));
            } else {
                printf("x = +-%lf", sqrt(c/a));
            }
        } else {
            double discr;
            discr = b*b - 4*a*c;
            if(discr < 0){
                printf("x = (%lf -+ i*%lf)/(2*%lf)", -1*b, sqrt(-1*discr), a);
            } else{
                double x1, x2;
                x1 = (-1*b - sqrt(discr))/(2*a);
                x2 = (-1*b + sqrt(discr))/(2*a);
                printf("x = %lf, %lf", x1, x2);
            }
        }
    }
}
