/**
* Яковлев Денис Михайлович (С)
* Построение циклического двусвязного списка целых чисел
* а) Переход к следующему и предыдущему элементу
* б) Вставка элемента после и перед текущим
* в) Удаление текущего элемента
* г) Создание копии списка
* д) Вывод всех элементов списка на экран
*/

#include<stdio.h>
#include<stddef.h>
#include"deque.h"
#include<stdlib.h>

int main()
{
    int i;
    printf("1. Moving from current to previous or next\n2. Insert element before or after current\n3. Delete current element\n4. Create a copy of the list\n5. Print all elements\nAny other key to leave\nSelect the option: ");
    deque *dq = deque_alloc(), *dqCpy = deque_alloc();
    while(scanf("%d", &i))
    {
        printf("\nThe number entered is %d\n", i);
        if(i == 1)
        {
            // +
            int temp;
            while(1)
            {
                printf("Press 1 to move front, 2 to move back, any other integer to return: ");
                scanf("%d", &temp);
                if(temp == 1)
                {
                    deque_move_front(dq);
                    deque_print((const deque *) dq);
                }
                else if(temp == 2)
                {
                    deque_move_back(dq);
                    deque_print((const deque *) dq);
                }
                else
                {
                    break;
                }
            }
        }
        else if(i == 2)
        {
            // +
            int temp, d;
            while(1)
            {
                printf("Insert number: ");
                scanf("%d", &d);
                printf("Press 1 to insert front, 2 to insert back, any other integer to return: ");
                scanf("%d", &temp);
                if(temp == 1)
                {
                    deque_insert_front(dq, d);
                    deque_print((const deque *) dq);
                }
                else if(temp == 2)
                {
                    deque_insert_back(dq, d);
                    deque_print((const deque *) dq);
                }
                else
                {
                    break;
                }
            }
        }
        else if(i == 3)
        {
            // +
            int temp;
            while(1)
            {
                printf("Press 1 to delete and move front, or 2 to delete and move back, or any other integer to return: ");
                scanf("%d", &temp);
                if(temp == 1)
                {
                    deque_delete_curr_front(dq);
                    deque_print((const deque *) dq);
                }
                else if(temp == 2)
                {
                    deque_delete_curr_back(dq);
                    deque_print((const deque *) dq);
                }
                else
                {
                    break;
                }
            }
        }
        else if(i == 4)
        {
            // +
            deque_free(dqCpy);
            dqCpy = deque_copy((const deque *) dq);
            deque_print((const deque *) dqCpy);
        }
        else if(i == 5)
        {
            // +
            deque_print((const deque *) dq);
        }
        /*
        else if(i == 6)
        {
            if(!*(dqList + 1))
            {
                printf("There is no copy\n");
            }
            else
            {

            }
        }
        */
        else
        {
            break;
        }
        printf("\n1. Moving from current to previous or next\n2. Insert element before or after current\n3. Delete current element\n4. Create a copy of the list\n5. Print all elements\nAny other key to leave\nSelect the option: ");
    }
    deque_free(dq);
    deque_free(dqCpy);
    return 0;
}
