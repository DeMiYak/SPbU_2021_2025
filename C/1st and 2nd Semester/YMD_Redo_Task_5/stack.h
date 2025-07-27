#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct node node;
struct node
{
    node *next;
    int key;
};

typedef struct stack
{
    node *head, *tail;
}stack;
#endif // STACK_H_INCLUDED
