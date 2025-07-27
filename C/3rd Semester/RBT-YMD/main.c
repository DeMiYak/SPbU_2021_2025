/**
* Яковлев Денис Михайлович (С)
* Графическая реализация красно-чёрного дерева
*/


#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<assert.h>
#include<string.h>
#include"rbt.h"
#include"graph.h"


int main()
{
    int d;
    rb_tree *t = rb_alloc();
    printf("RBTree:\n1. Insert node\n2. Delete node\n3. Print tree\nPress any key to exit\nSelect the option: ");
    while(scanf("%d", &d))
    {
        if(d == 1)
        {
            double data;
            int key;
            printf("Insert key and data: ");
            scanf("%d%lf", &key, &data);
            rb_insert(t, key, &data, sizeof(double));
        }
        else if(d == 2)
        {
            int key;
            printf("Delete key: ");
            scanf("%d", &key);
            rb_delete(t, key);
        }
        else if(d == 3)
        {
            rbt_tree_graph(t, 1, t->root);
        }
        else
        {
            break;
        }
    printf("\nRBTree:\n1. Insert node\n2. Delete node\n3. Print tree\nPress any key to exit\nSelect the option: ");
    }
    printf("Clearing the RBTree...");
    rb_free(&t);
    printf("\n...Clearing complete");
    return 0;
}
