/**
* Яковлев Денис Михайлович (С)
* Построение прямоугольника из "*" через внешнюю границу
* Входные данные: m, n - ширина и длина прямоугольника, d - толщина
* Вывод: прямоугольник из "*"
*/


#include<stdio.h>

void ramka(int a, int b, int c){
    for(int r1 = 1; r1 <= a; r1++){
        if((r1 <= c) || (r1 > a-c)){
                for(int r2 = 1; r2 <= b; r2++){
                    printf("*");
                }
        } else{
            for(int r2 = 1; r2 <= b; r2++){
                    if((r2 <= c) || (r2 > b-c)){
                        printf("*");
                    } else{
                    printf(" ");
                }
        }
        }
        printf("\n");
}
}

int main()
{
    int m, n, d;
    printf("m, n, d: ");
    scanf("%d%d%d", &m, &n, &d);
    ramka(m, n, d);
}
