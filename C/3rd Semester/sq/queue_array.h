#define QUEUE_MAX 100

typedef int element_t;

struct queue;
typedef struct queue queue;

queue * queue_alloc ();
queue * queue_clone (const queue *q);
void    queue_free  (queue *q);

int queue_is_empty (const queue *q);
int queue_is_full  (const queue *q);

int queue_push (queue *q, element_t  e);
int queue_pop  (queue *q, element_t *e);

const element_t * queue_get_front (const queue *q);
