typedef int element_t;

/* АТД стек */

struct stack;
typedef struct stack stack;


stack * stack_alloc ();
stack * stack_clone (const stack *s);
void    stack_free  (stack *s);

/* (Логические функции) */
int stack_is_empty (const stack *s);
int stack_is_full  (const stack *s);

/* 0 - успех, не 0 - неудача */
int stack_push (stack *s, element_t  e);
/* если e = NULL, игнорируется */
int stack_pop  (stack *s, element_t *e);

/* Возвращает NULL, если стек пуст */
const element_t * stack_get_front (const stack *s);

/* АТЧ очередь */

struct queue;
typedef struct queue queue;


queue * queue_alloc ();
queue * queue_clone (const queue *q);
void    queue_free  (queue *q);

int queue_is_empty (const queue *q);
int queue_is_full  (const queue *q);

int queue_push (queue *s, element_t  q);
int queue_pop  (queue *s, element_t *q);

const element_t * queue_get_front (const queue *q);
