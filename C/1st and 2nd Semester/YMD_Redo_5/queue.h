#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef int (*filter) (int);

typedef struct node node;
struct node
{
    node *next;
    int key;
};

typedef struct queue
{
    node *head, *tail;
}queue;

node *node_alloc(int key);

void node_free(node *n);

queue *queue_alloc();

queue *queue_insert(queue *q, int key);

int queue_pop(queue *q);


/**
* ������� "����������" �������� ������
* �� ������, �������������� � ������
*/
void queue_filter(queue *q, filter cmp);

void queue_print(queue *q);

void queue_free(queue *q);

/**
* ���������� 1: ������ ��������
*/
int clearOne(int var);

/**
* ���������� 2: �������� ��������
*/
int clearTwo(int var);

/**
* ���������� 3: ��������, ������� ��� (�� ������)
*/
int clearThree(int var);

#endif // QUEUE_H_INCLUDED
