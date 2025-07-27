#include"Distribution.h"

int HGDistribution::Inverse_Transform()
{
    // Шаг 1. Вычисление p0
	int i = 0;
	int n = a + b;
	double p = 1;
    for (int j = 0; j < k; j++) {
        p *= (b - j);
        p /= (n - j);
    }
	double l = p;

    // Шаг 2. Моделирование альфа
	mt19937 gen(rd());
	uniform_real_distribution<> distr(0, 1);
	double alpha = distr(gen);
	
    // Шаг 3. Метод обратных функций (складывание вероятностей)
    //  while (i <= k) {
    //  cout << p << endl;
	//	p = p * (double(a - i) * (k - i)) / ((i + 1) * (n - a - k + i + 1));
	//	// l += p;
	//	i++;
	//}

    while (alpha >= l) {
        double w = (double(a - i) * (k - i)) / ((i + 1) * (n - a - k + i + 1));
        // cout << p << ' ' << w << ' ' << l << endl;
        p *= w;
        l += p;
        i++;
    }
	return i;
}

int HGDistribution::Bernoulli_Distribution()
{
	int i = 0, j = 0;
	int n = a + b;
	mt19937 gen(rd());
	uniform_real_distribution<> distr(0, 1);
	double alpha = distr(gen);
	do {
		if (alpha < double(a - j)/(n - i)) j++;
		i++;
		alpha = distr(gen);
	} while (i < k);
	return j;
}

vector<int> Generate_Sample(MODELLING_METHOD mm, int sample_volume, HGDistribution& HG)
{
	vector<int> sample_vector;
	int (HGDistribution::*fptr)();
	if (mm == IT) fptr = &HGDistribution::Inverse_Transform;
	else fptr = &HGDistribution::Bernoulli_Distribution;
	for (int i = 0; i < sample_volume; i++)
		sample_vector.push_back((HG.*fptr)());
	return sample_vector;
}

const vector<double> Theory_Prob(const HGDistribution& HG)
{
	int a = HG.Get_A();
	int b = HG.Get_B();
	int k = HG.Get_K();
	int n = HG.Get_N();
	vector<double> tp;
	double prob = 1;
	for (int j = 0; j < k; j++) prob *= double(b - j) / (n - j);
	for (int j = 0; j <= k; j++) {
		tp.push_back(prob);
		prob = prob * (a - j)*(k - j) / ((j + 1)*(n - a - k + j + 1));
	}
	return tp;
}

vector<int> Count_Frequency(const vector<int>& sample, const int k)
{
	int n = sample.size();
	vector<int> frequency(k+1);
	for (int i = 0; i < n; i++) 
        frequency[sample[i]]++;
	return frequency;
}

vector<double> Theory_Frequency(const vector<double>& tp, int sample_volume)
{
	int n = tp.size();
	vector<double> tf(n);
	for (int i = 0; i < n; i++) 
        tf[i] = sample_volume * tp[i];
	return tf;
}

vector<pair<double, int>> Chi_Square_Merge(const vector<double>& tf, const vector<int>& freq)
{
	int n = tf.size();
	double sum_tf = 0;
	int sum_freq = 0;
	vector<pair<double, int>> merge_vector;
	// Хотим сделать так, чтобы условия применимости выполнялись:
	// 1. n >= 50(70) - можно прописать в main.
	// 2. n*p_i >= 5 (значения вектора).
	// Если значения < 5, то суммируем (объединяем) их, пока
	// не получится значение >= 5. Если в конце сумма окажется < 5,
	// то присваиваем этот остаток последнему элементу.
	// Условиями задачи гарантируется, что как минимум будет две степени свободы.
	for (int i = 0; i < n; i++) {
		sum_tf += tf[i];
		sum_freq += freq[i];
		if (sum_tf >= 5) {
			merge_vector.push_back(pair<double,int>(sum_tf, sum_freq));
			sum_tf = 0;
			sum_freq = 0;
		}
	}
	if (sum_tf) {
		merge_vector.back().first += sum_tf;
		merge_vector.back().second += sum_freq;
	};
	return merge_vector;
}

double Chi_Square(const vector<pair<double, int>>& merge_freq)
{
	int n = merge_freq.size();
	double chi = 0;
	for (int i = 0; i < n; i++)
		chi += pow((merge_freq[i].first - merge_freq[i].second),2) / merge_freq[i].first;
	return chi;
}

int DOF(const vector<pair<double, int>>& merge_freq)
{
	return merge_freq.size()-1;
}

double P_Value(MODELLING_METHOD mm, int sample_volume, HGDistribution& HGOrig, HGDistribution& HGAlter) {
	vector<int> sample = Generate_Sample(mm, sample_volume, HGAlter);
	vector<int> freq = Count_Frequency(sample, HGAlter.Get_K());
	const vector<double> tp = Theory_Prob(HGOrig);
	vector<double> tf = Theory_Frequency(tp, sample_volume);
	vector<pair<double, int>> m_f = Chi_Square_Merge(tf, freq);
	double chi = Chi_Square(m_f);
	int dof = DOF(m_f);
	return 1 - pChi(chi, dof);
}

void P_Distribution(vector<double>& p_distr) {
	double sample_volume = 0;
	for (int i = 0; i < p_distr.size(); i++)
		sample_volume += p_distr[i];

	for (int i = 1; i < p_distr.size(); i++) {
		p_distr[i] += p_distr[i - 1];
        // Сколько выходит за alpha
		p_distr[i - 1] /= sample_volume;
	}
	p_distr[p_distr.size() - 1] /= sample_volume;
}

void Test(MODELLING_METHOD mm)
{
    // a = 25, b = 30, k = 20
    random_device rd, rdAlt;
    int a, b, k;
    int n = 100, len = 10000;
    cin >> a >> b >> k;
    /*vector<double> sample = Hypergeometric_distribution(a, b, k);
    cout << endl << endl;
    for (int i = 0; i <= k; i++) {
        cout << "p" << i << ":\t" << sample[i] << '\n';
    }*/


    //cout << endl << inverse_transform(a, b, k, rd) << endl;
    //cout << endl << bernoulli_distribution(a, b, k, rd) << endl;

    // test_modelling
    HGDistribution HG(a, b, k, rd);
    /*
    -Тестировать функции моделирования можно, например, так: вывести несколько первых реализаций
        датчика случайных чисел и несколько первых реализаций для моделируемого распределения.Затем, следуя
        алгоритму(а не тексту функции), сосчитать, какой должна быть реализация.
        */
    printf("%-10s|%s\n", "Inverse", "Bernoulli");
    for (int i = 0; i < 100; i++) {
        printf("%-10d|%d\n", HG.Inverse_Transform(), HG.Bernoulli_Distribution());
    }

    // For Bernoulli

    /*- Для тестирования правильности применения хи - квадрата, имеет смысл вывести теоретические и
        эмпирические частоты до объединения интервалов, затем после объединения интервалов, а также число
        степеней свободы, статистику критерия и p - level.Сумма теоретических и эмпирических частот всегда
        должна быть равна объему выборки.*/

    vector<int> sample = Generate_Sample(mm, n, HG);
    vector<int> freq = Count_Frequency(sample, HG.Get_K());
    const vector<double> tp = Theory_Prob(HG);
    vector<double> tf = Theory_Frequency(tp, n);
    vector<pair<double, int>> m_f = Chi_Square_Merge(tf, freq);
    double chi = Chi_Square(m_f);
    int dof = DOF(m_f);
    double p_level = pChi(chi, dof);

    int f_s = 0;
    double tf_s = 0;
    printf("%-s\n%-10s|%s\n", "Frequency", "Empiric", "Theoretical");
    for (int i = 0; i <= k; ++i) {
        printf("%-10d|%.5lf\n", freq[i], tf[i]);
        f_s += freq[i];
        tf_s += tf[i];
    }
    printf("\n%-30s%d\n%-30s%.6lf\n", "Sample Volume: ", n, "Chi-Square: ", chi);
    printf("%-30s%d\n%-30s%.6lf\n", "Degree of Freedom: ", dof, "P-level: ", p_level);
    printf("%-30s%d\n%-30s%.6lf\n", "Empiric Frequency: ", f_s, "Theoretical Frequency: ", tf_s);

    printf("\n%-s\n%-10s|%s\n", "Aggregated frequencies", "Empiric", "Theoretical");
    for (int i = 0; i < m_f.size(); ++i) {
        printf("%-10d|%lf\n", m_f[i].second, m_f[i].first);
    }
    //-Дальнейшей проверкой правильности будет близость гистограмм моделируемого распределения и
    //    выборки, а также не очень большие и не очень маленькие значения критерия хи - квадрат(если вы уже
    //        будете уверены, что в моделировании у вас ошибок нет, то эти же самые характеристики будут служить
    //        тестом для правильности построения гистограммы и вычисления критерия). Математическое ожидание для
    //    случайной величины с распределением хи - квадрат равно числу степеней свободы, т.е.реализации должны
    //    колебаться вокруг числа степеней свободы.Естественно, самой сильной проверкой будет равномерное
    //    распределение p - levels.

    printf("\n%-s\n", "Distribution when H1 = H0");

    vector<double> p_distr(20);
    for (int i = 0; i < len; i++) {
        double p_level = P_Value(mm, n, HG, HG);
        // Это распределение должно получиться равномерным, если проверяем нулевую гипотезу
        p_level = floor(p_level / 0.05);
        if (p_level == 20) p_level--;
        p_distr[p_level]++;
    }

    // Комментарий: выводить частоты m_f
    /*printf("%-s\n%-10s|%s\n", "Frequency", "Empiric", "Theoretical");
    for(int i = 0; i < m_f.size(); i++) {
        printf("%-10d|%.6lf\n", m_f[i].second, m_f[i].first);
    }*/

    P_Distribution(p_distr);

    printf("\n%-s\n%-10s|%s\n", "Type I Error", "alpha", "#(p-value)");
    for (int i = 0; i < 20; i++) {
        printf("%-10.2lf|%.3lf\n", 0.05 * (i + 1), p_distr[i]);
    }


    //- Проверку гипотез удобно реализовать так : у вас в программе существует понятие основной(нулевой) и
    //    альтернативных гипотез(в данном случае нулевая и альтернативная гипотезы отличаются разными
    //        значениями параметров заданного распределения).Можно всегда моделировать распределение согласно
    //    альтернативной гипотезе и проверять на соответствие нулевой гипотезе(т.е.теоретические частоты всегда
    //        вычисляются на основе параметров из нулевой гипотезы).Если вы формально делаете альтернативную
    //    гипотезу равной нулевой, то распределение p - levels должно быть равномерным и на его основе можно
    //    смотреть, насколько истинная вероятность ошибки I рода отличается от заданного уровня значимости.Если
    //    альтернативная гипотеза отличается от нулевой, то распределение P - levels показывает, чему равна
    //    мощность критерия против заданной альтернативы при заданных уровнях значимости.

    HGDistribution HGAlt(a + 1, b - 2, k, rdAlt);
    vector<double> p_distrAlt(20);

    printf("\n%-s\n%-s\n%-s", "Distribution for", "H0: a = a0, b = b0;", "H1: a = a0 + 1, b = b0 - 2");
    for (int i = 0; i < len; i++) {
        double p_level = P_Value(mm, n, HG, HGAlt);
        p_level = floor(p_level / 0.05);
        if (p_level == 20) p_level--;
        // Это распределение должно получиться равномерным, если проверяем нулевую гипотезу
        p_distrAlt[p_level]++;
    }

    P_Distribution(p_distrAlt);
    // Отсюда получаем мощность критерия для H1
    printf("\n%-s\n%-10s|%s\n", "Criterion Power", "alpha", "#(p-value)");
    for (int i = 0; i < 20; i++) {
        printf("%-10.2lf|%.3lf\n", 0.05 * (i + 1), p_distrAlt[i]);
    }

    printf("\n%-s", "Second H1 distribution");

    random_device rdAlt2;
    HGDistribution HGAlt2(a - 5, b + 15, k, rdAlt2);
    for (int i = 0; i < 20; i++)
        p_distrAlt[i] = 0;

    for (int i = 0; i < len; i++) {
        double p_level = P_Value(mm, n, HG, HGAlt2);
        p_level = floor(p_level / 0.05);
        if (p_level == 20) p_level--;
        // Это распределение должно получиться равномерным, если проверяем нулевую гипотезу
        p_distrAlt[p_level]++;
    }

    P_Distribution(p_distrAlt);
    // Отсюда получаем мощность критерия для H1
    printf("\n%-s\n%-10s|%s\n", "Criterion Power", "alpha", "#(p-value)");
    for (int i = 0; i < 20; i++) {
        printf("%-10.2lf|%.3lf\n", 0.05 * (i + 1), p_distrAlt[i]);
    }



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
    //        vector<int> sample = Generate_Sample(mm, n, HGAlter);
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
}


