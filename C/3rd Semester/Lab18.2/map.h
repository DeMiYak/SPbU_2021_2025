//
// Created by vadim on 25.03.2022.
//

#ifndef LAB18_2_MAP_H
#define LAB18_2_MAP_H

typedef struct node node;

node *CreateMap(char *arr[100], size_t n);

void PrintWords(node *root, size_t *n);

#endif //LAB18_2_MAP_H
