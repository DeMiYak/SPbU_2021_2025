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

void queue_filter(queue *q, filter cmp)
{
    if(q)
    {
        while(cmp(q->head->key)){
            // printf("\n%d\n\n", queue_pop(q));
            queue_pop(q);
            queue_print(q);
        }
        if(q->head == NULL)
        {
            // printf("40");
            return;             // D -> A -> B -> C = D -> A -> C
        }
        for(node *temp = q->head; temp; temp = temp->next)
        {
            while(temp->next && cmp(temp->next->key))
            {
                node *nxt = temp->next;
                temp->next = temp->next->next;
                free(nxt);
            }
            printf("\ntemp = %d\n", temp->key);
            if(!temp->next) q->tail = temp;
        }
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
        for(node *temp = q->head; temp; temp = temp->next)
            queue_pop(q);
    }
}

int clearOne(int var)
{
    return var%2;
}

int clearTwo(int var)
{
    return (var+1)%2;
}

int clearThree(int var)
{
    return var%3;
}

int clearFour(int var)
{
    return isPrime(var);
}

int clearFive(int var)
{
    return !isPrime(var);
}

int isPrime(int var)
{
    // printf("\nvar = %d\n", var);
    // printf("sqrt = %lf\n", sqrt((double)var));
    // printf("(int) sqrt = %lf\n", ceil(sqrt((double)var)));
    int threshold = floor(sqrt((double) var)) + 1;
    for(int check = 2; check < threshold; ++check)
    {
        // printf("\n%d/%d = %d\n", var, check, var%check);
        if (!(var%check))
        {
       //     printf("isPrime = 0\n");
            return 0;
        }
    }
    // printf("isPrime = 1\n");
    return 1;
}
