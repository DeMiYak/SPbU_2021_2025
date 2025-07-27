#include<stdio.h>
#include<math.h>

void loadup(double *xy, double *xx, double *xi, double *yi, int i, double x[], double y[]){
        for(int k = 0; k < i; k++){
                *xy += x[k]*y[k];
                *xx += x[k]*x[k];
                *xi += x[k];
                *yi += y[k];
                }
}

void arrayx(double x[], double y[], int i){
        for(int k = 0; k < i; k++){
                scanf("%lf%lf", &x[k], &y[k]);
        }
}

void findsolution(double xy, double xx, double xi, double yi, int i){
    double a, b;
    if(xx*i - xi*xi != 0){
        b = (xx*yi - xy*xi)/(xx*i - xi*xi);
        a = (xy*i - xi*yi)/(xx*i - xi*xi);
        printf("y = %lfx + %lf \n", a, b);
        printf("xy = %lf \nxx = %lf \nxi = %lf \nyi = %lf", xy, xx, xi, yi);
        } else printf("Error");
}
