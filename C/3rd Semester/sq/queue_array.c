#include<stdlib.h>
#include "queue_array.h"

struct queue
{
    element_t data[QUEUE_MAX];
    size_t head, tail;
};

queue * queue_alloc ()
{
    queue *q = malloc(sizeof(*q));
    if (!q) return NULL;

    q->head = q->tail = QUEUE_MAX;
    return q;
}

queue * queue_clone (const queue *q)
{
    queue *n = malloc(sizeof(*n));
    if (!n) return NULL;

    *n = *q;
    return n;
}

void    queue_free  (queue *q)
{
    free(q);
}

int queue_is_empty (const queue *q)
{
    return q->head == QUEUE_MAX;
}
int queue_is_full  (const queue *q)
{
    return (q->tail + 1) % QUEUE_MAX == q->head; // рассмотрение очереди справа налево
                                                 // голова идёт влево, хвост остаётся позади
}

int queue_push (queue *q, element_t  e)
{
    if (q->head == QUEUE_MAX)
    {
        q->data[0] = e;
        q->head = q->tail = 0;
        return 0;
    }

    if (queue_is_full(q)) return 1;

    q->tail = (q->tail + 1) % QUEUE_MAX;
    q->data[q->tail] = e;
    return 0;
}

int queue_pop  (queue *q, element_t *e)
{
    if (queue_is_empty(q)) return 1;

    if (e) *e = q->data[q->head];
    if (q->head == q->tail)
    {
        q->head = q->tail = QUEUE_MAX;
        return 0;
    }

    q->head = (q->head + 1) % QUEUE_MAX;
    return 0;
}

const element_t * queue_get_front (const queue *q)
{
    return q->head == QUEUE_MAX ? NULL : &(q->data[q->head]);
}
