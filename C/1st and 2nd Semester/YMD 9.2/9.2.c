/**
* Яковдев Денис Михайлович (С)
* Перестановка двух чисел в порядке убывания адресов
* Входные данные: произвольные a, b
* Вывод: Адресы a, b в порядке убывания
*/

#include<stdio.h>

void abba(int *a, int *b){
    if(*a < *b){
        int *tem = b;
        a = tem;
        b = a;
    }
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    abba(&a, &b);
    printf("%d : %d", a, b);
}
