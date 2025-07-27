//
// Created by  on 22.10.2021.
//

#ifndef LAB9_4_QUADRATICEQUATION_H
#define LAB9_4_QUADRATICEQUATION_H

enum result {
    TWO_RESULT,
    ONE_RESULT,
    COMPLEX_RESULT,
    LINE_RESULT,
    NO_RESULT,
    INF_RESULT,
    ERROR
};

enum result QuadraticEquationFunc(int a, int b, int c, double *x1, double *x2);

#endif //LAB9_4_QUADRATICEQUATION_H