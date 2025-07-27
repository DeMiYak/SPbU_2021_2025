#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"stack.h"

// +
void node_free(node *m)
{
    m->prev = m->next = NULL;
    free(m);
}

// +
node *node_alloc(double data)
{
    node *m = malloc(sizeof(node));
    m->data = data;
    m->next = m->prev = NULL;
    return m;
}

// +
stack *stack_alloc()
{
    stack *st = malloc(sizeof(stack));
    st->head = NULL;
    st->tail = NULL;
    st->curr = NULL;
    st->length = 0;
    return st;
}

// +
node *stack_insert(stack *st, double data)
{
    node *m = node_alloc(data);
    if(st->length == 0)
    {
        st->head = st->tail = m;
    }
    else
    {
        m->prev = st->tail;
        st->tail->next = m;
        st->tail = m;
    }
    st->length++;
    return m;
}

// +
double stack_pop_tail(stack *st)
{
    if(st->length == 0)
    {
        return 0/0.0;
    }
    node *m = st->tail;
    double data = m->data;
    if(st->length == 1)
    {
        st->head = st->tail = NULL;
        st->length = 0;
        node_free(m);
        return data;
    }
    st->tail = m->prev;
    st->tail->next = NULL;
    st->length--;
    node_free(m);
    return data;
}

// +
double stack_tail_data(stack *st)
{
    if(st->length == 0)
    {
        return 0/0.0;
    }
    return st->tail->data;
}

// +
void stack_free(stack *st)
{
    while(st->length > 0)
    {
        stack_pop_tail(st);
    }
    free(st);
}

// +
int strCat(const char *outS, char *inS, int n)
{
    char *j = inS + n;
    for(const char *i = outS; *i != '\0'; ++i, ++j)
    {
        if(*i == '.' && *(i + 1) == '\0')
        {
            break;
        }
        *j = *i;
    }
    int r = j - inS - n;
    return r;
}

// +
void stack_to_str(stack *st, char *str, int maxSize)
{
    char *s = str;
    int i = 0;
    if(str == NULL)
    {
        s = malloc(sizeof(char)*maxSize);
        *s = '\0';
    }
    node *m = st->head;
    for(; m != NULL; m = m->next)
    {
        char buffer[32];
        gcvt(m->data, 32, buffer);
        i += strCat(buffer, s, i);
        char *temp = " ";
        i += strCat(temp, s, i);
        if(maxSize - i < 50)
        {
            if(maxSize - i > 10)
                i += strCat("LowSize", s, i);
            break;
        }
    }
    *(s + i) = '\0';
    if(str == NULL)
    {
        printf("%s\n", s);
        free(s);
    }
}
