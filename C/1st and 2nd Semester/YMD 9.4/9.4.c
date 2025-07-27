/**
* Я вам запрещаю использовать буквы
*
*
*
*/

#include<stdio.h>
#include<math.h>
#include<locale.h>

enum QuadStatus {ERROR, TWO_ROOTS, ONE_ROOT, ANY_NUMBER, NO_ROOTS, TWO_COMPLEX_ROOTS};
/* int {-120, -119, ..., 0 , 1, 2}; */
enum QuadStatus QuadFunc(double a, double b, double c, double *root1, double *root2){
    if(a != a || b != b || c != c || a == 1.0/0.0 || a == -1.0/0.0 || b == 1.0/0.0 || b == -1.0/0.0 || c == 1.0/0.0 || c == -1.0/0.0){
        return ERROR;
    } else if (a == 0){
        if (b == 0){
            if (c == 0){
                return ANY_NUMBER;
            } else return NO_ROOTS;
        } else {
            if (root1 != NULL && root2 != NULL) *root1 = *root2 = -1*c/b;
            return ONE_ROOT;
        }
    } else {
        double discr = b*b - 4*a*c;
        if (discr > 0){
            if (root1 != NULL) *root1 = (-1*b - sqrt(discr))/(2*a);
            if (root2 != NULL) *root2 = (-1*b + sqrt(discr))/(2*a);
            return TWO_ROOTS;
        } else if (discr == 0){
            if (root1 != NULL && root2 != NULL) *root1 = *root2 = -1*b/(2*a);
            return ONE_ROOT;
        } else return TWO_COMPLEX_ROOTS;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    double a1, a2, b1, b2, c1 ,c2, root1, root2;
    if (scanf("%lf%lf%lf%lf%lf%lf", &a1, &a2, &b1, &b2, &c1, &c2) != 6){
        printf("Invalid input\n");
        return 2;
    }
    printf("%lf %lf %lf\n", a1/a2, b1/b2, c1/c2);
    switch (QuadFunc(a1/a2, b1/b2, c1/c2, &root1, &root2))
    {
    case TWO_ROOTS:
        printf("Два вещественных корня: %lf ; %lf", root1, root2);
        break;
    case ONE_ROOT:
        printf("Один кратный корень: %lf", root1);
        break;
    case TWO_COMPLEX_ROOTS:
        printf("Два комплексных корня");
        break;
    case NO_ROOTS:
        printf("Нет решений");
        break;
    case ANY_NUMBER:
        printf("Любое вещественное число");
        break;
    case ERROR:
        printf("Корень не определён (ОШИБКА)");
        break;
    }

}
