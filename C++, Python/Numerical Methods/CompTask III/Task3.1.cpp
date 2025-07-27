#include"Task3.1.h"

//////////////////////////////////


void LagrangeInterpolation(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double))
{
    wcout << endl << L"Интерполяция Лагранжа:" << endl;
    double denominator;
    double numerator;
    double total = 0;
    double *ptr = arg;
    for(;ptr < (arg + deg); ptr++)
    {
        denominator = fnc(arg, deg, *ptr, *ptr);
        numerator = fnc(arg, deg, x, *ptr);
        double temp = *(ptr+size)/denominator;
        // cout << "denominator: " << denominator << endl;
        total += numerator*temp;
        // cout << "total: " << total << endl;
        cout << temp;
        for(double *ptrj = arg; ptrj < (arg + deg); ptrj++)
        {
            if(ptrj!=ptr) cout << "(x - " << *ptrj << ")";
        }
        cout << '+';
    }

    /*
    for(size_t i = 0; i < deg; i++)
    {
        double a = 0;
        for(double *ptrj = arg; ptrj <= (arg + i) ; ptrj++)
        {
            denominator = fnc(arg, i, *ptrj, *ptrj);
            a += *(ptrj + size)/denominator;
        }
        cout << a;
        for(size_t j = 0; j < i; j++) cout << "(x - " << arg[j] << ")";
        cout << '+';
    }
    */

    wcout << L"\nЗначение в точке интерполяции f(x) = " << x << ": " << total << endl;
    wcout << L"Абсолютная погрешность: " << fabs(total - f(x)) << endl << endl;
}

double LagrangeInterpolationVar(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double))
{
    double denominator;
    double numerator;
    double total = 0;
    double *ptr = arg;
    for(;ptr < (arg + deg); ptr++)
    {
        denominator = fnc(arg, deg, *ptr, *ptr);
        numerator = fnc(arg, deg, x, *ptr);
        double temp = *(ptr+size)/denominator;
        total += numerator*temp;
    }
    return total;

}

void NewtonInterpolation(double *arg, size_t size, size_t deg, double x, double (*fnc)(double*, size_t, double, double), double (*f)(double))
{
    setlocale(LC_ALL, "russian");
    wcout << L"Интерполяция Ньютона:" << endl;
    size_t degp = deg + 1;
    double space[degp][deg], total = 0, product = 1;
    for(size_t i = 0; i < deg; i++)
    {
        space[0][i] = arg[i];
        space[1][i] = arg[size+i];
    }
    for(size_t i = 2; i < degp; i++)
    {
        for(size_t j = 0; j < degp - i; j++)
        {
            space[i][j] = (space[i-1][j+1]-space[i-1][j])/(space[0][j+i-1]-space[0][j]);
        }
    }

    /*
    for(size_t i = 0; i < 2; i++)
    {
        cout << "f" << i << ": ";
        for(size_t j = 0; j < degp; j++)
            cout << space[i][j] << ' ';
        cout << endl;
    }

    for(size_t i = 2; i < degp; i++)
    {
        cout << "f" << i << ": ";
        for(size_t j = 0; j < degp - i; j++)
        cout << space[i][j] << ' ';
        cout << endl;
    }
    */

    for(size_t i = 1; i < degp; i++)
    {
        cout << space[i][0];
        for(int j = i-2; j>=0; j--) cout << "(x - " << space[0][j] << ")";
        cout << '+';
    }
    for(size_t i = 1; i < degp; i++)
    {
        total += space[i][0]*product;
        product *= (x - arg[i-1]);
    }

    wcout << L"\nЗначение в точке интерполяции f(х) = " << x << ": " << total << endl;
    wcout << L"Абсолютная погрешность: " << fabs(total - f(x)) << endl << endl;
}


/////////////////////////////

double f(double x)
{
    return exp(-x) - x*x/2;
};

double df(double x)
{
    return -exp(-x) - x;
}

double fi(double x, double node, double* arg, size_t N)
{
    return x - fMod(x, node, arg, N)/df(x);
}

double secf(double x, double y, double node, double* arg, size_t N)
{
    return x - fMod(x, node, arg, N)/(f(x) - f(y))*(x - y);
}

void BiSect(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t))
{
    size_t counter = 0;
    double x = beg, xNext = beg + h;
    while(x < end)
    {
        double a = x, b = xNext;
        double c, delta, fappr=(a+b)/2;
        size_t m = 0;
        if(f(a, node, arg, N)*f(b, node, arg, N)<=0)
        {
            counter++;
            while(b - a >= 2*eps){
                m++;
                c = (a+b)/2;
                if(f(b, node, arg, N)*f(c, node, arg, N)<=0)
                {
                    a = c;
                } else b = c;
            }
            delta = (b-a)/2;

            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c, node, arg, N)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}

void NewtonApprox(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t), double (*fi)(double, double)){
    size_t counter = 0;
    double x = beg, xNext = beg + h;
    while(x < end)
    {
        double a = x, b = xNext;
        double c = (a+b)/2, delta, fappr=(a+b)/2;
        size_t m = 0;
        if(f(a, node, arg, N)*f(b, node, arg, N) <= 0){
            counter++;
            while(fabs(c - a) >= eps){
                m++;
                a = c;
                c = fi(c, node);
                if(c > xNext || c < x){
                    wcout << L"Между "<< x << L" и " << xNext << L": Ошибка: корень не может быть вычислен (попробуйте взять N побольше)" << endl;
                    m = 0;
                    break;
                }
            }
        }
        if(m){
            delta = fabs(c-a);

            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c, node, arg, N)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}

void ModNewtonApprox(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t), double (*df)(double)){
    size_t counter = 0;
    double x = beg, xNext = beg + h;
    while(x < end)
    {
        double a = x, b = xNext;
        double c = (a+b)/2, delta, fappr=(a+b)/2;
        double cf = df(c);
        size_t m = 0;
        if(f(a, node, arg, N)*f(b, node, arg, N) <= 0){
            counter++;
            while(fabs(c - a) >= eps){
                m++;
                a = c;
                c = c - f(c, node, arg, N)/cf;
                if(c > xNext || c < x){
                    wcout << L"Между "<< x << L" и " << xNext << L": Ошибка: корень не может быть вычислен (попробуйте взять N побольше)" << endl;
                    m = 0;
                    break;
                }
            }
        }
        if(m){
            delta = fabs(c-a);

            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c, node, arg, N)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}

void SecantApprox(double beg, double end, double h, double eps, double node, double* arg, size_t N, double (*f)(double, double, double*, size_t), double (*secf)(double, double, double, double*, size_t)){
     size_t counter = 0;
     double x = beg, xNext = beg + h;
     while(x < end){
        double a = x, b = xNext;
        double c = secf(b, a, node, arg, N), delta, fappr=secf(b, a, node, arg, N);
        size_t m = 0;
        if(f(a, node, arg, N)*f(b, node, arg, N)<=0){
            counter++;
            while(fabs(c - b) >= eps){
                m++;
                a = b;
                b = c;
                c = secf(c, a, node, arg, N);
                if(c < x || c > xNext){
                    wcout << L"Между "<< x << L" и " << xNext << L": Ошибка: корень не может быть вычислен (попробуйте взять N побольше)" << endl;
                    m = 0;
                    break;
                }
            }
        }
        if(m){
            delta = fabs(c - b);
            wcout << '\n' << L"Между " << x << L" и " << xNext << ":\n"<< L"Начальное приближение: " << fappr << endl;
            wcout << L"Число итераций: " << m << L"\nПриближённое решение: " << c << L"\nДлина последнего отрезка: " << delta;
            wcout << L"\nНевязка |f(X)-0|: " << fabs(f(c, node, arg, N)) << endl;

        }

        x = xNext;
        xNext += h;
    }
    wcout << '\n' << L"Число корней: " << counter << endl;
}


///////////////////////////////////

double productValue(double *arg, size_t size, double x, double c)
{
    double value = 1; double* ptr = arg;
    for(;ptr < (arg + size); ptr++) {if(c!=*ptr) value *= (x-*ptr);}
    // cout << "value: " <<  value << endl;
    return value;
}

double* buildup(double(*f)(double), size_t size, double a, double b)
{
    double *temp = new double[2*size];
    double *ptr = temp;
    double h;
    if(size==1) h = (a+b)/2;
    else h = (b-a)/(size-1);
    double x = a;
    wcout << "x" << setw(27) << "f(x)" << endl;
    for(;ptr < (temp + size); ptr++, x+=h)
    {
        *ptr = x;
        *(ptr + size) = f(x);
        wcout << *ptr << setw(24) << *(ptr+size) << endl;
    }
    return temp;
};

void sortTable(double *arg, size_t size, size_t deg, double x, void (*fnc1)(double*, double*, size_t, size_t), void (*fnc2)(double*, double*, size_t))
{

    double temp[size];
    for(size_t i = 0; i < size; i++) temp[i]=fabs(x-arg[i]);
    fnc1(temp, arg, size, deg);
    fnc2(temp, arg, size);
};

void sortArray(double *temp, double *arg, size_t size, size_t deg)
{
    for(size_t i = 0; i < deg; i++)
    {
        size_t min = i;
        for(size_t j = i + 1; j < size; j++)
        {
            if(temp[j] < temp[min]) min = j;
        }
        if(min!=i)
        {
            double temp1 = temp[min], temp2 = arg[min], temp3 = arg[min+size];
            temp[min] = temp[i];
            temp[i] = temp1;
            arg[min] = arg[i];
            arg[i] = temp2;
            arg[min+size] = arg[i+size];
            arg[i+size] = temp3;
        }
    }
};

void printArray(double *tmp, double *temp, size_t size)
{
    double *ptr = temp;
    double *val = tmp;
    wcout << "#" << setw(27) << "f(x)" << setw(27) << "x" << endl;
    for(;ptr < (temp + size); ptr++, val++)
    {
        wcout << *val << setw(24) << *ptr << setw(24) << *(ptr + size) << endl;

    }
}

///////////////////////////////////
// Первый способ решения

void swapColumns(double *arg, size_t size, double x)
{
    wcout << "f(x)" << setw(27) << "x" << endl;
    double *threshold = arg + size;
    for(double *ptrfx = arg; ptrfx < threshold; ptrfx++){
        double x = *(ptrfx + size);
        *(ptrfx + size) = *ptrfx;
        *ptrfx = x;
        wcout << *ptrfx << setw(24) << *(ptrfx + size) << endl;
    }

}

void procedureOne(){
    wcout << L"Первый способ решения:" << endl;
    double a, b;
    size_t m, n;
    double x;
    wcout << L"Начало отрезка: ";   cin >> a;
    wcout << L"Конец отрезка: "; cin >> b;
    while(b<=a)
    {
        wcout << endl << L"Ошибка: конец отрезка меньше-равен начала. Пожалуйста, введите сначала начало отрезка, затем конец." << endl;
        wcout << endl << L"Начало отрезка: "; cin >> a;
        wcout << endl << L"Конец отрезка: "; cin >> b;
    }

    wcout << L"Число аргументов: "; cin >> m;

    // Этап 0.5. Таблица значений
    // Замечание: так как m не изменяется, можно использовать статический массив.
    double* arg = buildup(&f, m, a, b);

    wcout << endl << L"Введите точку интерполяции f(х): "; cin >> x; wcout << endl;

    swapColumns(arg, m, x);

    wcout << L"Степень интерполяционного многочлена (меньше числа аргументов): "; cin >> n; wcout << endl;
    while(n>=m)
    {
        wcout << endl << L"Ошибка: такого многочлена не существует. Пожалуйста, введите степень меньше числа аргументов: ";
        wcout << endl; cin >> n; wcout << endl;
    }

    sortTable(arg, m, n+1, x, &sortArray, &printArray);

    int p;
    size_t cmp = n + 1, cmpx = x+1;
    wcout << L"Нажмите 1, чтобы начать процесс интерполяции" << endl << L"Нажмите 0, чтобы выйти" << endl;
    wcout << endl; cin >> p;
    while(p!=0 && p!=1)
    {
            wcout << endl << L"Ошибка: неправильные значения. Пожалуйста, введите 0 или 1." << endl << endl;
            cin >> p;
    }

    while(p)
    {
        if(cmp!=n || cmpx!=x)
        {
            cmp = n;
            cmpx = x;
            LagrangeInterpolation(arg, m, n+1, x, &productValue, &f);
            NewtonInterpolation(arg, m, n+1, x, &productValue, &f);
        }
        else wcout << endl << L"Введена та же степень и точка интерполяционного многочлена. Пожалуйста, введите другие значения." << endl;

        wcout << endl << L"Нажмите 1, чтобы начать процесс интерполяции" << endl << L"Нажмите 0, чтобы выйти" << endl;
        wcout << endl; cin >> p;
        while(p!=0 && p!=1)
        {
            wcout << endl << L"Ошибка: неправильные значения. Пожалуйста, введите 0 или 1." << endl << endl;
            cin >> p;
        }
        if(p)
        {
            wcout << L"Введите точку интерполяции f(х): "; cin >> x; wcout << endl;
            wcout << L"Степень интерполяционного многочлена (меньше числа аргументов): "; cin >> n; wcout << endl;
            while(n>=m)
            {
                wcout << endl << L"Ошибка: такого многочлена не существует. Пожалуйста, введите степень меньше числа аргументов: ";
                wcout << endl; cin >> n; wcout << endl;
            }
            sortTable(arg, m, n+1, x, &sortArray, &printArray);
        }
    }
}

double fMod(double x,double node, double* arg, size_t N)
{
    double fx = LagrangeInterpolationVar(arg, N, N, x, &productValue, &f);
    return fx - node;
}

void procedureTwo(){
    wcout << L"Второй способ решения" << endl;
    double a, b;
    double eps;
    size_t N;
    double x;
    int flag = 1;
    while(!(flag-1))
    {

        /* 0. Entering data and checking-in */
        wcout << L"Начало отрезка: ";   cin >> a;
        wcout << L"Конец отрезка: "; cin >> b;
        while(b<=a)
        {
            wcout << endl << L"Ошибка: конец отрезка меньше-равен начала. Пожалуйста, введите сначала начало отрезка, затем конец." << endl;
            wcout << endl << L"Начало отрезка: "; cin >> a;
            wcout << endl << L"Конец отрезка: "; cin >> b;
        }
        wcout << L"(Погрешность) eps = ";cin >> eps;
        while(eps <= 0)
        {
            wcout << endl << L"Ошибка: отрицательное значение погрешности" << endl;
        }
        wcout << L"(Число разбиений) N = "; cin >> N; wcout << endl;
        while(N == 0)
        {
            wcout << endl << L"Ошибка: неположительное число узлов интерполирования. Пожалуйста, введите N не менее 1." << endl;
            cin >> N;
        }

        double* arg = buildup(&f, N, a, b);

        /* 1. Decoupling roots on [A, B] */

        double h = (b-a)/N;
        wcout << endl << L"Введите точку интерполяции f(х): "; cin >> x; wcout << endl;
        // 1.1 Bisection Method
        /**
        wcout << '\n' << '\n' << L"Метод бисекции: " << endl;
        BiSect(a, b, h, eps, x, fMod);
        */

        /**
        // 1.2 Tangent Method
        wcout << '\n' << '\n' << L"Метод Ньютона: " << endl;
        NewtonApprox(a, b, h, eps, x, fMod, fi);
        */

        /**
        // 1.3 Modified Tangent Method (MoTangeM)
        wcout << '\n' << '\n' << L"Модифицированный метод Ньютона: " << endl;
        ModNewtonApprox(a, b, h, eps, x, fMod, df);
        */
        double A = x*x <= 2? -1: -x*x/2, B = x*x <= 1 ? 1 : x*x;
        // 1.4 Secant Method
        wcout << '\n' << '\n' << L"Метод секущих: " << endl;
        SecantApprox(A, B, h, eps, x, arg, N, fMod, secf);

        wcout << endl << endl << L"Желаете повторить?\nВведите цифру 1, чтобы продолжить. Чтобы закончить, введите любое другое число" << endl;
        cin >> flag;
    }
}

void introOne(){
    wcout << L"Задача обратного интерполирования:" << endl;
    wcout << L"Интерполяционный многочлен в форме Ньютона и в форме Лагранжа." << endl << endl;
    wcout << L"Вариант 7. Функция f(x) = eps(-x) - x^2/2" << endl << endl;
}
// Второй способ решения

