#ifndef Pigeon
#define Pigeon

// Рассматривает ситуации, которые могут получиться во время вычислений
enum QuadStatus
{
    ERROR,              /*NAN or INF*/
    TWO_ROOTS,          /*Два корня*/
    ONE_ROOT,           /*Один корень*/
    ANY_NUMBER,         /*Любое вещественное число*/
    NO_ROOTS,           /*Нет корней*/
    TWO_COMPLEX_ROOTS   /*Два комплексных корня*/
};
// Вычисляет корни квадратного уравнения и указывает их число
enum QuadStatus QuadFunc(double a, double b, double c, double *root1, double *root2);



#endif // Pigeon
