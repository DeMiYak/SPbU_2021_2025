#pragma once
#include<random>

class Distribution {
public:
	void ChangeWhBalls(int _whBalls = 20) {
		whBalls = _whBalls;
	}
	void ChangeBlBalls(int _blBalls = 30) {
		blBalls = _blBalls;
	}
	void ChangePickNum(int _pickNum = 10) {
		pickNum = _pickNum;
	}
	int GetWhBalls() const { return whBalls; }
	int GetBlBalls() const { return blBalls; }
	int GetPickNum() const { return pickNum; }
private:
	// Х параметры распределени€, с которыми моделируетс€ распределение
	int whBalls, blBalls, pickNum;

	// Х параметры распределени€ дл€ нулевой гипотезы
};

class SampleModelling
{
public:
	/*SampleModelling(int _whBalls, int _blBalls, int _pickNum, int _samVol, std::random_device& _rd):
		whBalls(_whBalls), blBalls(_blBalls), pickNum(_pickNum), rd(_rd), samVol(_samVol), sample(nullptr) {};*/
	SampleModelling(int _samVol) : samVol(_samVol), sample(new int[_samVol]) {};
	virtual void Simulate(Distribution dis, int _samVol) = 0;
	virtual ~SampleModelling() { delete[] sample; };
public:
	// Х результат моделировани€(выборка : массив плюс размер)
	int* sample;
	int samVol;
};

class BernoulliSample : public SampleModelling
{
public:
	BernoulliSample(int _samVol = 1) : SampleModelling(_samVol) {};
	virtual void Simulate(Distribution dis, int _samVol) override;
};

class InverseFunctionSample : public SampleModelling
{
public:
	InverseFunctionSample(int _samVol = 1) : SampleModelling(_samVol) {};
	virtual void Simulate(Distribution dis, int _samVol) override;
};

class Histogram
{
public:
	Histogram() {
		empLen = 1;
		empFreq = new int[empLen];
	}
	void SetLength(int _empLen) {
		if (empLen == _empLen)
			return;
		empLen = _empLen;
		delete[] empFreq;
		empFreq = new int[empLen];
	}
	~Histogram() {
		delete[] empFreq;
		empLen = 0;
	}
	int GetEmpLength() const { return empLen; }
	int* GetEmpFrequency() const { return empFreq; }
	void CountSampleFrequency(SampleModelling* samMod, Distribution dis);
private:
	void NullifyEmpFrequency();
	// Distribution distrHist;
	// SampleModelling* samHist;
	// Х частоты теоретического распределени€
	// Х частоты эмпирического распределени€
	int* empFreq;
	int empLen;
	// Х результаты применени€ хи-квадрат.
};

