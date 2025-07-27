//
// Created by vadim on 28.03.2022.
//

#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include "stack.h"

typedef struct Stack Stack;
typedef struct Node Node;

struct Node {
    double value;
    Node *back, *next;
};

Stack *StackInit() {
    Stack *initStack = (Stack *) malloc(sizeof(Stack));
    initStack->last = NULL;
    initStack->first = NULL;
    initStack->current = NULL;
    initStack->len = 0;
    return initStack;
}

Node *Push(Stack *stack, double value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->back = NULL;
    if (stack->len == 0) {
        stack->last = node;
        stack->first = node;
    } else {
        node->back = stack->last;
        stack->last->next = node;
        stack->last = node;
    }
    stack->len++;
    return node;
}

double Pop(Stack *stack) {
    if (stack->len == 0) {
        return 0.0 / 0.0;
    }
    Node *node = stack->last;
    double value = node->value;
    if (stack->len == 1) {
        stack->first = NULL;
        stack->last = NULL;
        stack->len = 0;
        free(node);
        return value;
    }
    stack->last = node->back;
    stack->last->next = NULL;
    stack->len--;
    free(node);
    return value;
}

double Back(Stack *stack) {
    if (stack->len < 1) {
        return 0.0 / 0.0;
    }
    return stack->last->value;
}

void StackDelete(Stack *stack) {
    while (stack->len > 0) {
        Pop(stack);
    }
    free(stack);
}

int SCat(char *inS, int n, const char *outS) {
    char *j = inS + n;
    for (const char *i = outS; *i != '\0'; ++i, ++j) {
        if (*i=='.' && *(i+1)=='\0'){
            break;
        }
        *j = *i;
    }
    int r = j - inS - n;
    return r;
}

void StackToStr(Stack *stack, char *str, int maxSize) {
    char *s = str;
    int it = 0;
    if (str == NULL) {
        s = (char *) malloc(maxSize * sizeof(char));
        s[0] = '\0';
    }
    Node *node = stack->first;
    for (; node != NULL; node = node->next) {
        char buffer[32];
        gcvt(node->value, 32, buffer);
        it += SCat(s, it, buffer);
        char *temp = " ";
        it += SCat(s, it, temp);
        if (maxSize - it < 50) {
            if (maxSize - it > 10)
                it += SCat(s, it, "LowSize");
            break;
        }
    }
    s[it] = '\0';
    if (str == NULL) {
        printf("%s\n", s);
        free(s);
    }
}
