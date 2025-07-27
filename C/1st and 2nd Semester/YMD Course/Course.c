/**
* Яковлев Денис Михайлович (С)
* Программа по созданию линейного приближения
* по методу наименьших квадратов
*
* Ввод:
* Коэффициенты a, b;
* Размер шума s;
* Число циклов ccl;
* Количество подряд идущих натуральных x - n;
*
* Вывод:
* 1. Новые коэффициенты anew и bnew;
* 2. Сумма разностей - дельта между "новыми" y и "старыми" y;
* 3. Суммы xi, yi и суммы произведений xx, xy;
* 4. Квадрат разницы между новыми и старыми коэффициентами
* 5. Ошибочные значения коэффициента а, b и линейного уравнения
*/



/**
=========

Денис, здравствуйте!
Я всё получила.
Теперь, собственно, финальное задание.
Вы генерируете временные ряды много раз (M) (задавайте все параметры внутри кода кроме числа повторов M), временные ряды состоят из тренда, квадратичного или линейного, и шума.
Каждый раз оцениваете параметры тренда, считайте среднеквадратическое отклонение оцененного тренда от настоящего тренда, среднеквадратическое отклонение оцененного тренда от всего ряда (тренд+шум),
среднеквадратическое отклонение прогноза по оцененному тренду от прогноза по настоящему тренду.
Длину ряда можно взять равной 100. Прогнозы можно рассмотреть — на 1 и на 10 точек вперед. Тренды подбирайте так, чтобы линейный и квадратичный были очень похожи.

Среднеквадратическое отклонение (СКО) — это средний квадрат разности. Полученные СКО усредняете по M повторам.

Таким образом, получите 12 чисел (два вида тренда и 4 средних СКО для каждого).
Сначала напишите мне, какие неравенства вы предполагаете для полученных 12 СКО (не в том смысле, что сравнивать нужно все со всеми, а просто напишите те пары, для которых,
как вам кажется, вы можете предсказать, что получится). Пришлите мне свои предположения как можно раньше, до написания программы
Проверьте, что получается, с помощью программы.
НЭ

=========
*/



#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"sup.h"
#include"matrixSolve.h"
#include"matrixInitFunc.h"
#include"matrixStruct.h"
#include"matrixOper.h"
#define M 100000
int main()
{
    //
    int re;
    printf("Include c? (0: NO, 1: YES): ");
    scanf("%d", &re);
    double a, b, c;                                // Коэффициенты a, b
    if(re)
    {
        printf("Enter the coefficients (a, b, c): ");
        scanf("%lf%lf%lf", &a, &b, &c);
    }
    else
    {
        c = 0;
        printf("Enter the coefficients (a, b): ");
        scanf("%lf%lf", &a, &b);
    }
    double aQ, bQ, cQ;
    //
    double s;                                   // Размер шума
    printf("Enter the random noice scale: ");
    scanf("%lf", &s);
    //
    // size_t ccl = M;                           // Число циклов (созданных временных рядов)
    size_t ccl = 4;
    // size_t ccl;
    // printf("Enter the number of cycles: ");
    // scanf("%Iu", &ccl);
    //
    size_t n = 100;                             // Число x-координат (натуральные числа от 1 до n)
    // printf("Enter the number of x-coordinates: ");
    // scanf("%Iu", &n);
    assert(n >= 2);                             // Условие на наличие хотя бы двух точек
    printf("\n");
    //
    findabcQ(a, b, n, &aQ, &bQ, &cQ);
    printf("Old coefficients: a = %.10lf, b = %.10lf\n\n", a, b); // Вывод старых коэффициентов
    printf("Approximate quadratic coefficients from linear equation:\naQ = %.16lf\nbQ = %.16lf\ncQ = %.16lf\n\n", aQ, bQ, cQ);
    printf("1: %lf\n2: %lf\n3: %lf\n\n", aQ + bQ + cQ - a - b, n*n/4*aQ + n/2*bQ + cQ - n/2*a - b, n*n*aQ + n*bQ + cQ - n*a - b);
    //
    int p;
    printf("Choose the method: \n1. Linear Normal\n2. Linear Centralised\n3. Linear Matrix\n4. Quadratic Centralised Matrix\n5. Comparing Quadratic and Linear Equations\nEnter the number: ");
    scanf("%d", &p);
    //
    int d;                                                              // Проверка на вывод полных данных в циклах
    printf("Do you want to see the answers? (press 0 to refuse): ");
    scanf("%d", &d);
    //
    double wrvala = 0, wrvalb = 0, wrvalc = 0, wrvaleq = 0; // усреднённые среднеквадратические ошибки для а, b коэффициентов и линейного уравнения
    //
    if(p == 1)                  // Обычный метод
    {
        for(size_t j = 1; j <= ccl; ++j){
            printf("// Cycle #%Iu:\n", j);
            srand((j*(int)a + (int)b)%RAND_MAX);// Функция создания последовательности случайных чисел
            //
            double xi = (n*n + n)/2;            // Сумма xj
            double xx = (n*(n+1)*(2*n+1))/6;    // Сумма произведений xj * xj
            double yi = 0;                      // Сумма yj
            double xy = 0;                      // Сумма произведений xj * yj
            double delta = 0;                   // Разность, вычисляемая методом наименьших квадратов
            double anew, bnew;                  // Новые коэффициенты для линейного уравнения
            //
            for(size_t i = 1; i <= n; ++i){
                double e = (double) rand()/RAND_MAX*s - (double) s/2; // Генератор случайных шумов
                double yt = a*i + b + e;                              // Линейное уравнение со случайной величиной
                yi += yt;
                xy += i*yt;
            }
            findabLine(xy, xx, xi, yi, n, &anew, &bnew);    // Вызов функции по нахождению новых коэффициентов

            double dela = anew - a, delb = bnew - b;    // Разности между новыми и старыми коэффициентами

            deltaCalcLine(dela, delb, n, &delta, &wrvala, &wrvalb, &wrvaleq);   // Функция, подсчитывающая сумму для ошибочных значений
            //
            if(d) getFullAnswerLine(delta, dela, delb, anew, bnew);          // Вывод на экран значений, связанных с новыми коэффициентами
        }
    }
    else if (p == 2)                // Нормированный метод
    {
        for(size_t j = 1; j <= ccl; ++j){
                printf("// Cycle #%Iu:\n", j);
                srand((j*(int)a + (int)b)%RAND_MAX);// Функция создания последовательности случайных чисел
                //
                double xi = (n*n + n)/2;            // Сумма xj
                double xx = (n*(n+1)*(2*n+1))/6;    // Сумма произведений xj * xj
                double yi = 0;                      // Сумма yj
                double xy = 0;                      // Сумма произведений xj * yj
                double delta = 0;                   // Разность, вычисляемая методом наименьших квадратов
                double anew, bnew;                  // Новые коэффициенты для линейного уравнения
                double my[n], mx[n], mxe[n];
                //
                for(size_t i = 1; i <= n; ++i){
                    double e = (double) rand()/RAND_MAX*s - (double) s/2; // Генератор случайных шумов
                    double yt = a*i + b + e;                              // Линейное уравнение со случайной величиной
                    my[i-1] = yt;
                    mx[i-1] = i;
                    mxe[i-1] = e;
                    yi += yt;
                    xy += i*yt;
                }
                /*
                Подсчитаны: значения по yt, сумма этих значений yi
                и сумма произведений xi * yi.
                Следующий этап - подсчёт новых сумм
                Воспользуюсь формулой в конце страницы 2.
                */
                double xC = 0, xyC = 0, yi_av = yi/n, xi_av = xi/n;
                for(size_t i = 0; i < n; ++i)
                {
                    my[i] -= yi_av;
                    mx[i] -= xi_av;
                }
                for(size_t i = 0; i < n; ++i)
                {
                    xC += pow(mx[i], 2);
                    xyC += mx[i]*my[i];
                }
                printf("\naC = %.10lf\nbC = %.10lf\nxC = %.10lf\nxyC = %.10lf\n", xyC/xC, yi_av - xyC/xC*xi_av, xC, xyC);
                findabLine(xy, xx, xi, yi, n, &anew, &bnew);    // Вызов функции по нахождению новых коэффициентов

                double dela = anew - a, delb = bnew - b;    // Разности между новыми и старыми коэффициентами

                deltaCalcLine(dela, delb, n, &delta, &wrvala, &wrvalb, &wrvaleq);   // Функция, подсчитывающая сумму для ошибочных значений
                //
                if(d) getFullAnswerLine(delta, dela, delb, anew, bnew);          // Вывод на экран значений, связанных с новыми коэффициентами
            }
    }
    else if(p == 3)             // Матричный метод
    {
        for(size_t j = 1; j <= ccl; ++j){
                printf("// Cycle #%Iu:\n", j);
                srand((j*(int)a + (int)b)%RAND_MAX);// Функция создания последовательности случайных чисел
                //
                double xi = (n*n + n)/2;            // Сумма xj
                double xx = (n*(n+1)*(2*n+1))/6;    // Сумма произведений xj * xj
                double yi = 0;                      // Сумма yj
                double xy = 0;                      // Сумма произведений xj * yj
                double delta = 0;                   // Разность, вычисляемая методом наименьших квадратов
                double anew, bnew;                  // Новые коэффициенты для линейного уравнения
                double detInv = 1/(xx*n - xi*xi);          // Детерминант для обратной матрицы
                matrixLine *mInv = matrixLine_alloc(2, 2); // Матрица для подсчёта 1: (A(T)A)^(-1)
                matrixLine *bM = matrixLine_alloc(2, 1);   // Матрица для подсчёта 2: (A(T)b)
                //
                for(size_t i = 1; i <= n; ++i){
                    double e = (double) rand()/RAND_MAX*s - (double) s/2; // Генератор случайных шумов
                    double yt = a*i + b + e;                              // Линейное уравнение со случайной величиной
                    yi += yt;
                    xy += i*yt;
                }
                //
                mInv->mat[0] = n;
                mInv->mat[1] = mInv->mat[2] = -xi;
                mInv->mat[3] = xx;
                matrixLine_mult_scalar_all(mInv, detInv);
                // matrixLine_print(mInv);
                // printf("\n\n\nxx = %lf\nxi = %lf\n n = %Iu\n", xx, xi, n);
                //
                bM->mat[0] = xy;
                bM->mat[1] = yi;
                matrixLine *xVector = matrixLine_mult_matrixes((const matrixLine *) mInv, (const matrixLine *) bM);
                matrixLine_print(mInv);
                printf("\n\n\n");
                matrixLine_print(bM);
                printf("\n\n\n");
                matrixLine_print(xVector);
                printf("\n\n\n");
                findabLine(xy, xx, xi, yi, n, &anew, &bnew);    // Вызов функции по нахождению новых коэффициентов

                double dela = anew - a, delb = bnew - b;    // Разности между новыми и старыми коэффициентами

                deltaCalcLine(dela, delb, n, &delta, &wrvala, &wrvalb, &wrvaleq);   // Функция, подсчитывающая сумму для ошибочных значений
                //
                if(d) getFullAnswerLine(delta, dela, delb, anew, bnew);          // Вывод на экран значений, связанных с новыми коэффициентами
                matrixLine_free(mInv);
                matrixLine_free(bM);
                matrixLine_free(xVector);
            }
    }
    else if(p == 4) // Матричный метод (Квадратичный тренд)
    {
        for(size_t j = 1; j <= ccl; ++j){
            printf("// Cycle #%Iu:\n", j);
            srand((j*(int)a + (int)b + (int)c)%RAND_MAX);// Функция создания последовательности случайных чисел
            //
            double xi = (n*n + n)/2;            // Сумма xj
            double xx = (n*(n+1)*(2*n+1))/6;    // Сумма произведений xj * xj
            double yi = 0;                      // Сумма yj
            // double xy = 0;                      // Сумма произведений xj * yj
            double delta = 0;                   // Разность, вычисляемая методом наименьших квадратов
            double anew, bnew, cnew;            // Новые коэффициенты для линейного уравнения
            double my[n], mx[n], mxx[n], mxe[n];// Массивы сумм
            double detInv;                         // Обратный детерминант
            matrixLine *mInv = matrixLine_alloc(2, 2);
            matrixLine *bM = matrixLine_alloc(2, 1);
            if(!mInv || !bM) return 0;
            //
            for(size_t i = 1; i <= n; ++i){
                double e = (double) rand()/RAND_MAX*s - (double) s/2;           // Генератор случайных шумов
                double yt = a*i*i + b*i + c + e;                                // Линейное уравнение со случайной величиной
                my[i-1] = yt;
                mx[i-1] = i;
                mxx[i-1] = i*i;
                mxe[i-1] = e;
                yi += yt;
                // xy += i*yt;
            }
            /*
            Подсчитаны: значения по yt, сумма этих значений yi
            и сумма произведений xi * yi.
            Следующий этап - подсчёт новых сумм
            Воспользуюсь формулой в конце страницы 2.
            */
            double xxC = 0, xyC = 0, x2yC = 0, xx2C = 0, x2x2C = 0;
            double yi_av = yi/n, xi_av = xi/n, xxi_av = xx/n;
            for(size_t i = 0; i < n; ++i) // Создание центрированных данных (симуляция)
            {
                my[i] -= yi_av;
                mx[i] -= xi_av;
                mxx[i] -= xxi_av;
            }
            for(size_t i = 0; i < n; ++i) // Без внедрения погрешностей
            {
                xxC += pow(mx[i], 2);
                xyC += mx[i]*my[i];
                x2yC += mxx[i]*my[i];
                xx2C += mx[i]*mxx[i];
                x2x2C += pow(mxx[i], 2);
            }
            //
            mInv->mat[0] = xxC;
            mInv->mat[1] = mInv->mat[2] = -xx2C;
            mInv->mat[3] = x2x2C;
            bM->mat[0] = x2yC;
            bM->mat[1] = xyC;
            detInv = 1/(x2x2C*xxC - xx2C*xx2C);
            //
            matrixLine_mult_scalar_all(mInv, detInv);
            matrixLine *xVector = matrixLine_mult_matrixes((const matrixLine *)mInv, (const matrixLine *)bM);
            matrixLine_print(mInv);
            printf("\n\n");
            matrixLine_print(bM);
            printf("\n\n");
            /*
            matrixLine_print(xVector);
            printf("\n\n");
            */
            if(!xVector) return 0;
            anew = xVector->mat[0];
            bnew = xVector->mat[1];
            cnew = yi_av - a*xxi_av - b*xi_av;      // Коэффициент C
            printf("a = %.10lf\nb = %.10lf\nc = %.10lf\n", anew, bnew, cnew);
            //
            // findabSquare(x2yC, xxC, xx2C, xyC, x2x2C ,&anew, &bnew);    // Вызов функции по нахождению новых коэффициентов
            //
            double dela = anew - a, delb = bnew - b, delc = cnew - c;    // Разности между новыми и старыми коэффициенами
            deltaCalcSquare(dela, delb, delc, n, &delta, &wrvala, &wrvalb, &wrvalc, &wrvaleq);   // Функция, подсчитывающая сумму для ошибочных значений
            //
            if(d) getFullAnswerSquare(delta, dela, delb, delc, anew, bnew, cnew);          // Вывод на экран значений, связанных с новыми коэффициентами
            matrixLine_free(bM);
            matrixLine_free(mInv);
            matrixLine_free(xVector);
            }
    }

    else if(p == 5) // Смешанный метод (сравнение квадратичного и линейного трендов)
    {
        clock_t timerStart = clock();
        double deLOne = 0, deLTwo = 0, prL = 0, deLQOne = 0, deLQTwo = 0, prLQ = 0; // Разницы для линейного тренда
        double deQOne = 0, deQTwo = 0, prQ = 0, deQLOne = 0, deQLTwo = 0, prQL = 0; // Разницы для квадратичного тренда
        for(size_t j = 1; j <= ccl; ++j){
            if(d) printf("// Cycle #%Iu:\n", j);
            srand((j*(int)a + (int)b)%RAND_MAX);// Функция создания последовательности случайных чисел
            //
            double xi = (n*n + n)/2, xi_av = xi/n;            // Сумма xj
            double xx = (n*(n+1)*(2*n+1))/6, xxi_av = xx/n;    // Сумма произведений xj * xj
            double yi = 0;                      // Сумма yj
            double xy = 0;                      // Сумма произведений xj * yj
            double aLineL, bLineL;// Новые коэффициенты для линейного уравнения
            double myL[n], mx[n], mxx[n];// Массивы сумм
            // Linear
            for(size_t i = 1; i <= n; ++i){
                double e = (double) rand()/RAND_MAX*s - (double) s/2;           // Генератор случайных шумов
                double yt = a*i + b + e;                                // Линейное уравнение со случайной величиной
                myL[i-1] = yt;
                mx[i-1] = i - xi_av;
                mxx[i-1] = i*i - xxi_av;
                yi += yt;
                xy += i*yt;
            }
            //Line in Linear
            findabLine(xy, xx, xi, yi, n, &aLineL, &bLineL);
            // double delaLineL = aLineL - a, delbLineL = bLineL - b;

            // Quadratic in Linear
            double yiL_av = yi/n;
            double aQnewL, bQnewL, cQnewL;
            double xxC = 0, xyC = 0, x2yC = 0, xx2C = 0, x2x2C = 0;
            for(size_t i = 0; i < n; ++i) // Без внедрения погрешностей
            {
                double yL = myL[i] - yiL_av;
                xxC += pow(mx[i], 2);
                xyC += mx[i]*yL;
                x2yC += mxx[i]*yL;
                xx2C += mx[i]*mxx[i];
                x2x2C += pow(mxx[i], 2);
            }
            findabSquare(x2yC, xxC, xx2C, xyC, x2x2C, &aQnewL, &bQnewL);
            cQnewL = yiL_av - aQnewL*xxi_av - bQnewL*xi_av;
            // double delaQL = aQ - aQnewL, delbQL = bQ - bQnewL, delcQL = cQ - cQnewL;
            if(d) printf("Approximate linear coefficients for linear temporal series:\na = %lf\nb = %lf\nApproximate quadric coefficients for linear temporal series:\na = %lf\nb = %lf\nc = %lf\n\n", aLineL, bLineL, aQnewL, bQnewL, cQnewL);

            //

            // Quadratic
            yi = 0, xy = 0;
            double myQ[n];
            double aQnewQ, bQnewQ, cQnewQ;
            double aLineQ, bLineQ;
            for(size_t i = 1; i <= n; ++i)
            {
                double e = (double) rand()/RAND_MAX*s - (double) s/2;
                double yt = aQ*i*i + bQ*i + cQ + e;
                myQ[i - 1] = yt;
                yi += yt;
                xy += i*yt;
            }
            // Line in Quadratic
            findabLine(xy, xx, xi, yi, n, &aLineQ, &bLineQ);
            // double delaLineQ = a - aLineQ, delbLineQ = b - bLineQ;
            // Quadratic in Quadratic
            double yiQ_av = yi/n;
            xxC = 0;
            xyC = 0;
            x2yC = 0;
            xx2C = 0;
            x2x2C = 0;
            for(size_t i = 0; i < n; ++i) // Без внедрения погрешностей
            {
                double yQ = myQ[i] - yiQ_av;
                xxC += pow(mx[i], 2);
                xyC += mx[i]*yQ;
                x2yC += mxx[i]*yQ;
                xx2C += mx[i]*mxx[i];
                x2x2C += pow(mxx[i], 2);
            }
            findabSquare(x2yC, xxC, xx2C, xyC, x2x2C, &aQnewQ, &bQnewQ);
            cQnewQ = yiQ_av - aQnewQ*xxi_av - bQnewQ*xi_av;
            if(d) printf("Approximate linear coefficients for quadratic temporal series:\na = %lf\nb = %lf\nApproximate quadric coefficients for quadratic temporal series:\na = %lf\nb = %lf\nc = %lf\n\n", aLineQ, bLineQ, aQnewQ, bQnewQ, cQnewQ);
            // double delaQ = aQnewQ - aQ, delbQ = bQnewQ - bQ, delcQ = cQnewQ - cQ;
            double prN = n + 10;

            // Calculation
            for(size_t i = 1; i <= prN; ++i)
            {
                double tempLtoL = aLineL*i + bLineL;
                double tempQtoL = aQnewL*i*i + bQnewL*i + cQnewL;
                double tempLtoQ = aLineQ*i + bLineQ;
                double tempQtoQ = aQnewQ*i*i + bQnewQ*i + cQnewQ;
                double tempLor = a*i + b;
                double tempQor = aQ*i*i + bQ*i + cQ;
                /*
                double tempL = aLine*i + bLine;
                double tempQ = aQnew*i*i + bQnew*i + cQnew;
                double tempLor = a*i + b;
                double tempQor = aQ*i*i + bQ*i + cQ;
                double tempDeL = delaLine*i + delbLine;
                double tempDeQ = delaQ*i*i + delbQ*i + delcQ;
                double resQL = tempQor - tempL, resLQ = tempLor - tempQ;
                */
                if(i <= n)
                {
                    deLOne += pow(tempLtoL - tempLor, 2);
                    deLTwo += pow(tempLtoL - myL[i-1], 2);
                    deQOne += pow(tempQtoQ - tempQor, 2);
                    deQTwo += pow(tempQtoQ - myQ[i-1], 2);
                    deLQOne += pow(tempQtoL - tempLor, 2);
                    deLQTwo += pow(tempQtoL - myL[i-1], 2);
                    deQLOne += pow(tempLtoQ - tempQor, 2);
                    deQLTwo += pow(tempLtoQ - myQ[i-1], 2);
                }
                else
                {
                    prL += pow(tempLtoL - tempLor, 2);
                    prQ += pow(tempQtoQ - tempQor, 2);
                    prLQ += pow(tempQtoL - tempLor, 2);
                    prQL += pow(tempLtoQ - tempQor, 2);
                }
            }
            if(d) printf("\n//////\n\n\n");
        }
        deLOne = pow(deLOne/n/ccl,0.5);
        deLTwo = pow(deLTwo/n/ccl,0.5);
        deQOne = pow(deQOne/n/ccl,0.5);
        deQTwo = pow(deQTwo/n/ccl,0.5);
        deLQOne = pow(deLQOne/n/ccl,0.5);
        deLQTwo = pow(deLQTwo/n/ccl,0.5);
        deQLOne = pow(deQLOne/n/ccl,0.5);
        deQLTwo = pow(deQLTwo/n/ccl,0.5);
        prQ = pow(prQ/10/ccl,0.5);
        prLQ = pow(prLQ/10/ccl,0.5);
        prL = pow(prL/10/ccl,0.5);
        prQL = pow(prQL/10/ccl,0.5);
        printf("\n\ndeLOne = %.4lf\ndeLTwo = %.4lf\ndeQOne = %.4lf\ndeQTwo = %.4lf\ndeLQOne = %.4lf\ndeLQTwo = %.4lf\ndeQLOne = %.4lf\ndeQLTwo = %.4lf\nprQ = %.4lf\nprLQ = %.4lf\nprL = %.4lf\nprQL = %.4lf\n", deLOne, deLTwo, deQOne, deQTwo, deLQOne, deLQTwo, deQLOne, deQLTwo, prQ, prLQ, prL, prQL);
        //printf("%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf\n%.4lf", a, b, deLOne, deLTwo, deQOne, deQTwo, deLQOne, deLQTwo, deQLOne, deQLTwo, prQ, prLQ, prL, prQL);
        clock_t timerStop = clock();
        double seconds = (double)(timerStop - timerStart)/CLOCKS_PER_SEC;
        printf("\nTotal time: %.4lf seconds\n\nn = %Iu\ns = %.4lf\nccl = %Iu\na = %.4lf\nb = %.4lf\naQ = %.4lf\nbQ = %.4lf\ncQ = %.4lf\n", seconds, n, s, ccl, a, b, aQ, bQ, cQ);
        /*
        double a[12];
        a[0] = deLOne;
        a[1] = deLTwo;
        a[2] = deQOne;
        a[3] = deQTwo;
        a[4] = deLQOne;
        a[5] = deLQTwo;
        a[6] = deQLOne;
        a[7] = deQLTwo;
        a[8] = prQ;
        a[9] = prQL;
        a[10] = prL;
        a[11] = prLQ;
        for(size_t i = 0; i < 11; i++)
        {
            printf("\n");
            for(size_t j = i+1; j <= 11; j++)
            {
                printf("%d\n",cmp((const double *)&a[i], (const double *)&a[j]));
            }
            printf("\n");
        }
        */
        printf("%d\n", cmp((const double *)&deLTwo, (const double *)&deLQTwo));
    }
    else printf("Incorrect input\n...Closing the program");
    return 0;
    //
    // wrvala = pow(wrvala/ccl, 0.5);          // Ошибочное значение коэффициента a
    // wrvalb = pow(wrvalb/ccl, 0.5);          // Ошибочное значение коэффициента b
    // wrvalc = pow(wrvalc/ccl, 0.5);          // Ошибочное значение коэффициента c
    // wrvaleq = pow(wrvaleq/(n*ccl), 0.5);    // Ошибочное значение линейного уравнения
    // printf("wrvala = %.10lf\nwrvalb = %.10lf\nwrvalc = %.10lf\nwrvaleq = %.10lf\n", wrvala, wrvalb, wrvalc, wrvaleq);
}


/**
Test 1.1:
deLOne = 4.094624
deLTwo = 28.584275
deQOne = 4.982548
deQTwo = 28.435326
deLQOne = 5.035535
deLQTwo = 29.313204
deQLOne = 4.153867
deQLTwo = 29.164914
prQ = 10.544738
prLQ = 10.548035
prL = 6.243677
prQL = 6.246971

Total time: 13.2890000000000000 seconds

n = 100
s = 100.000000
ccl = 100000
a = 30000.000000
b = -513.000000
aQ = 0.000408
bQ = 29999.958776
cQ = -512.959184


Test 1.2:

deLOne = 2.047312
deLTwo = 14.292137
deQOne = 2.491274
deQTwo = 14.217663
deLQOne = 2.595364
deLQTwo = 14.670129
deQLOne = 2.167919
deQLTwo = 14.595717
prQ = 5.272369
prLQ = 5.279136
prL = 3.121839
prQL = 3.130987

Total time: 13.1270000000000010 seconds

n = 100
s = 50.0000000000000000
ccl = 100000
a = 30000.0000000000000000
b = -513.0000000000000000
aQ = 0.0004081632653061
bQ = 29999.9587755102040000
cQ = -512.9591836734689400

Test 2:

deLOne = 2.048373
deLTwo = 14.292308
deQOne = 2.491586
deQTwo = 14.217551
deLQOne = 2.595779
deLQTwo = 14.670514
deQLOne = 2.169007
deQLTwo = 14.595781
prQ = 5.272071
prLQ = 5.279032
prL = 3.122747
prQL = 3.131887

Total time: 13.3340000000000000 seconds

n = 100
s = 50.0000000000000000
ccl = 100000
a = 10000.0000000000000000
b = -40000.0000000000000000
aQ = 0.0004081632653061
bQ = 9999.9587755102038000
cQ = -39999.9591836734690000

Test 3.1:

deLOne = 2.935847
deLTwo = 14.862702
deQOne = 1.486716
deQTwo = 14.236660
deLQOne = 0.796881
deLQTwo = 15.295444
deQLOne = 2.318863
deQLTwo = 14.694428
prQ = 0.745184
prLQ = 0.969938
prL = 1.563507
prQL = 1.801053

Total time: 13.3030000000000010 seconds

n = 100
s = 50.0000000000000000
ccl = 100000
a = 0.0000100000000000
b = 30.0000000000000000
aQ = 0.0004081632653061
bQ = -0.0412144897959184
cQ = 30.0408163265306140

Test 3.2:
deLOne = 2.935847
deLTwo = 14.862702
deQOne = 1.486716
deQTwo = 14.236660
deLQOne = 0.796881
deLQTwo = 15.295444
deQLOne = 2.318863
deQLTwo = 14.694428
prQ = 0.745184
prLQ = 0.969938
prL = 1.563507
prQL = 1.801053

Total time: 1.6550000000000000 seconds

n = 100
s = 50.0000000000000000
ccl = 10000
a = 0.0000100000000000
b = 30.0000000000000000
aQ = 0.0004081632653061
bQ = -0.0412144897959184
cQ = 30.0408163265306140

Test 4:

deLOne = 2.041755
deLTwo = 14.293334
deQOne = 2.487245
deQTwo = 14.218039
deLQOne = 2.591355
deLQTwo = 14.668449
deQLOne = 2.161753
deQLTwo = 14.593659
prQ = 5.296767
prLQ = 5.303489
prL = 3.125134
prQL = 3.134362

Total time: 1.6719999999999999 seconds

n = 100
s = 50.0000000000000000
ccl = 10000
a = 100000.0000000000000000
b = -55555555.0000000000000000
aQ = 0.0004081632653061
bQ = 99999.9587755102110000
cQ = -55555554.9591836780000000

Test 5:
deLOne = 2.0482320492188570
deLTwo = 14.2923073452012520
deQOne = 2.4915787834026526
deQTwo = 14.2180188581616150
deLQOne = 2.5956480737417746
deLQTwo = 14.6706472737087190
deQLOne = 2.1684693988317001
deQLTwo = 14.5963620017627190
prQ = 5.2735122068446572
prLQ = 5.2802075542407838
prL = 3.1228460053408997
prQL = 3.1322743624279306

Total time: 13.5980000000000010 seconds

n = 100
s = 50.0000000000000000
ccl = 100000
a = -45324.0000000000000000
b = 16.0000000000000000
aQ = 0.0004081632653061
bQ = -45324.0412244897960000
cQ = 16.0408163265310580


Test 6:

deLOne = 0.8189822956338747
deLTwo = 5.7168907916273319
deQOne = 0.9965161256358505
deQTwo = 5.6870483471883828
deLQOne = 1.2336159400407760
deLQTwo = 5.9057965778648134
deQLOne = 1.0912614933398774
deQLTwo = 5.8757652452349305
prQ = 2.1089458017132792
prLQ = 2.1260437367441063
prL = 1.2487602400747309
prQL = 1.2752822672161250

Total time: 128.6450000000000100 seconds

n = 100
s = 20.0000000000000000
ccl = 1000000
a = 43.0000000000000000
b = 10.0000000000000000
aQ = 0.0004081632653061
bQ = 42.9587755102040840
cQ = 10.0408163265306100
*/



/**
Test 1:

deLOne = 10.055812
deLTwo = 5.719466
deQOne = 1.002688
deQTwo = 5.688249
deLQOne = 1.238111
deLQTwo = 5.909736
deQLOne = 1.091562
deQLTwo = 5.878797
prQ = 2.118326
prLQ = 2.140119
prL = 10.195999
prQL = 1.275438

Total time: 1.6940000000000000 seconds

n = 100
s = 20.000000
ccl = 10000
a = 40.000000
b = 50.000000
aQ = 0.000408
bQ = 39.958776
cQ = 50.040816

Test 2:

deLOne = 180.020853
deLTwo = 5.717955
deQOne = 0.997106
deQTwo = 5.686713
deLQOne = 1.233856
deLQTwo = 5.907712
deQLOne = 1.090539
deQLTwo = 5.876327
prQ = 2.109003
prLQ = 2.126906
prL = 180.047796
prQL = 1.276850

Total time: 1.6859999999999999 seconds

n = 100
s = 20.000000
ccl = 10000
a = 130.000000
b = -50.000000
aQ = 0.000408
bQ = 129.958776
cQ = -49.959184
Test 3:

deLOne = 512.978540
deLTwo = 5.716885
deQOne = 1.000505
deQTwo = 5.686033
deLQOne = 1.236860
deLQTwo = 5.906808
deQLOne = 1.089924
deQLTwo = 5.875587
prQ = 2.106516
prLQ = 2.123008
prL = 512.957254
prQL = 1.273306

Total time: 1.6990000000000001 seconds

n = 100
s = 20.000000
ccl = 10000
a = -500.000000
b = 13.000000
aQ = 0.000408
bQ = -500.041224
cQ = 13.040816

Test 4:


*/


/**
Test 1:

Enter the coefficients (a, b, c): 20 13 1
Enter the random noice scale: 20
Enter the number of cycles: 1000
Enter the number of x-coordinates: 100


deLOne = 7.103798
deLTwo = 5.716514
deQOne = 0.994164
deQTwo = 5.689432
deLQOne = 89.051088
deLQTwo = 89.235896
deQLOne = 89.024681
deQLTwo = 89.235289
prQ = 0.653185
prLQ = 10.452669
prL = 2.316948
prQL = 10.494975
Total time: 0.5190000000000000 seconds

Test 2:

Enter the coefficients (a, b, c): 20 13 1
Enter the random noice scale: 20
Enter the number of cycles: 1000
Enter the number of x-coordinates: 100

deLOne = 7.299984
deLTwo = 5.751737
deQOne = 0.962737
deQTwo = 5.749931
deLQOne = 89.078922
deLQTwo = 89.272908
deQLOne = 89.098065
deQLTwo = 89.340703
prQ = 0.605659
prLQ = 10.502555
prL = 2.437103
prQL = 10.536671
Total time: 0.0790000000000000 seconds

Test 3:

deLOne = 7.117953
deLTwo = 5.717242
deQOne = 0.992652
deQTwo = 5.687286
deLQOne = 89.026587
deLQTwo = 89.216368
deQLOne = 89.034593
deQLTwo = 89.220584
prQ = 2.103252
prLQ = 33.213854
prL = 7.356446
prQL = 33.190379
Total time: 1.7360000000000000 seconds

Enter the coefficients (a, b, c): 20 13 1
Enter the random noice scale: 20
Enter the number of cycles: 10000
Enter the number of x-coordinates: 100
*/


// getfullanswer
/**

Line Normal:

Enter the coefficients (a, b): 14 20
Enter the random noice scale: 20
Enter the number of cycles: 4
Enter the number of x-coordinates: 100

y = ax + b
Old coefficients: a = 14.000000, b = 20.000000
// Cycle #1:
New coefficients: anew = 13.9910555038, bnew = 19.8556278443
Delta = 42.1961854121
Square difference of anew and a, bnew and b: delta of a's = 0.0000800040, delta of b's = 0.0208433193
//

// Cycle #2:
New coefficients: anew = 13.9858507253, bnew = 21.0308383065
Delta = 26.6863943899
Square difference of anew and a, bnew and b: delta of a's = 0.0002002020, delta of b's = 1.0626276141
//

// Cycle #3:
New coefficients: anew = 14.0066921955, bnew = 18.6906460768
Delta = 98.0931678377
Square difference of anew and a, bnew and b: delta of a's = 0.0000447855, delta of b's = 1.7144076961
//

// Cycle #4:
New coefficients: anew = 14.0398927298, bnew = 17.5263882454
Delta = 153.6766486848
Square difference of anew and a, bnew and b: delta of a's = 0.0015914299, delta of b's = 6.1187551126
//

*/

/**
Line Centralised:

y = ax + b
Old coefficients: a = 14.0000000000, b = 20.0000000000
Choose the method:
1. Standard
2. Normalised
3. Matrix
Enter the number: 2
Do you want to see the answers? (press 0 to refuse): 1
// Cycle #1:

a = 14.036125
xNorm = 83325.000000
yNorm = 1169560.149541
New coefficients: anew = 13.9910555038, bnew = 19.8556278443
Delta = 42.1961854121
Square difference of anew and a, bnew and b: delta of a's = 0.0000800040, delta of b's = 0.0208433193
//

// Cycle #2:

a = 13.980830
xNorm = 83325.000000
yNorm = 1164952.685324
New coefficients: anew = 13.9858507253, bnew = 21.0308383065
Delta = 26.6863943899
Square difference of anew and a, bnew and b: delta of a's = 0.0002002020, delta of b's = 1.0626276141
//

// Cycle #3:

a = 14.058873
xNorm = 83325.000000
yNorm = 1171455.560167
New coefficients: anew = 14.0066921955, bnew = 18.6906460768
Delta = 98.0931678377
Square difference of anew and a, bnew and b: delta of a's = 0.0000447855, delta of b's = 1.7144076961
//

// Cycle #4:

a = 14.027820
xNorm = 83325.000000
yNorm = 1168868.095950
New coefficients: anew = 14.0398927298, bnew = 17.5263882454
Delta = 153.6766486848
Square difference of anew and a, bnew and b: delta of a's = 0.0015914299, delta of b's = 6.1187551126
//

wrvala = 0.0218884750
wrvalb = 1.4930366491
wrvaleq = 0.8953384783

//
*/

/**
Line Matrix:

y = ax + b
Old coefficients: a = 14.0000000000, b = 20.0000000000
Choose the method:
1. Standard
2. Normalised
3. Matrix
Enter the number: 3
Do you want to see the answers? (press 0 to refuse): 1
// Cycle #1:

0.000012        -0.000606
-0.000606       0.040606



4834144.550310
72640.393078



13.991056
19.855628


New coefficients: anew = 13.9910555038, bnew = 19.8556278443
Delta = 42.1961854121
Square difference of anew and a, bnew and b: delta of a's = 0.0000800040, delta of b's = 0.0208433193
//

// Cycle #2:

0.000012        -0.000606
-0.000606       0.040606



4838318.326365
72731.629994



13.985851
21.030838


New coefficients: anew = 13.9858507253, bnew = 21.0308383065
Delta = 26.6863943899
Square difference of anew and a, bnew and b: delta of a's = 0.0002002020, delta of b's = 1.0626276141
//

// Cycle #3:

0.000012        -0.000606
-0.000606       0.040606



4833552.067019
72602.860195



14.006692
18.690646


New coefficients: anew = 14.0066921955, bnew = 18.6906460768
Delta = 98.0931678377
Square difference of anew and a, bnew and b: delta of a's = 0.0000447855, delta of b's = 1.7144076961
//

// Cycle #4:

0.000012        -0.000606
-0.000606       0.040606



4838905.965758
72654.097110



14.039893
17.526388


New coefficients: anew = 14.0398927298, bnew = 17.5263882454
Delta = 153.6766486848
Square difference of anew and a, bnew and b: delta of a's = 0.0015914299, delta of b's = 6.1187551126
//

wrvala = 0.0218884750
wrvalb = 1.4930366491
wrvaleq = 0.8953384783

*/

/**
Enter the coefficients (a, b, c): 14 20 5
Enter the random noice scale: 20
Enter the number of cycles: 4
Enter the number of x-coordinates: 100

Old coefficients: a = 14.0000000000, b = 20.0000000000
Choose the method:
1. Line Normal
2. Line Centralised
3. Line Matrix
4. Square Centralised Matrix
Enter the number: 4
Do you want to see the answers? (press 0 to refuse): 1
// Cycle #1:

0.000000        -0.000002
-0.000002       0.000196


12845500504.359869
119487304.699850

a = 13.998088
b = 20.184206
c = 4.403931
New coefficients: anew = 13.9980876180, bnew = 20.1842060822, cnew = 4.4039307840
Delta = 709.6200799552
Square difference of anew and a, bnew and b, cnew and c: delta a's = 0.0000036572, delta of b's = 0.0339318807, delta of c's = 0.3552985102
//

// Cycle #2:

0.000000        -0.000002
-0.000002       0.000196


12845618832.908108
119486871.011689

a = 14.001007
b = 19.884100
c = 5.316300
New coefficients: anew = 14.0010074368, bnew = 19.8840996111, cnew = 5.3162999359
Delta = 525.8801147188
Square difference of anew and a, bnew and b, cnew and c: delta a's = 0.0000010149, delta of b's = 0.0134329001, delta of c's = 0.1000456495
//

// Cycle #3:

0.000000        -0.000002
-0.000002       0.000196


12845781255.273289
119488607.627186

a = 14.000774
b = 19.928543
c = 4.028602
New coefficients: anew = 14.0007737555, bnew = 19.9285428857, cnew = 4.0286019471
Delta = 421.9128289444
Square difference of anew and a, bnew and b, cnew and c: delta a's = 0.0000005987, delta of b's = 0.0051061192, delta of c's = 0.9436141772
//

// Cycle #4:

0.000000        -0.000002
-0.000002       0.000196


12846019386.914278
119491374.061708

a = 14.000030
b = 20.036825
c = 4.540971
New coefficients: anew = 14.0000303755, bnew = 20.0368248086, cnew = 4.5409710990
Delta = 358.6780722597
Square difference of anew and a, bnew and b, cnew and c: delta a's = 0.0000000009, delta of b's = 0.0013560665, delta of c's = 0.2107075320
//

wrvala = 0.0011480150
wrvalb = 0.1160031967
wrvalc = 0.6343630406
wrvaleq = 2.2450451532
*/

/**
Результаты ручного тестирования 1:
Ввод:
20 1
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21

Вывод:
y = 1.000000x(1) + 1.000000
xy = 3080.000000
xx = 2870.000000
xi = 210.000000
yi = 230.000000
*/


/**
Результаты ручного тестирования 2:
Ввод:
20 2
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21

Вывод:
y = 0.044929x(2) + 5.052632
xy = 46970.000000
xx = 722666.000000
xi = 2870.000000
yi = 230.000000
*/


/**
Результаты ручного тестирования 3:
Ввод:
20 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21

Вывод:
y = 0.002178x(3) + 6.698156
xy = 766766.000000
xx = 216455810.000000
xi = 44100.000000
yi = 230.000000
*/

/**
Root mean square for a = 9.6054831421
Root mean square for b = 59.7621499417
Root mean square for equations = 38.9187393880
The time required for computations is 2.7040000000
*/
