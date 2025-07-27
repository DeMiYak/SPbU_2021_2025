#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"Deque.h"

/**
int deque_push_front(deque *d, int e)
{
    node *n = malloc(sizeof(node));
    if(!n) return 1;

    n->data = e;
    n->next = d->head;
    n->prev = NULL;

    if(d->tail == NULL)
    {
        d->head = d->tail = n;
    }
    else
    {
        d->head->prev = n;
        d->head = n;
    }
    return 0;
}

int deque_push_back(deque *d, int e)
{
    node *n = malloc(sizeof(node));
    if(!n) return -1;

    n->data = e;
    n->prev = d->tail;
    n->next = NULL;

    if(d->head == NULL)
    {
        d->tail = d->head = n;
    }
    else
    {
        d->tail->next = n;
        d->tail = n;
    }
    return 0;
}

int deque_pop_front(deque *d)
{
    int e;
}
*/

/**
* Яковлев Денис Михайлович (С)
* Циклический двусвязный список целых чисел
* (а) перехода к следующему и предыдущему элементу;
* (б) вставка элемента после и перед текущим;
* (с) удаление текущего элемента;
* (д) создания копии списка;
* (е) вывода всех элементов списка на экран;
*/

node *node_alloc(int d)
{
    node *n = malloc(sizeof(node));
    n->prev = NULL;
    n->next = NULL;
    n->data = d;
    return n;
}

deque *deque_alloc()
{
    deque *dq = malloc(sizeof(deque));
    dq->curr = NULL;
    dq->length = 0;
    return dq;
}

deque *deque_push_front(deque *dq, int d)
{
    node *n = malloc(sizeof(node));
    if(!dq || !n) return NULL;
    n->data = d;
    if(!dq->curr)
    {
        dq->curr = n;
        n->next = n->prev = n;
    }
    else
    {
        n->next = dq->curr->next;
        n->prev = dq->curr;
        dq->curr->next->prev = n;
        dq->curr->next = n;
    }
    dq->length++;
    return dq;
}

deque *deque_push_back(deque *dq, int d)
{
    node *n = malloc(sizeof(node));
    if(!dq || !n) return NULL;
    n->data = d;
    if(!dq->curr)
    {
        dq->curr = n;
        n->next = n->prev = n;
    }
    else
    {
        n->prev = dq->curr->prev;
        n->next = dq->curr;
        dq->curr->prev->next = n;
        dq->curr->prev = n;
    }
    dq->length++;
    return dq;
}

deque *deque_delete_curr_move_front(deque *dq)
{
    if(!dq) return NULL;
    if(length == 1)
    {
        node_free(dq->curr);
        length--;
        return dq;
    }
    else
    {
        dq->curr->next->prev =
        length--;
    }
}

node *node_free(node *n)
{
    if(!n) return NULL;
    n->prev = NULL;
    n->next = NULL;
    free(n);
}
// A



// B

// C

// D

// E
