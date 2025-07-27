/**
* Яковлев Денис Михайлович (С)
* Дана строка слов символов с разделителями.
* Найти частоту встречаемости и число появлений слов
* Ввод: строка слов символов
* Вывод: массив слов с двумя значениями для каждого слова n - число появлений, f - частота встречаемости
*/

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"

int main()
{
    // 0. Выделения памяти для динамических массивов
    size_t limit;
    printf("limit = ");
    scanf("%Iu", &limit);
    char *src = malloc(limit);
    char **cpy = (char **) malloc(sizeof(char *)*limit);
    // 1. Заполнение массива
    char temp;
    scanf("%c", &temp);
    // printf("%i\n", temp);
    arrFill(src, limit);
    size_t n = transferArr(src, cpy);
    // 2. Создание и заполнение дерева слов
    for(char **ptr = cpy; *ptr != NULL ; ++ptr)
        printf("%p %s\n", ptr, *ptr);
    node *data = createMap(cpy);
    printStr(data, &n);
    free(src);
    free(cpy);
}
