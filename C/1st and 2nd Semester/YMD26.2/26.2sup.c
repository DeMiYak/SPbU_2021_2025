/**
* а) Переход к следующему и предыдущему элементу
* б) Вставка элемента после и перед текущим
* в) Удаление текущего элемента
* г) Создание копии списка
* д) Вывод всех элементов списка на экран
*/

#include<stdio.h>
#include"deque.h"
#include<stdlib.h>
#include<stddef.h>

node *node_alloc(int d)
{
    node *m = malloc(sizeof(node));
    if(!m) return NULL;
    m->data = d;
    m->prev = NULL;
    m->next = NULL;
    return m;

}

void node_free(node *m)
{
    m->prev = NULL;
    m->next = NULL;
    free(m);
}

deque *deque_alloc()
{
    deque *dq = malloc(sizeof(deque));
    dq->length = 0;
    dq->curr = NULL;
    return dq;
}
// A

deque *deque_move_front(deque *dq)
{
    if(!dq->curr) return dq;
    if(!dq) return NULL;
    if(dq)
    {
        dq->curr = dq->curr->next;
    }
    return dq;
}

deque *deque_move_back(deque *dq)
{
    if(!dq->curr) return dq;
    if(!dq) return NULL;
    if(dq)
    {
        dq->curr = dq->curr->prev;
    }
    return dq;
}

// B

// Inserts an element in the front of curr
deque *deque_insert_front(deque *dq, int d)
{
    node *m = node_alloc(d);
    if(!m || !dq) return NULL;
    if(!dq->curr)
    {
        dq->curr = m;
        m->next = m->prev = m;
        dq->length = 0;
    }
    else
    {
        m->prev = dq->curr;
        m->next = dq->curr->next;
        dq->curr->next->prev = m;
        dq->curr->next = m;
    }
    dq->length++;
    return dq;
}

// Inserts an element in the back of curr
deque *deque_insert_back(deque *dq, int d)
{
    node *m = node_alloc(d);
    if(!m || !dq) return NULL;
    if(!dq->curr)
    {
        dq->curr = m;
        m->next = m->prev = m;
        dq->length = 0;
    }
    else
    {
        m->next = dq->curr;
        m->prev = dq->curr->prev;
        dq->curr->prev->next = m;
        dq->curr->prev = m;
    }
    dq->length++;
    return dq;
}

// C

// Deletes the current node in the deque and moves it front
deque *deque_delete_curr_front(deque *dq)
{
    if(!dq) return NULL;
    if(!dq->curr) return dq;
    if(dq->length == 1)
    {
        dq->curr = NULL;
        dq->length = 0;
        return dq;
    }
    dq->curr->prev->next = dq->curr->next;
    dq->curr->next->prev = dq->curr->prev;
    node *curr = dq->curr;
    deque_move_front(dq);
    node_free(curr);
    dq->length--;
    return dq;
}

// Deletes the current node in the deque and moves it back
deque *deque_delete_curr_back(deque *dq)
{
    if(!dq) return NULL;
    if(!dq->curr) return dq;
    if(dq->length == 1)
    {
        dq->curr = NULL;
        dq->length = 0;
        return dq;
    }
    dq->curr->prev->next = dq->curr->next;
    dq->curr->next->prev = dq->curr->prev;
    node *curr = dq->curr;
    deque_move_back(dq);
    node_free(curr);
    dq->length--;
    return dq;
}

// D

// Creates a copy of deque
deque *deque_copy(const deque *dq)
{
    if(!dq) return NULL;
    deque *dqCpy = deque_alloc();
    if(!dq->curr) return dqCpy;
    for(size_t i = 0; i < dq->length; ++i)
    {
        deque_insert_front(dqCpy, dq->curr->data);
        deque_move_front(dqCpy);
        deque_move_front((deque *) dq);
    }
    deque_move_front(dqCpy);
    return dqCpy;
}

// E

// Prints all the elements in the deque
void deque_print(const deque *dq)
{
    if(dq)
    {
        /*
        for(size_t i = 0; i < dq->length; ++i)
        {
            if(i == 0)
            {
            }
            printf("////\ni = %Iu\n\ndata = %d\n////\n\n", i, dq->curr->data);
            deque_move_front((deque *) dq);
        }
        */
        printf("\n\n");
        for(size_t i = 0; i < dq->length; ++i)
        {
            printf("%Iu: %d\n", i, dq->curr->data);
            deque_move_front((deque *) dq);
        }
        if(dq->curr == NULL)
        {
            printf("\nCurr is NULL\n");
        }
    }
    else
    {
        printf("\ndq = NULL\n");
    }

}

void deque_free(deque *dq)
{
    if(dq)
    {
        size_t temp = dq->length;
        for(size_t i = 0; i < temp; ++i)
        {
            deque_delete_curr_front(dq);
        }
    }
    free(dq);
}


// DequeList
/*
dequeList *dequeList_alloc(deque *dq)
{
    dequeList *dList = malloc(sizeof(dequeList));
    dList->currPos = 1;
    dList->dequeSize = 1;
    dList->dqList = (deque **) malloc(sizeof(deque *)*dList->dequeSize);
    return dList;
}

dequeList *dequeList_add_copy()

*/
