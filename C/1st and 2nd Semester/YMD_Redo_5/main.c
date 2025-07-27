/**
* Яковлев Денис Михайлович (С)
* Написать функцию, удаляющую из заданного списка элемент по его номеру
* void queue_filter(queue *q, filter cmp);
*/

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<math.h>
#include"queue.h"

int main()
{
    queue *q = queue_alloc();
    int d;
    filter fil;
    printf("d = ");
    scanf("%d", &d);
    switch(d)
    {
    case 1:
        fil = &clearOne;
        break;
    case 2:
        fil = &clearTwo;
        break;
    case 3:
        fil = &clearThree;
        break;
    default:
        break;
    }
    queue_insert(q, 0);
    queue_insert(q, 1);
    queue_insert(q, 2);
    queue_insert(q, 3);
    queue_insert(q, 4);
    queue_insert(q, 5);
    queue_insert(q, 6);
    queue_insert(q, 7);
    queue_insert(q, 8);
    queue_insert(q, 9);
    queue_insert(q, 10);
    queue_insert(q, 11);
    queue_insert(q, 12);
    queue_insert(q, 13);
    queue_insert(q, 14);
    queue_insert(q, 15);
    queue_insert(q, 16);
    printf("\nOriginal queue:\n");
    queue_print(q);
    printf("\n\n\n");
    queue_filter(q, fil);
    printf("Filtered queue:\n");
    queue_print(q);
    queue_free(q);
    return 0;
}
