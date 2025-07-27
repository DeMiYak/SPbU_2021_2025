#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

struct array
{
    void *data;
    size_t size;         /* размер элемента                                       */
    size_t capacity;     /* вместимость                                           */
    size_t min;          /* минимальная вместимость                               */
    size_t count;        /* размер массива                                        */
    array_capacity_f fr; /* устанавливаемая вместимость по размеру массива        */
    array_capacity_f fs; /* максимально допустимая вместимость по размеру массива */
};

size_t array_capacity_fr (size_t count)
{
    return 2 * count;
}

size_t array_capacity_fs (size_t count)
{
    return 4 * count;
}

array *array_alloc (size_t size, size_t min, array_capacity_f fr, array_capacity_f fs)
{
    array *a = malloc (sizeof *a);
    if (!a) return NULL;

    if (!min) min = ARRAY_MIN_CAPACITY;
    if (!fr)  fr  = array_capacity_fr;
    if (!fs)  fs  = array_capacity_fs;

    a->count    = 0;
    a->size     = size;
    a->data     = NULL;
    a->min      = min;
    a->capacity = min;
    a->fr       = fr;
    a->fs       = fs;

    if (array_adjust_capacity (a))
    {
        array_free(a);
        return NULL;
    }

    return a;
}

array *array_clone (const array *a)
{
    array *b = array_alloc(a->size, a->min, a->fr, a->fs);

    if (!b) return NULL;

    if (array_resize(b, a->count))
    {
        array_free(b);
        return NULL;
    }

    memcpy (b->data, a->data, a->count * b->size);
    return b;
}


void array_free (array *a)
{
    free (a->data);
    free (a);
}

int array_set_capacity (array *a, size_t capacity)
{
    void *n = realloc (a->data, capacity * a->size);
    if (!n) return 1;

    a->capacity = capacity;
    a->data     = n;

    if (a->count > capacity) a->count = capacity;

    return 0;
}

int array_adjust_capacity (array *a)
{
    size_t capacity = a->fr (a->count);
    if (capacity < a->min) capacity = a->min;
    return array_set_capacity (a, capacity);
}

int array_set_min_capacity (array *a, size_t min)
{
    array b = *a;
    if (!min) min = ARRAY_MIN_CAPACITY;
    b.min = min;
    if (array_adjust_capacity (&b)) return 1;
    *a = b;
    return 0;
}

int array_set_capacity_fr (array *a, array_capacity_f fr)
{
    array b = *a;
    if (!fr) fr  = array_capacity_fr;
    b.fr = fr;
    if (array_adjust_capacity (&b)) return 1;
    *a = b;
    return 0;
}

int array_set_capacity_fs (array *a, array_capacity_f fs)
{
    array b = *a;
    if (!fs) fs  = array_capacity_fs;
    b.fs = fs;
    if (array_adjust_capacity (&b)) return 1;
    *a = b;
    return 0;
}

int array_resize (array *a, size_t count)
{
    array b = *a;
    b.count = count;
    if ( ( (count > a->count &&       count  > b.capacity ) ||
           (count < a->count && a->fs(count) < b.capacity )
         ) && array_adjust_capacity(&b) )
        return 1;
    *a = b;
    return 0;
}

size_t array_capacity (const array *a)
{
    return a->capacity;
}

size_t array_size (const array *a)
{
    return a->count;
}

int array_set (array *a, size_t i, const void *e)
{
    if (i < a->count)
    {
        memcpy (array_element(a, i), e, a->size);
        return 0;
    }
    return 1;
}

int array_get (const array *a, size_t i, void *e)
{
    if (i < a->count)
    {
        memcpy (e, array_element_const(a, i), a->size);
        return 0;
    }
    return 1;
}

void * array_element (array *a, size_t i)
{
    return (char *) a->data + i * a->size;
}

const void * array_element_const (const array *a, size_t i)
{
    return (char *) a->data + i * a->size;
}

int array_insert (array *a, const void *e)
{
    size_t count = a->count;
    int status = array_resize (a, count + 1);
    if (status) return status;

    memcpy (array_element(a, count), e, a->size);
    return 0;
}

int array_delete (array *a, size_t i)
{
    size_t count = a->count;
    void *tmp = NULL;
    int status;

    if (i >= count) return 1;
    --count;

    if (count > i)
    {
        tmp = malloc(a->size);
        if (!tmp) return 1;
        memcpy(tmp, array_element_const(a, count), a->size);
    }
    status = array_resize (a, count);
    if (status)
    {
        free(tmp);
        return status;
    }

    if (count > i)
    {
        memcpy (array_element(a, i), tmp, a->size);
        free(tmp);
    }
    return 0;
}

void array_foreach (array *a, array_callback_f f, void *data)
{
    char *t = a->data, *e = t + a->count * a->size;
    for (; t < e; t += a->size) f(t, data);
}
void array_foreach_const (const array *a, array_callback_f_const f, void *data)
{
    const char *t = a->data, *e = t + a->count * a->size;
    for (; t < e; t += a->size) f(t, data);
}

void array_iforeach (array *a, array_icallback_f f, void *data)
{
    size_t i = 0;
    for (; i < a->count; ++i) f(array_element(a, i), i, a->count, data);
}
void array_iforeach_const (const array *a, array_icallback_f_const f, void *data)
{
    size_t i = 0;
    for (; i < a->count; ++i) f(array_element_const(a, i), i, a->count, data);
}
