int main()
{
    //
    double a, b;
    printf("Enter the coefficients (a, b): ");
    scanf("%lf%lf", &a, &b);
    //
    double s;
    printf("Enter the random noice scale: ");
    scanf("%lf", &s);
    //
    unsigned int ccl;
    printf("Enter the number of cycles: ");
    scanf("%ud", &ccl);
    //
    unsigned int n;
    printf("Enter the number of x-coordinates: ");
    scanf("%ud", &n);
    printf("\n");
    //
    printf("y = ax + b\n");
    printf("Old coefficients: a = %lf, b = %lf\n", a, b); // Вывод старых коэффициентов
    for(size_t i = 1; i <= ccl; ++i){
        printf("// Cycle #%lu:\n", i);
        srand((i*(int)a + (int)b)%RAND_MAX);
        //
        struct data src;
        src.sums.xj = 0;
        src.sums.xx = 0;
        src.sums.xy = 0;
        src.sums.yj = 0;
        src.delta = 0;
        //
        for(size_t j = 1; j <= n; ++j){
            double ej = (double) rand()/RAND_MAX*s - (double) s/2; // Генератор случайных шумов
            double yt = a*j + b + ej;                              // Линейное уравнение со случайным шумом
            src.sums.xj += j;
            src.sums.yj += yt;
            src.sums.xx += j*j;
            src.sums.xy += j*yt;
        }
        findab(src, n);
        //
        // getfullanswer(delta, anew, bnew, a, b, n, xj, yj, xx, xy);
        // getshortanswer(delta, anew, bnew, a, b, n);
    }
}



struct data
{
    struct {
        double xx, xy, xj, yj;
    } sums;
    double delta;
    struct{
        double anew, bnew;
    } param;
};



void findab(struct data *src ,size_t n){
    if(src.sums.xx*n - src.sums.xj*src.sums.xj != 0){
        src.param.bnew = (src.sums.xx*src.sums.yj - src.sums.xy*src.sums.xj)/(src.sums.xx*n - src.sums.xj*src.sums.xj);
        src.param.anew = (src.sums.xy*n - src.sums.xj*src.sums.yj)/(src.sums.xx*n - src.sums.xj*src.sums.xj);
    }
    else{
        src.param.bnew = 0;
        src.param.anew = 0;
    }
}
