#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

typedef struct node
{
    struct node *prev, *next;
    int data;
}node;

typedef struct deque
{
    node *curr;
    size_t length;
}deque;

#endif // DEQUE_H_INCLUDED
