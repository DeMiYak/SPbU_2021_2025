#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

typedef struct node
{
    int data;
    struct node *prev, *next;
}node;

typedef struct deque
{
    size_t length;
    node *curr;
}deque;

typedef struct dequeList
{
    size_t dequeSize, currPos;
    deque **dqList;
}dequeList;

node *node_alloc(int d);

void node_free(node *m);

deque *deque_alloc();

deque *deque_move_front(deque *dq);

deque *deque_move_back(deque *dq);

deque *deque_insert_front(deque *dq, int d);

deque *deque_insert_back(deque *dq, int d);

deque *deque_delete_curr_front(deque *dq);

deque *deque_delete_curr_back(deque *dq);

deque *deque_copy(const deque *dq);

void deque_print(const deque *dq);

void deque_free(deque *dq);


#endif // DEQUE_H_INCLUDED
