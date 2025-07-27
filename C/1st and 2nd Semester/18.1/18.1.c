/**
* Яковлев Денис Михайлович (С)
* Дана строка слов символов, слова разделяются
* пробелами и знаками препинания. Разделители могут повторяться,
* могут встречаться в начале и конце строки. Преобразовать строку в массив слов.
* Примечание: создать копию строки в памяти, в ней, используя функция strtok,
* находить конец очередного слова, заменяя разделитель символом с кодом 0,
* сохранять в массиве указателей на char начало очередного слова
* Ввод: строка символов, разделённая пробелами или знаками препинания
* Вывод: массив слов
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"

int main()
{
    size_t limit;
    printf("limit = ");
    scanf("%Iu", &limit);
    char temp;
    scanf("%c", &temp);
    // printf("%i %c\n", temp, temp);
    // Создание и заполнение массива символов
    char *src = malloc(sizeof(char)*limit);
    // Выделение памяти под динамический двумерный массив
    char **cpy = (char **) malloc(sizeof(char *)*limit);
    for(size_t i = 0; i < limit; ++i)
    {
        cpy[i] = (char *) malloc(sizeof(char *)*limit);
    }
    arrFill(src, limit);
    //

    // Поиск токенов и вывод массива слов
    size_t n = transferArr(src, cpy);
    for(char **ptr = cpy; n > 0; ++ptr, --n) printf("|%s|\n", *ptr);
    //
    free(src);
    for(size_t i = 0; i < limit; ++i) free(cpy[i]);
    free(cpy);
}
