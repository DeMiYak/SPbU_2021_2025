#include "FYA.h"
#include "PROBDIST.H"
#include <iostream>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
double eps = 1e-15;

int random(int low, int high)
{
	std::uniform_int_distribution<> rang(low, high);
	return rang(gen);
}

FYA::FYA(int _length) : length(_length)
{
	arr = new int[length];
	for (int i = 0; i < length; ++i) {
		arr[i] = i + 1;
	}
}

void FYA::Shuffle()
{
	for (int i = length - 1; i > 0; --i) {
		int j = random(0, i);
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

void FYA::Print()
{
	std::cout << "{ " << arr[0] << ", ";
	for (int i = 1; i < length - 1; ++i) {
		std::cout << arr[i] << ", ";
	}
	std::cout << arr[length - 1] << " }" << std::endl;
}

FYA::~FYA()
{
	delete[] arr;
}

FYInterface::FYInterface(int _length, int _k) : FYA(_length), K(_k)
{
	cycle = new int[_length];
	for (int i = 0; i < _length; ++i) {
		cycle[i] = 0;
	}
}

FYInterface::~FYInterface()
{
	delete[] cycle;
}

void FYInterface::CountOnePermutation()
{
	// Вводим вектор флажков для обхода
	vector<int> flag(length);

	for (int i = 0; i < length; ++i) {
		int count = 0;
		// Если флаг = 0 (не посещал клетку),
		// то пробегаемся по циклу и помечаем 1.
		if (flag[i] == 0) {
			// Прибавляем к длине цикла
			++count;
			flag[i] = 1;
			int k = arr[i] - 1;
			while (flag[k] != 1) {
				++count;
				flag[k] = 1;
				k = arr[k] - 1;
			}
			// Получили длину цикла count, занесём в cycle
			++cycle[count - 1];
		}
	}
}

void FYInterface::CountPermutations(int num)
{
	for (int i = 0; i < num; ++i) {
		Shuffle();
		CountOnePermutation();
	}
}

void FYInterface::ResetCycles()
{
	for (int i = 0; i < length; ++i) {
		cycle[i] = 0;
	}
}

int FYInterface::CountCycleK()
{
	int j = 0;

	// Вводим массив флажков для нахождения циклов
	vector<int> flag(length);

	// Пробегаемся по перестановке и считаем циклы фиксированной длины 
	for (int i = 0; i < length; ++i) {
		int count = 0;
		// Если флаг = 0 (не посещал клетку),
		// то пробегаемся по циклу и помечаем 1.
		if (flag[i] == 0) {
			// Прибавляем к длине цикла
			++count;
			flag[i] = 1;
			int k = arr[i] - 1;
			while (flag[k] != 1) {
				++count;
				flag[k] = 1;
				k = arr[k] - 1;
			}
			// Если длина цикла совпадает с указанной, то прибавляем 1
			if (count == K) {
				++j;
			}
		}
	}
	return j;
}

void FYInterface::Print()
{
	std::cout << "{ " << cycle[0] << ", ";
	for (int i = 1; i < length - 1; ++i) {
		std::cout << cycle[i] << ", ";
	}
	std::cout << cycle[length - 1] << " }" << std::endl;
}

void FYSample::Simulate(FYInterface& fyi)
{
	for (int i = 0; i < samLen; ++i) {
		fyi.Shuffle();
		sample[i] = fyi.CountCycleK();
	}
}

void FYSample::ChangeLength(int _samLen) {
	if (_samLen == samLen) {
		return;
	}
	samLen = _samLen;
	delete[] sample;
	sample = new int[samLen];
}

vector<double> PoissonDistribution::Theory_Prob()
{
	vector<double> tp(0);
	double thVal = exp(-lambda);
	tp.push_back(thVal);
	int i = 1;
	while(thVal > eps) {
		tp.push_back(thVal *= lambda / i);
		++i;
	}
	return tp;
}

vector<int> Count_Frequency(FYSample& sample, const int length) {
	int* smp = sample.GetSample();
	int smLen = sample.GetLen();
	vector<int> freq(length);
	for (int i = 0; i < smLen; ++i) {
		freq[smp[i]]++;
	}
	return freq;
}

vector<double> Theory_Frequency(const vector<double>& tp, int sample_volume) {
	int n = tp.size();
	vector<double> tf(n);
	for (int i = 0; i < n; ++i) {
		tf[i] = sample_volume * tp[i];
	}
	return tf;
}

void LineLength(vector<double>& tf, vector<int>& freq){
	int ntf = tf.size(), nfreq = freq.size();
	while (nfreq < ntf) {
		freq.push_back(0);
		++nfreq;
	}
	while (ntf < nfreq) {
		tf.push_back(0);
		++ntf;
	}
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
			merge_vector.push_back(pair<double, int>(sum_tf, sum_freq));
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
		chi += pow((merge_freq[i].first - merge_freq[i].second), 2) / merge_freq[i].first;
	return chi;
}

int DOF(const vector<pair<double, int>>& merge_freq)
{
	return merge_freq.size() - 1;
}

double P_Value(int sample_volume, FYInterface& fyi) {
	//vector<int> sample = Generate_Sample(mm, sample_volume, HGAlter);
	int length = fyi.GetLength();
	PoissonDistribution pd(1. / fyi.GetK());
	FYSample sample(sample_volume);
	sample.Simulate(fyi);
	vector<int> freq = Count_Frequency(sample, length);
	const vector<double> tp = pd.Theory_Prob();
	vector<double> tf = Theory_Frequency(tp, sample_volume);
	LineLength(tf, freq);
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

void Test() {
	int len = 20, k = 3;
	int iternum = 10e2;
	int num = 10e2;
	FYInterface fyi(len, k);

	// Сырое тестирование FYSample
	printf("%-10s\n", "K Count");
	for (int i = 0; i < 100; i++) {
		fyi.Shuffle();
		// fyi.CountOnePermutation();
		// fyi.Print();
		cout << fyi.CountCycleK() << endl;
		// fyi.ResetCycles();
		//printf("%-10d\n", fyi.CountCycleK());
	}

	PoissonDistribution pd(1. / fyi.GetK());
	FYSample sample(num);
	sample.Simulate(fyi);
	vector<int> freq = Count_Frequency(sample, len);
	const vector<double> tp = pd.Theory_Prob();
	vector<double> tf = Theory_Frequency(tp, num);
	LineLength(tf, freq);
	vector<pair<double, int>> m_f = Chi_Square_Merge(tf, freq);
	double chi = Chi_Square(m_f);
	int dof = DOF(m_f);
	double p_level = 1 - pChi(chi, dof);

	int f_s = 0;
	double tf_s = 0;
	printf("%-s\n%-10s|%s\n", "Frequency", "Empiric", "Theoretical");
	for (int i = 0; i <= k; ++i) {
		printf("%-10d|%.5lf\n", freq[i], tf[i]);
		f_s += freq[i];
		tf_s += tf[i];
	}
	printf("\n%-30s%d\n%-30s%.6lf\n", "Sample Volume: ", num, "Chi-Square: ", chi);
	printf("%-30s%d\n%-30s%.6lf\n", "Degree of Freedom: ", dof, "P-level: ", p_level);
	printf("%-30s%d\n%-30s%.6lf\n", "Empiric Frequency: ", f_s, "Theoretical Frequency: ", tf_s);

	printf("\n%-s\n%-10s|%s\n", "Aggregated frequencies", "Empiric", "Theoretical");
	for (int i = 0; i < m_f.size(); ++i) {
		printf("%-10d|%lf\n", m_f[i].second, m_f[i].first);
	}

	printf("\n%-s\n", "Distribution of sample compared to Poisson");

	vector<double> p_distr(20);
	for (int i = 0; i < iternum; i++) {
		double p_level = P_Value(num, fyi);
		// Это распределение должно получиться равномерным, если проверяем нулевую гипотезу
		p_level = floor(p_level / 0.05);
		if (p_level == 20) p_level--;
		p_distr[p_level]++;
	}

	P_Distribution(p_distr);

	printf("\n%-s\n%-10s|%s\n", "Type I Error", "alpha", "#(p-value)");
	for (int i = 0; i < 20; i++) {
		printf("%-10.2lf|%.3lf\n", 0.05 * (i + 1), p_distr[i]);
	}


	// По i-ой позиции
	num = 10e5, len = 40;
	int ind = 3;
	FYInterface fyiN(len, ind);
	vector<int> frequency(len);
	for (int i = 0; i < num; ++i) {
		fyiN.Shuffle();
		int q = fyiN[ind];
		++frequency[q - 1];
	}
	
	printf("\n%-s\n", "Frequencies by index-th position");
	printf("%-s%d\n%-5s|%s\n", "index: ", ind, "i", "Count");
	for (int i = 0; i < len; i++) {
		printf("%-5d|%.3lf\n", i + 1, double(frequency[i])/num);
	}
};