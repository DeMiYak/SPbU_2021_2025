#ifndef SUP_H_INCLUDED
#define SUP_H_INCLUDED

typedef struct node node;

struct node
{
    node *prev, *next;
    int key;
};

typedef struct deque deque;

struct deque
{
    node *head, *tail;
};

typedef int (*criteria) (node *n);

deque *deque_delete(criteria (*crit), deque *dq);

deque *deque_insert(node *n, deque *dq);

deque *deque_alloc();

node *node_alloc(int key);

#endif // SUP_H_INCLUDED
