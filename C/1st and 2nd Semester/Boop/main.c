#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<math.h>
#include"queue.h"

int main()
{
    int d;
    filter fil;
    printf("d = ");
    scanf("%d", &d);
    switch (d)
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
    case 4:
        fil = &clearFour;
        break;
    case 5:
        fil = &clearFive;
        break;
    default:
        exit(0);
        break;
    }

    queue *q = queue_alloc();
    queue_insert(q, 3);
    queue_insert(q, 8);
    queue_insert(q, 6);
    queue_insert(q, 2);
    queue_insert(q, 13);
    queue_insert(q, 1);
    queue_insert(q, 5);
    queue_print(q);
    queue_filter(q, fil);
    queue_print(q);
    queue_free(q);
    return 0;
}
