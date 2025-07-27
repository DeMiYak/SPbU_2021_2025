#include"help.h"
#include<math.h>
#include<stddef.h>

enum QuadStatus QuadFunc(double a, double b, double c, double *root1, double *root2){
    if(a != a || b != b || c != c || a == 1.0/0.0 || a == -1.0/0.0 || b == 1.0/0.0 || b == -1.0/0.0 || c == 1.0/0.0 || c == -1.0/0.0){
        return ERROR;
    } else if (a == 0){
        if (b == 0){
            if (c == 0){
                return ANY_NUMBER;
            } else return NO_ROOTS;
        } else {
            if (root1 != NULL && root2 != NULL) *root1 = *root2 = -1*c/b;
            return ONE_ROOT;
        }
    } else {
        double discr = b*b - 4*a*c;
        if (discr > 0){
            if (root1 != NULL) *root1 = (-1*b - sqrt(discr))/(2*a);
            if (root2 != NULL) *root2 = (-1*b + sqrt(discr))/(2*a);
            return TWO_ROOTS;
        } else if (discr == 0){
            if (root1 != NULL && root2 != NULL) *root1 = *root2 = -1*b/(2*a);
            return ONE_ROOT;
        } else return TWO_COMPLEX_ROOTS;
    }
}
