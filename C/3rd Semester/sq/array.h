#include <stddef.h>

struct array;
typedef struct array array;

typedef int element_t;

array * array_alloc (size_t size);
array * array_clone (const array *a);
void    array_free  (array * a);

      element_t * array_get       (      array *a, size_t i);
const element_t * array_get_const (const array *a, size_t i);

size_t array_get_size (const array *a);
/* 0, если ограничения нет */
size_t array_max_size (const array *a);
/* 0 - успех, не 0 - неудача */
int    array_resize (array *a, size_t size);

