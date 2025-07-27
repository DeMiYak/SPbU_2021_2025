/**
Дан связный список целых чисел, организованный по принципу стека. Требуется написать функцию, удаляющую из заданного списка элементы, удовлетворяющие заданному критерию.
 Критерий передается в функцию посредством функционального указателя на логическую функцию целого чис-ла.
  Выделение дополнительной памяти (создание нового списка, создание дополнительных узлов) недопускается.
*/
/*
Идея: поступает связный список, организованный по принципу стека (первый вошёл, последний вышел)
Функция идёт с хвоста до головы, проверяя каждый элемент на удовлетворение заданному критерию.
Если элемент удовлетворяет условию - оно удаляется, и так до тех пор, пока не будет проверяться голова.
На голове необходимо проверить на NULL
Если удалили хвост - смещаем его. Если удалили элемент изнутри - просто удаляем его. Если удалили голову - смещаем её и завершаем проверку
*/

/* Реализация: отсутствует */
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include"sup.h"




node *node_alloc(int key)
{
    node *n = malloc(sizeof(node));
    n->prev = n->next = NULL;
    n->key = key;
    return n;
}

void node_free(node *n)
{
    n->prev = n->next = NULL;
    free(n);
}

deque *deque_alloc()
{
    deque *dq = malloc(sizeof(deque));
    if(!dq) return NULL;
    dq->head = NULL;
    dq->tail = NULL;
    return dq;
}

deque *deque_insert(node *n, deque *dq)
{
    if(!dq || !n) return NULL;
    if(!dq->head || !dq->tail)
    {
        dq->head = dq->tail = n;
    }
    else
    {
        n->prev = dq->tail;
        dq->tail->next = n;
        dq->tail = n;
    }
    return dq;
}

/*
deque *deque_delete_by_criteria(criteria (*crit), deque *dq)
{
    if(!dq) return NULL;
    if(!dq->head || !dq->tail) return dq;
    node *n = dq->tail;

}
*/

/*
void deque_print(deque *dq)
{
    if(dq)
    {
        if(dq->head && dq->tail)
        {
            if()
        }
        if()
    }
}
*/
