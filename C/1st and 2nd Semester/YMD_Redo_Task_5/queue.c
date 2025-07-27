#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<math.h>
#include"queue.h"

node *node_alloc(int key)
{
    node *n = malloc(sizeof(node));
    if(!n) return NULL;
    n->next = NULL;
    n->key = key;
    return n;
}

void node_free(node *n)
{
    n->next = NULL;
    free(n);
}

queue *queue_alloc()
{
    queue *q = malloc(sizeof(queue));
    if(!q) return NULL;
    q->head = q->tail = NULL;
    return q;
}

queue *queue_insert(queue *q, int key)
{
    if(!q) return NULL;
    node *n = node_alloc(key);
    if(!n) return q;
    if(!q->tail)
        q->tail = q->head = n;
    else
    {
        q->tail->next = n;
        q->tail = n;
    }
    return q;
}

int queue_pop(queue *q)
{
    int x = q->head->key;
    if(q->head == q->tail)
    {
        node_free(q->head);
        return x;
    }
    else
    {
        node *ptr = q->head;
        q->head = q->head->next;
        node_free(ptr);
    }
    return x;
}

void queue_filter(queue *q, size_t index)
{
    if(!q || !q->head) return;

    size_t number = 0; // номер элемента списка
    node *ptr = q->head, *ptrPrev = NULL;
    while(number < index && ptr->next)
    {
        ptrPrev = ptr;
        ptr = ptr->next;
        number++;
    }
    if(number != index)
    {
        printf("Index is non-existent.\nProceeding to return the queue...\n");
        return;
    }
    if(ptr == q->head)
    {
        q->head = ptr->next;
        free(ptr);
        return;
    }
    if(ptr->next)
    {
        ptrPrev->next = ptr->next;
        free(ptr);
        return;
    }
    else
    {
        ptrPrev->next = NULL;
        free(ptr);
        q->tail = ptrPrev;
        return;
    }
}

void queue_print(queue *q)
{
    if(q)
    {
        for(node *temp = q->head; temp; temp = temp->next)
        {
            printf("%d\n", temp->key);
        }
    }
}

void queue_free(queue *q)
{
    if(q)
    {
        node *temp = q->head;
        while(temp)
        {
            node *temp2 = temp->next;
            node_free(temp);
            temp = temp2;
        }
    }
}
