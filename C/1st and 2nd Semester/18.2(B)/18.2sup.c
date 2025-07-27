#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"

typedef struct node node;
struct node
{
    struct node *l, *r;    // Левая и правая ветви
    char *key;      // Значение строки
    size_t count;   // Кол-во повторяющихся слов
};

void arrFill(char *src, size_t limit)
{
    char *ptr = src, *end = src + limit;
    for(;ptr < end; ++ptr)
    {
        scanf("%c", ptr);
        if(*ptr == '\n') break;
    }
    *ptr = '\0';
}
/*
int compare(char *root, char *line)
{
    char *ptrRoot = root, *ptrLine = line;
    for(; *ptrRoot != *ptrLine || *ptrRoot != '\0' ;++ptrRoot, ++ptrLine)
    {
        if(*ptrRoot > *ptrLine) return -1;
        if(*ptrRoot < *ptrLine) return 1;
    }
    return 0;
}
*/
/*
node *mapInsert(char *key, node *data)
{
    if(data == NULL)
    {
        return createNode(key);
    }
    int check = compare(data->key, key);
    if(check == 1)
    {
        if(data->r == NULL)
        {
            data->r = createNode(key);
        }
        else data = data->r;
    } else if(check == -1)
    {
        if(data->l == NULL)
        {
            data->l = createNode(key);
        }
        else data = data->l;
    } else
    {
        data->count++;
    }
    printf("%d %p\n", check, data);
    return data;
}
*/

node *mapInsert(char *key, node *root) {   // Функция создания
    if (root == NULL) {     // Если вершмна пуста
        return createNode(key);
    }
    while (1) {
        int check = strcmp(root->key, key);
        if (check == 0) {     // Если строки совпадают
            root->count++;
            break;
        } else if (check == 1) {      // Если строка больше
            if (root->l == NULL) {
                root->l = createNode(key);
                break;
            } else {
                root = root->l;
            }
        } else {                    // Если строка меньше
            if (root->r == NULL) {
                root->r = createNode(key);
                break;
            } else {
                root = root->r;
            }
        }
    }
    return root;
}


node *createMap(char **cpy)
{
    char **ptr = cpy;
    node *data = createNode(*ptr);
    ++ptr;
    for(; *ptr != NULL; ++ptr)
    {
        printf("\n|%s|\n", *ptr);
        mapInsert(*ptr, data);
    }
    return data;
}

node *createNode(char *key) // Функция создания точки вершины
{
    node *data = (node *) malloc(sizeof(node));
    data->key = key;
    data->count = 1;
    data->l = NULL;
    data->r = NULL;
    return data;
}

size_t transferArr(char *src, char **cpy) // Функция создания массива строк
{
    char **ptrCpy = cpy;
    size_t i = 0;
    for(char *ptr = strtok(src, " ,.;:-!?"); ptr != NULL; ptr = strtok(NULL, " ,.;:-!?"))
    {
        *ptrCpy = ptr;
        ++ptrCpy;
        ++i;
    }
    *ptrCpy = NULL;
    return i;
}

void printStr(node *data, size_t *n)
{
    if(data->l != NULL)
        printStr(data->l, n);
    double percent = data->count*1.0/(*n)*100;
    printf("%s %Iu %lf\n", data->key, data->count, percent);
    if(data->r != NULL)
        printStr(data->r, n);
}
