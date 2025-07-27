#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include"stack.h"

node *node_alloc(int key)
{
    node *n = malloc(sizeof(node));
    if(!n) return NULL;
    n->key = key;
    n->next = NULL;
    return n;
}

stack *stack_alloc()
{
    stack *st = malloc(sizeof(stack));
    if(!st) return NULL;
    st->head = NULL;
    st->tail = NULL;
    return st;
}

stack *stack_push(stack *st, int key)
{
    if(!st) return NULL;
    node *n = node_alloc(key);
    if(!st->head)
    {
        st->head = st->tail = n;
    }
    else
    {
        st->head->next = n;
        st->head = n;
    }
    return st;
}

int stack_pop(stack *st)
{
    int x = st->tail->key;
    if(st->head == st->tail)
    {
        free(st->tail);
    }
    else
    {
        node *ptr = st->tail;
        st->tail = st->tail->next;
        free(ptr);
    }
    return x;
}

int
