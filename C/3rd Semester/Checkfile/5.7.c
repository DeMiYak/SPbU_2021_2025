/**
* Проверка нахождения точки с координатами (х, у) внутри прямоугольника, образованного точками с координатами (х1, у1) и (х2, у2)
* Вводные данные: шесть вещественных координат: х1, у1, х2, у2, х, у
* Вывод: Да, нет, на границе (погрешность)
*/

#include<stdio.h>
#include<locale.h>
#include<math.h>

int main()
{
    setlocale(LC_ALL, "rus");
    double eps;
    eps = 1e-6;
    double x1, y1, x2, y2;
    double x, y;
    double m1, m2, m3, m4;
    scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
    scanf("%lf%lf", &x, &y);
    m1 = x1 > x2 ? x1 : x2;
    m2 = x1 > x2 ? x2 : x1;
    m3 = y1 > y2 ? y1 : y2;
    m4 = y1 > y2 ? y2 : y1;
    if(m2 + eps < x && x < m1 - eps && m4 + eps < y && y < m3 - eps){
        printf("Да");
    } else if(m2 - eps < x || m1 + eps > x || m3 + eps < y || y < m4 - eps){
        printf("Нет");
    } else {
        printf("На границе (погрешность)");
    }
    return 0;
}
