#include<stdio.h>
#include<math.h>

/* c - итеративно */
int iterEuclid (int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a != 0 && b != 0){
        if (a > b){
                a = a%b;
        } else b = b%a;
    }
    return a+b;
}

/* c - рекурсивно */
int recuEuclid (int a, int b) {
    a = abs(a);
    b = abs(b);
    return (a == 0 || b == 0) ? a+b : recuEuclid(b, a%b);
}

/* d */

int NOK (int a, int b){
    int d = iterEuclid(a, b);
    if (d != 0){
            return a*b/d;
    } else return 0;
}
