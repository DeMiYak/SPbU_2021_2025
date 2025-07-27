#pragma once
using namespace std;
#include<vector>

class FYA
{
public:
	FYA(int _length);
	~FYA();
	void Shuffle();
	virtual void Print();
	int GetLength() const { return length; }
	int operator[] (int index) const { 
		if (0 <= index && index < length) {
			return arr[index];
		}
		else exit(1);
	}
protected:
	int* arr;
	int length;
};

int random(int low, int high);

class FYInterface : public FYA {
public:
	FYInterface(int _length = 1, int _k = 1);
	~FYInterface();

	int* GetCycle() const { return cycle; }
	int GetK() const { return K; }
	void ChangeK(int _k) { K = _k; }
	void ResetCycles();

	// Не нужны
	
	// Считает число циклов в одной перестановке
	void CountOnePermutation();

	// Считает число циклов в перестановках
	void CountPermutations(int num);

	// Считывает число циклов длины k
	int CountCycleK();

	virtual void Print();
private:
	int* cycle;
	int K;
	int I;
};

class FYSample {
public:
	FYSample(int _samLen = 1) : samLen(_samLen), sample(new int[_samLen]) {};
	void Simulate(FYInterface& fyi);
	void ChangeLength(int _samLen);
	int* GetSample() const { return sample; }
	int GetLen() const { return samLen; }
	~FYSample() { delete[] sample; }
private:
	int* sample;
	int samLen;
};

class PoissonDistribution {
public:
	PoissonDistribution(double _lambda = 1) : lambda(_lambda) {};
	vector<double> Theory_Prob();
private:
	double lambda;
};

vector<int> Count_Frequency(FYSample& sample, const int length);

vector<double> Theory_Frequency(const vector<double>& tp, int sample_volume);

// Выравнивает длины теоретических/эмпирических частот,
// поскольку теоретические вероятности строятся до eps,
// а freq имеют изначально заданный интервал
void LineLength(vector<double>& tf, vector<int>& freq);

vector<pair<double, int>> Chi_Square_Merge(const vector<double>& tf, const vector<int>& freq);

double Chi_Square(const vector<pair<double, int>>& merge_freq);

int DOF(const vector<pair<double, int>>& merge_freq);

double P_Value(int sample_volume, FYInterface& fyi);

void P_Distribution(vector<double>& p_distr);

void Test();
