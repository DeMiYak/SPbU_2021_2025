#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>
#include"matrixStruct.h"
#include"matrixInitFunc.h"
#include"matrixOper.h"
#include"matrixSolve.h"
// Задача: избавиться от утечек памяти, сократить использование памяти засчёт обращения к функции free ; рассмотреть resize на корректность

int main()
{
    size_t i, j, k;
    printf("1. Print\n2. Sum\n3. Identity\n4. Zero_Set\n5. Mult_Scalar_Row\n6. Mult_Scalar_All\n7. Swap_Rows\n8. Transpose\n9. Clone\n10. Add\n11. Add_Scalar\n12. Resize\n13. Mult_Matrixes\n14. Matrix_Norm\n15. Matrixes_Taylor_Exp\n16. Gauss_Method\nSelect one of the following: ");
    scanf("%Iu", &k);
    printf("Enter number of rows = ");
    scanf("%Iu", &i);
    printf("Enter number of columns = ");
    scanf("%Iu", &j);
    if(k == 1)
    {
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\n\n");
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 2)
    {
        matrixLine *m = matrixLine_alloc(i, j), *m1 = matrixLine_alloc(i, j), *m2 = matrixLine_alloc(i, j);
        matrixLine_scan(m1);
        printf("\nMatrix m1 complete\n");
        matrixLine_scan(m2);
        printf("\nMatrix m2 complete\n");
        matrixLine_sum(m, m1, m2);
        if(m || m->mat) matrixLine_print(m);
        else printf("Error");
        matrixLine_free(m);
        matrixLine_free(m1);
        matrixLine_free(m2);
    }
    else if(k == 3)
    {
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        matrixLine_identity(m);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 4)
    {
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        matrixLine_set_zero(m);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 5)
    {
        double eps;
        size_t ind;
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        printf("\neps = ");
        scanf("%lf", &eps);
        printf("\nindex = ");
        scanf("%Iu", &ind);
        matrixLine_mult_scalar_row(m, ind, eps);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 6)
    {
        double eps;
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        printf("\neps = ");
        scanf("%lf", &eps);
        matrixLine_mult_scalar_all(m, eps);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 7)
    {
        size_t indx, indy;
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        printf("First index = ");
        scanf("%Iu", &indx);
        printf("Second index = ");
        scanf("%Iu", &indy);
        matrixLine_swap_row(m, indx, indy);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 8)
    {
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete");
        matrixLine *m1 = matrixLine_transpose_rect(m);
        matrixLine_print(m1);
        matrixLine_free(m);
        matrixLine_free(m1);
    }
    else if(k == 9)
    {
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        matrixLine *mClone = matrixLine_clone((const matrixLine *) m);
        matrixLine_print(mClone);
        matrixLine_free(mClone);
        matrixLine_free(m);
    }
    else if(k == 10)
    {
        matrixLine *m = matrixLine_alloc(i, i), *m1 = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        matrixLine_scan(m1);
        printf("\nMatrix m1 complete\n");
        matrixLine_add(m, (const matrixLine *) m1);
        matrixLine_print(m);
        matrixLine_free(m);
        matrixLine_free(m1);
    }
    else if(k == 11)
    {
        double eps;
        size_t indx, indy;
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        printf("eps = ");
        scanf("%lf", &eps);
        printf("To index = ");
        scanf("%Iu", &indx);
        printf("From index = ");
        scanf("%Iu", &indy);
        matrixLine_add_row_scalar(m, indx, indy, eps);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 12)
    {
        size_t indx, indy;
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        printf("\nNew number of rows: ");
        scanf("%Iu", &indx);
        printf("\nNew number of columns: ");
        scanf("%Iu", &indy);
        matrixLine *m1 = matrixLine_resize(m, indx, indy);
        matrixLine_print(m1);
        matrixLine_free(m);
        matrixLine_free(m1);
    }
    else if(k == 13)
    {
        size_t k, w;
        printf("m2 rows: ");
        scanf("%Iu", &k);
        printf("m2 columns: ");
        scanf("%Iu", &w);
        matrixLine *m1 = matrixLine_alloc(i, j), *m2 = matrixLine_alloc(k, w);
        matrixLine_scan(m1);
        printf("\nMatrix m1 complete\n");
        matrixLine_scan(m2);
        printf("\nMatrix m2 complete\n");
        //matrixLine_print(m1);
        //printf("\n\n");
        //matrixLine_print(m2);
        matrixLine *m = matrixLine_mult_matrixes((const matrixLine *) m1, (const matrixLine *) m2);
        matrixLine_print(m);
        matrixLine_free(m);
        matrixLine_free(m1);
        matrixLine_free(m2);
    }
    else if(k == 14)
    {
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        double norm = matrixLine_Norm(m);
        printf("\nnorm = %lf\n", norm);
        matrixLine_print(m);
        matrixLine_free(m);
    }
    else if(k == 15)
    {
        double eps;
        matrixLine *m = matrixLine_alloc(i, j);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        printf("\neps = ");
        scanf("%lf", &eps);
        matrixLine *m1 = matrixLine_Taylor_Exp((const matrixLine *) m, eps);
        printf("\n\n\n");
        matrixLine_print(m1);
        printf("\n\n");
        matrixLine_free(m1);
        matrixLine_free(m);
    }
    else if(k == 16)
    {
        matrixLine *m = matrixLine_alloc(i, j), *ext = matrixLine_alloc(i, 1);
        matrixLine_scan(m);
        printf("\nMatrix m complete\n");
        matrixLine_scan(ext);
        printf("\nMatrix ext complete\n");
        matrixLine *mClone = matrixLine_clone((const matrixLine *) m), *extClone = matrixLine_clone(ext);
        matrixLine *result = matrixLine_Gauss_Method(m, ext);
        matrixLine_print(m);
        printf("\n\n\nresult:\n");
        matrixLine_print(result);
        printf("\n\n\n");
        matrixLine *check = matrixLine_mult_matrixes((const matrixLine *) mClone, (const matrixLine *) ext);
        printf("check:\n");
        matrixLine_print(check);
        printf("\next:\n");
        matrixLine_print(extClone);
        matrixLine_free(mClone);
        matrixLine_free(extClone);
        matrixLine_free(check);
        matrixLine_free(ext);
        matrixLine_free(result);
        matrixLine_free(m);

    }
    else
    {
        printf("Wrong key");
    }
    return 0;
}

/**
Test 1, 2:
5 6 7 8 9
10 11 11 13 13
14 41 -41 41 41
1 2 3 4 5
6 8 9 0 11

Test 12:
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1

1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1

Test 7:
5 6 7 8 9 10
10 11 11 13 13 4
14 41 41 41 41 15
1 2 3 4 5 6
6 8 9 0 11 8

Test Gauss_Method
m:
1 6 3 5 5
3 4 5 6 7
5 6 7 8 9
8 8 13 10 11
9 10 11 12 15

ext:
7 8 9 10 11

result:
-1.435 -0.525 0.358 2.102 0
*/
