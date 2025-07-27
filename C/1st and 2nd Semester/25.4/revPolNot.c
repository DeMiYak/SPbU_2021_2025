#include<math.h>
#include<string.h>
#include"stack.h"
#include"revPolNot.h"
#include"integrals.h"
#include"functions.h"
/**
* Бинарные арифметические операции: сложение, вычитание, умножение, деление, возведение в степень
* Математические функции
* Константы
* На свой выбор: среднее арифметическое n чисел, *определённый интеграл
*/
int revPolNot(stack *st, char *oper)
{
    if(!strcmp(oper, "e"))
    {
        stack_insert(st, exp(1));
    }
    else if(!strcmp(oper, "pi"))
    {
        stack_insert(st, PI);
    }
    else if(!strcmp(oper, "print"))
    {
        return 0;
    }
    else if(st->length < 1)
    {
        return -1;
    }
    else if(!strcmp(oper, "sin"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, sin(n1));
    }
    else if(!strcmp(oper, "cos"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, cos(n1));
    }
    else if(!strcmp(oper, "tan"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, tan(n1));
    }
    else if(!strcmp(oper, "asin"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, asin(n1));
    }
    else if(!strcmp(oper, "acos"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, acos(n1));
    }
    else if(!strcmp(oper, "atan"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, atan(n1));
    }
    else if(!strcmp(oper, "sinh"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, sinh(n1));
    }
    else if(!strcmp(oper, "cosh"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, cosh(n1));
    }
    else if(!strcmp(oper, "tanh"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, tanh(n1));
    }
    else if(!strcmp(oper, "sqrt"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, sqrt(n1));
    }
    else if(!strcmp(oper, "asinh"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, asinh(n1));
    }
    else if(!strcmp(oper, "acosh"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, acosh(n1));
    }
    else if(!strcmp(oper, "atanh"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, atanh(n1));
    }
    else if(!strcmp(oper, "exp"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, exp(n1));
    }
    else if(!strcmp(oper, "Stirling"))
    {
        double n1 = stack_pop_tail(st);
        stack_insert(st, sqrt(2*PI*n1)*pow(n1/e, n1));
    }
    else if(!strcmp(oper, "inv"))
    {
        stack_insert(st, (double) 1/stack_pop_tail(st));
    }
    else if(!strcmp(oper, "rev"))
    {
        stack_insert(st, -stack_pop_tail(st));
    }
    else if(!strcmp(oper, "del"))
    {
        stack_pop_tail(st);
    }
    else if(st->length < 2)
    {
        return -1;
    }
    else if(!strcmp(oper, "+"))
    {
        double n1 = stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        stack_insert(st, n2 + n1);
    }
    else if(!strcmp(oper, "-"))
    {
        double n1 = stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        stack_insert(st, n2 - n1);
    }
    else if(!strcmp(oper, "*"))
    {
        double n1 = stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        stack_insert(st, n2*n1);
    }
    else if(!strcmp(oper, "/"))
    {
        double n1 = stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        stack_insert(st, n2/n1);
    }
    else if(!strcmp(oper, "^"))
    {
        double n1 = stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        stack_insert(st, pow(n2, n1));
    }
    else if(!strcmp(oper, "avArith"))
    {
        long int count = (long int) stack_pop_tail(st);
        double sum = 0;
        for(long int i = 0; i < count; ++i)
        {
            double n1 = stack_pop_tail(st);
            if(n1 != 0/0.0 && st->length)
            {
                sum += n1;
            }
            else
            {
                count = i;
                break;
            }
        }
        if(count > 0)
        {
            stack_insert(st, sum/count);
        }
        else
        {
            stack_insert(st, 0);
        }
    }
    else if(st->length < 3)
    {
        return -1;
    }
    else if(!strcmp(oper, "integralExp"))
    {
        long int n1 = (long int) stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        double n3 = stack_pop_tail(st);
        if(n1 > 0)
        {
            stack_insert(st, avrectintegr(n3, n2, exponential, n1, NULL));
        }
        else return -1;
    }
    else if(!strcmp(oper, "integralSin"))
    {
        long int n1 = (long int) stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        double n3 = stack_pop_tail(st);
        if(n1 > 0)
        {
            stack_insert(st, avrectintegr(n3, n2, sinus, n1, NULL));
        }
        else return -1;
    }
    else if(!strcmp(oper, "integralCos"))
    {
        long int n1 = (long int) stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        double n3 = stack_pop_tail(st);
        if(n1 > 0)
        {
            stack_insert(st, avrectintegr(n3, n2, cosin, n1, NULL));
        }
        else return -1;
    }
    else if(!strcmp(oper, "integralLog"))
    {
        long int n1 = (long int) stack_pop_tail(st);
        double n2 = stack_pop_tail(st);
        double n3 = stack_pop_tail(st);
        if(n1 > 0)
        {
            stack_insert(st, avrectintegr(n3, n2, logarithmic, n1, NULL));
        }
        else return -1;
    }
    return 0;
}
