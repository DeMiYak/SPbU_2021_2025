//
// Created by vadim on 25.03.2022.
//

#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include "map.h"

typedef struct node node;
struct node {
    char *key;
    struct node *l, *r;
    int count;
};

int StringCmp(char *a, char *b) { // Функция сравнения строк
    char *j = b;
    for (char *i = a; *i != *j || *i != '\0'; ++i, ++j) {
        if (*i > *j)return 1;

        if (*i < *j)return -1;
    }
    return 0;
}

node *CreateNode(char *key) {       // Функция создания вершины
    node *root = (node *) malloc(sizeof(node));
    root->key = key;
    root->count = 1;
    root->l = NULL;
    root->r = NULL;
    return root;
}

node *MapInsert(node *root, char *key) {   // Функция создания
    if (root == NULL) {     // Если вершмна пуста
        return CreateNode(key);
    }
    while (1) {
        int cmp = StringCmp(root->key, key);
        if (cmp == 0) {     // Если строки совпадают
            root->count++;
            break;
        } else if (cmp == 1) {      // Если строка больше
            if (root->l == NULL) {
                root->l = CreateNode(key);
                break;
            } else {
                root = root->l;
            }
        } else {                    // Если строка меньше
            if (root->r == NULL) {
                root->r = CreateNode(key);
                break;
            } else {
                root = root->r;
            }
        }
    }
    return root;
}

node *CreateMap(char *words[100], size_t n) {
    node *root = CreateNode(words[0]);
    for (size_t i = 1; i < n; ++i) {
        MapInsert(root, words[i]);
    }
    return root;
}

void PrintWords(node *root, size_t *n) {
    if (root->l != NULL) {
        PrintWords(root->l, n);
    }
    double percent = root->count * 1.0 / (*n) * 100;
    printf("%s %i %lf%%\n", root->key, root->count, percent);
    if (root->r != NULL) {
        PrintWords(root->r, n);
    }
}
