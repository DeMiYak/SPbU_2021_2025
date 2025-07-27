#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

typedef struct node node;

void arrFill(char *, size_t); // Функция заполнения массива

/*
int compare(char *, char *); // Функция сравнения двух слов
*/

void whereTo(const char *, node *); // Функция нахождения нужной вершины

node *mapInsert(char *, node *);

node *createMap(char **);

node *createNode(char *);

size_t transferArr(char *, char **);

void printStr(node *, size_t *);

#endif // HEAD_H_INCLUDED
