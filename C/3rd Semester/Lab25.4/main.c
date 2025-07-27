#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "stack.h"
#include "PolishCalculator.h"

int main() {
    size_t len = 1000;
    Stack *stack = StackInit();
    char com[100];
    while (strcmp(com, "end") != 0) {
        scanf("%s", com);
        double tempI;
        if (sscanf(com, "%lf", &tempI) == 1) {
            Push(stack, tempI);
        } else {
            if (Calculate(stack, com) == 0)
                StackToStr(stack, NULL, len);
            else
                printf("error\n");
        }
    }
}
