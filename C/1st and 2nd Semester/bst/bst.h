#include <stddef.h>

typedef int key_t;

typedef struct bst
{
    key_t key;
    struct bst *left, *right;
} bst;


