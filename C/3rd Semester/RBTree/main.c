#include <stdio.h>
#include <stdlib.h>

#include "rbt.h"
#include "graph_rbt.h"

int main(){

    double v = 0;
    int k;
    size_t n;

    rb_tree *rbt;

    rbt = rb_alloc();

    rb_insert(rbt, 2, &v, sizeof(double));
    rb_insert(rbt, 3, &v, sizeof(double));
    rb_insert(rbt, 0, &v, sizeof(double));
    rb_insert(rbt, 1, &v, sizeof(double));
    rb_insert(rbt, -4, &v, sizeof(double));
    rb_insert(rbt, 5, &v, sizeof(double));
    rb_insert(rbt, 9, &v, sizeof(double));
    rb_insert(rbt, -3, &v, sizeof(double));
    rb_insert(rbt, -9, &v, sizeof(double));
    rb_insert(rbt, 11, &v, sizeof(double));
    while(1){
    printf("1)Insert elem in rbt\n2)Delete elem by key in rbt\n3)Show done rbt\n4)quit\n");
    scanf("%Iu", &n);

    switch(n){
    case 1:
        printf("Input key and double data: ");
        scanf("%d %lf", &k, &v);

        rb_insert(rbt, k, &v, sizeof(double));
        break;
    case 2:
        printf("Input key: ");
        scanf("%d", &k);

        rb_delete(rbt, k);
        break;
    case 3:

        rb_tree_graph(rbt, 1, rbt->root);
        break;
    case 4:
        return 0;
    default: printf("No such command");

    };

    }

    return 0;
}
