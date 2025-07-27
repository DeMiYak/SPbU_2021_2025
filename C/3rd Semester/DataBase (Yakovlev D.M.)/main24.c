/**
* Яковлев Денис Михайлович (С)
* Реализовать модуль обработки массива структур,
* описывающих некоторый объект реального мира не менне чем одним строковым,
* целочисленным и вещественным полями
* a) добавление элемента
* b) удаление элемента (по номеру)
* c) сортировка массива (по выбранному полю; по возрастанию; по убыванию)
* d) вывод элементов массива на экран и в текстовый файл
* e) прочтение массива из текстового файла
* f) вывод столбчатой диаграммы по выбранному полю с легендой
* g) вывод круговой диаграммы по выбранному полю с легендой
*/

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"head24.h"
#include"sort.h"

int main()
{
    int i;
    printf("1. Insert element\n2. Delete element by the number\n3. Sort data by age with ascent\n4. Sort data by age with descent\n5. Sort data by weight with ascent\n6. Sort data by weight with descent\n7. Sort data by initials with ascent\n8. Sort data by initials with descent\n9. Print the data\n10. Rewrite the text file\n11. Read the text file\n12. Print column diagram\n13. Print pie diagram\n14. Swap bases\nChoose the option: ");
    data *data = data_alloc();
    while(scanf("%d", &i))
    {
        if(i == 1)
        {
            char *letter = malloc(sizeof(char)*100);
            int age;
            double weight;
            printf("Write initials (limit: 100 symbols): ");
            strScan(letter);
            printf("\n| %s |\n", letter);
            printf("\nEnter age: ");
            scanf("%d", &age);
            printf("\nEnter weight: ");
            scanf("%lf", &weight);
            data_insert(data, letter, age, weight);
            data_print(data);
            printf("\n\n\n");
        }
        else if(i == 2)
        {
            size_t j;
            printf("Choose the number: ");
            scanf("%Iu", &j);
            data_delete(data, j);
        }
        else if(i == 3)
        {
            data = data_sort_age_ascending(data);
            data_print(data);
        }
        else if(i == 4)
        {
            data = data_sort_age_descending(data);
            data_print(data);
        }
        else if(i == 5)
        {
            data = data_sort_weight_ascending(data);
            data_print(data);
        }
        else if(i == 6)
        {
            data = data_sort_weight_descending(data);
            data_print(data);
        }
        else if(i == 7)
        {
            data = data_sort_char_ascending(data);
            data_print(data);
        }
        else if(i == 8)
        {
            data = data_sort_char_descending(data);
            data_print(data);
        }
        else if(i == 9)
        {
            data_print(data);
        }
        else if(i == 10)
        {
            data_rewrite_FILE(data, "list.txt");
            data_print(data);
        }
        else if(i == 11)
        {
            data_read_FILE(data, "list.txt");
            data_print(data);
        }
        else if(i == 12)
        {
            break;
        }
        else if(i == 13)
        {
            break;
        }
        else if(i == 14)
        {
            size_t j, k;
            printf("Enter the first base: ");
            scanf("%Iu", &j);
            printf("Enter the second base: ");
            scanf("%Iu", &k);
            if(j > data->len || k > data->len)
            {
                printf("Error: index outside the list\n(Returning the structure)\n");
            }
            else
            {
                swap_bases(&(data->p[j]), &(data->p[k]));
            }
        }
        else
        {
            break;
        }
        printf("\n\n1. Insert element\n2. Delete element by the number\n3. Sort data by age with ascent\n4. Sort data by age with descent\n5. Sort data by weight with ascent\n6. Sort data by weight with descent\n7. Sort data by initials with ascent\n8. Sort data by initials with descent\n9. Print the data\n10. Rewrite the text file\n11. Read the text file\n12. Print column diagram\n13. Print pie diagram\n14. Swap Bases\nChoose the option: ");
    }
    printf("\n\n\nCleaning Data Bases...");
    data_free(data);
    printf("\n\n...Cleaning complete\n");
    return 0;
}

/**
*/
