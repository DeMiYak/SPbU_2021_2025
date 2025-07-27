/**
* Яковлев Денис Михайлович (С)
* Функция выделения подстроки из строки
* Ввод: строка с ограничением по числу знаков,
* два значения, образующие начало и конец подстроки
* Вывод: подстрока
*/


#include <stdio.h>
#include <string.h>
#include "head.h"

int main() {
    size_t len = 100;
    char s[] = "0123456789";
    //printf("s=");
    //gets(s);
    //int n,m;
    //printf("n=");
    //scanf("%i",&n);
    //printf("m=");
    //scanf("%i",&m);
    char newS[len];
    SubStr(s, newS, 7, -3);
    printf("|%s|\t%i\n", newS, strcmp(newS, "567"));
    SubStr(s, newS, -1000, -300000);
    printf("|%s|\t%i\n", newS, strcmp(newS, ""));
    SubStr(s, newS, 999, -1);
    printf("|%s|\t%i\n", newS, strcmp(newS, ""));
    SubStr(s, newS, -1, -3);
    printf("|%s|\t%i\n", newS, strcmp(newS, "789"));
    SubStr(s, newS, 3, 4);
    printf("|%s|\t%i\n", newS, strcmp(newS, "3456"));
    SubStr(s, newS, -2, 1000);
    printf("|%s|\t%i\n", newS, strcmp(newS, "89"));
    SubStr(s, newS, -3, -10);
    printf("|%s|\t%i\n", newS, strcmp(newS, "01234567"));
    SubStr(s, newS, 12, -4);
    printf("|%s|\t%i\n", newS, strcmp(newS, "9"));
    SubStr(s, newS, -3, 0);
    printf("|%s|\t%i\n", newS, strcmp(newS, "789"));
    return 0;
}
