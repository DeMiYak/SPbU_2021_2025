#include"Distribution.h"

/// 
/// 1. Гипергеометрическое распределение 
/// 
/// 2. Построение графика зависимости мощности критерия от объёма
/// выборки при заданном уровне значимости и заданной альтернативе

/// <summary>
/// 1. Задавать параметры распределения, метод моделирования, объем выборки.
/// 2. Моделировать выборку(два метода).
/// 3. Изображать гистограмму на фоне теоретического распределения.Выдавать значение chi - square, число
/// степеней свободы(d.f. - degree of freedom) и пороговый уровень значимости(p - level).
/// 4. Получать выборку p-levels. Для этого задавать параметры распределения, которое моделируется,
/// параметры распределения, на согласие с которым проверяется гипотеза, и число повторов.Если это
/// одни и те же параметры распределения, то выдавать, какой истинный уровень значимости
/// соответствует заданному уровню значимости.Если это разные распределения, то выдавать, какая
/// мощность у критерия с заданным уровнем значимости против данной альтернативы.
/// 5. Изображать эмпирическую функцию распределения выборки p - levels на фоне теоретической ф.р. (т.е.,
/// функции распределения равномерного на[0, 1] распределения).
/// </summary>
/// <returns></returns>
int main()
{
    cout << "Inverse Transform Method: " << endl;
    Test(IT);
    cout << endl << "Bernoulli Distribution Method: " << endl;
    Test(BD);
    
    /*
    Построение графика зависимости мощности критерия от объёма выборки при
    заданном уровне значимости и заданной альтернативе
    */

    //random_device rdAlter, rdOrig;
    //int oa = 25, ob = 50, ok = 20;
    //int aa = oa-1, ab = ob+1, ak = ok;
    //HGDistribution HGOrig(oa, ob, ok, rdOrig);

    //// Уровень значимости
    //double alpha = 0.13;
    //// Число повторов
    //int lim = 3000;
    //// Альтернатива
    //HGDistribution HGAlter(aa, ab, ak, rdAlter);
    //printf("\n\n%-s%lf\n", "Alpha: ", alpha);
    //printf("%-s%c%d%c%d%c%d%c\n", "Original: ", '(',oa, ',',ob, ',',ok, ')');
    //printf("%-s%c%d%c%d%c%d%c\n", "Alternative: ", '(', aa, ',', ab, ',', ak, ')');
    //printf("%-15s|%s\n", "Sample Volume", "Criterion Power");
    //for (int i = 0; i <= 10; i++) {
    //    int n = 100 + 50 * i;
    //    double criteria_power = 0;
    //    for (int j = 0; j < lim; j++) {
    //        vector<int> sample = Generate_Sample(BD, n, HGAlter);
    //        vector<int> freq = Count_Frequency(sample, HGAlter.Get_K());
    //        // Так как верна альтернативная гипотеза,
    //        // то по ней выстраиваем теоретическое распределение
    //        // а затем проверяем, является ли верной гипотеза
    //        const vector<double> tp = Theory_Prob(HGOrig);
    //        vector<double> tf = Theory_Frequency(tp, n);
    //        vector<pair<double, int>> m_f = Chi_Square_Merge(tf, freq);
    //        double chi = Chi_Square(m_f);
    //        int dof = DOF(m_f);
    //        double p_level = pChi(chi, dof);
    //        if (alpha <= p_level) criteria_power++;
    //    }
    //    criteria_power /= lim;
    //    criteria_power = 1 - criteria_power;
    //    printf("%-15d|%.6lf\n", n, criteria_power);
    //}

    
    // Ошибка второго рода: P_H1(H0 неверно принята);
    // Мощность критерия: P_H1(H0 верно отвергнута);

    // For inverse_transform
    return 0;
    
}