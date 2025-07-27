#ifndef SUP_H_INCLUDED
#define SUP_H_INCLUDED
// Line
/**
* Функция findab передаёт значения новым коэффициентам;
*/
void findabLine(double xy, double xx, double xi, double yi, size_t n, double* a, double* b);


/**
* Выводит данные о новых коэффициентах, а также сравнивает их со старыми;
*/
void getFullAnswerLine(double delta, double dela, double delb, double anew, double bnew);

/**
* Вычисляет квадратические ошибки линейного уравнения с учётом случайных шумов
*/
void deltaCalcLine(double dela, double delb, size_t n, double *delta, double *wrvala, double *wrvalb, double *wrvaleq);

// Square

/**
* Передаёт значения новым коэффициентам квадратного уравнения
*/
void findabSquare(double x2yC, double xxC, double xx2C, double xyC, double x2x2C, double *a, double *b);

/**
* Выводит данные о новых коэффициентах квадратного уравнения
*/
void getFullAnswerSquare(double delta, double dela, double delb, double delc, double anew, double bnew, double cnew);

/**
* Вычисляет квадратические ошибки линейного уравнения с учётом случайных шумов
*/
void deltaCalcSquare(double dela, double delb, double delc, size_t n, double *delta, double *wrvala, double *wrvalb, double *wrvalc, double *wrvaleq);

/**
* Определяет коэффициенты квадратичного тренда через линейный
* (эмпирический метод минимизации разницы по принципу - начало и конец совпадают)
*/
void findabcQ(double a, double b, size_t n, double *aQ, double *bQ, double *cQ);

int cmp(const double *a, const double *b);
#endif // SUP_H_INCLUDED
