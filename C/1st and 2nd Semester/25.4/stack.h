#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define PI 3.141592653589793238462643383279502884197169399375105820974944

typedef struct node node;

struct node
{
    double data;
    node *prev, *next;
};

typedef struct stack
{
    size_t length;
    node *head, *tail, *curr;
}stack;

void node_free(node *m);

node *node_alloc(double data);

stack *stack_alloc();

node *stack_insert(stack *st, double data);

double stack_pop_tail(stack *st);

double stack_tail_data(stack *st);

void stack_free(stack *st);

int strCat(const char *, char *, int);

void stack_to_str(stack *st, char *str, int maxSize);

#endif // STACK_H_INCLUDED
