#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef int (*filter)(int);

typedef struct node node;
struct node
{
    node *next;
    int key;
};

typedef struct queue
{
    node *head, *tail;
} queue;

node *node_alloc(int key);

void node_free(node *n);

queue *queue_alloc();

queue *queue_insert(queue *q, int key);

int queue_pop(queue *q);

void queue_filter(queue *q, filter cmp);

int clearOne(int);

int clearTwo(int);

int clearThree(int);

int clearFour(int);

int clearFive(int);

int isPrime(int);

void queue_print(queue *q);

void queue_free(queue *q);

#endif // QUEUE_H_INCLUDED
