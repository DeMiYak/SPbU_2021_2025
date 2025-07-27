//
// Created by vadim on 08.04.2022.
//

#include <string.h>
#include <math.h>
#include "PolishCalculator.h"


int Calculate(Stack *stack, char *operation) {
    if (strcmp(operation, "e") == 0) {
        Push(stack, exp(1));
    } else if (strcmp(operation, "print") == 0) {
        return 0;
    } else if (stack->len < 1)
        return -1;
    else if (strcmp(operation, "del") == 0) {
        Pop(stack);
    } else if (strcmp(operation, "inv") == 0) {
        Push(stack, 1 / Pop(stack));
    } else if (strcmp(operation, "rev") == 0) {
        Push(stack, -Pop(stack));
    } else if (strcmp(operation, "sin") == 0) {
        Push(stack, sin(Pop(stack)));
    } else if (strcmp(operation, "cos") == 0) {
        Push(stack, cos(Pop(stack)));
    } else if (strcmp(operation, "sh") == 0) {
        Push(stack, sinh(Pop(stack)));
    } else if (strcmp(operation, "ch") == 0) {
        Push(stack, cosh(Pop(stack)));
    } else if (strcmp(operation, "arcsin") == 0) {
        Push(stack, asin(Pop(stack)));
    } else if (strcmp(operation, "arccos") == 0) {
        Push(stack, acos(Pop(stack)));
    } else if (strcmp(operation, "arcsh") == 0) {
        Push(stack, asinh(Pop(stack)));
    } else if (strcmp(operation, "arcch") == 0) {
        Push(stack, acosh(Pop(stack)));
    } else if (strcmp(operation, "sqrt") == 0) {
        Push(stack, sqrt(Pop(stack)));
    } else if (strcmp(operation, "exp") == 0) {
        Push(stack, exp(Pop(stack)));
    } else if (stack->len < 2)
        return -1;
    else if (strcmp(operation, "+") == 0) {
        double n1 = Pop(stack);
        double n2 = Pop(stack);
        Push(stack, n1 + n2);
    } else if (strcmp(operation, "-") == 0) {
        double n1 = Pop(stack);
        double n2 = Pop(stack);
        Push(stack, n2 - n1);
    } else if (strcmp(operation, "*") == 0) {
        double n1 = Pop(stack);
        double n2 = Pop(stack);
        Push(stack, n2 * n1);
    } else if (strcmp(operation, "/") == 0) {
        double n1 = Pop(stack);
        double n2 = Pop(stack);
        Push(stack, n2 / n1);
    } else if (strcmp(operation, "^") == 0) {
        double n1 = Pop(stack);
        double n2 = Pop(stack);
        Push(stack, pow(n2, n1));
    } else if (strcmp(operation, "sr") == 0) {
        int count = (int) Pop(stack);
        double sum = 0;
        for (int i = 0; i < count; ++i) {
            double el = Pop(stack);
            if (el != 0.0 / 0.0) {
                sum += el;
            } else {
                count = i;
                break;
            }
        }
        if (count > 0) {
            Push(stack, sum / count);
        } else {
            Push(stack, 0);
        }
    } else {
        return 1;
    }
    return 0;
}
