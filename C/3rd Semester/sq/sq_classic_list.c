#include<stdlib.h>
#include "sq_classic_list.h"

struct node
{
    element_t data;
    struct node *next;
};

int stack_push (node **top, element_t e)
{
    node *n = malloc (sizeof(*n));
    if (!n) return 1;

    n->data = e;
    n->next = *top;
    *top = n;

    return 0;
}

node * stack_push2 (node *top, element_t e)
{
    node *n = malloc (sizeof(*n));
    if (!n) return NULL;

    n->data = e;
    n->next = top;

    return n;
}

int queue_push (node **head, node **tail, element_t e)
{
    node *n = malloc (sizeof(*n));
    if (!n) return 1;

    n->data = e;
    n->next = NULL;

    if (*head == NULL)
        *head = n;
    else
        (*tail)->next = n;

    *tail = n;
    return 0;
}

int stack_pop (node **top, element_t *e)
{
    node *t = *top;
    if (!t) return 1;

    *top = t->next;
    if (e) *e = t->data;
    free(t);

    return 0;
}

node * stack_pop2 (node *top, element_t *e)
{
    node *t = top;
    if (!t) return NULL;

    if (e) *e = t->data;
    free(t);

    return t->next;
}

int queue_pop  (node **head, node **tail, element_t *e)
{
    node *t = *head;
    if (!t) return 1;

    *head = t->next;
    if (e) *e = t->data;
    free(t);

    if (*head == NULL) *tail = NULL;

    return 0;
}
















