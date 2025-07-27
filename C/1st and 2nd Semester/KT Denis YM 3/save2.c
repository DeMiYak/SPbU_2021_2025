#include<stdio.h>
#include<math.h>
#include"save.h"


enum triangle CheckTriangle(double a, double b, double c){
    if(a < b){
        double k = a;
        a = b;
        b = k;
    }
    if(a < c){
        double k = a;
        a = c;
        c = k;
    }
    if(b < c){
        double k = b;
        b = c;
        c = k;
    }
    double result = b*b + c*c - a*a;
    if(a == b + c){
        return STRAIGHT;
    }
    else if(a > b + c){
        return NONEXISTENT;
    }
    else if(result < 0){
        return BLUNT;
    }
    else if(result == 0){
        return RIGHT;
    }
    else{
        return SHARP;
    }
}
