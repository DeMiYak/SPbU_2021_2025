#pragma once
#include"SampleModelling.h"
#include"Distribution.h"
#include"InvFunHypGeomSampleGenerator.h"
#include"BernHypGeomSampleGenerator.h"

/** 
* @brief Класс для хранения эмпирических и теоретических частот, а также
* вычисления степени свободы, значения хи-квадрата и порогового уровня (p-level).
*/
class ChiSqHistogram
{
public:
	ChiSqHistogram() : 
		freqLen(0), 
		empFreq(nullptr), 
		thFreq(nullptr), 
		dof(0), 
		chiSq(0), 
		pLevel(0) {};
	ChiSqHistogram(const BaseSampleGenerator* bsg, const Distribution& dis);
	ChiSqHistogram(const ChiSqHistogram& csh);
	ChiSqHistogram(ChiSqHistogram&& csh);
	ChiSqHistogram& operator=(const ChiSqHistogram& csh);
	ChiSqHistogram& operator=(ChiSqHistogram && csh);
	friend std::ostream& operator<<(std::ostream& os, const ChiSqHistogram& csh);
	void SetData(const BaseSampleGenerator* bsg, const Distribution& dis);
	void Resize(int _freqLen);
	void CalcChiSq();
	int GetDegreeOfFreedom() const { return dof; }
	double GetChi() const { return chiSq; }
	double GetPLevel() const { return pLevel; }
	int GetFreqLen() const { return freqLen; }
	double* GetThFreq() const { return thFreq; }
	int* GetEmpFreq() const { return empFreq; }
	~ChiSqHistogram() {
		delete[] empFreq;
		delete[] thFreq;
		freqLen = 0;
	}
private:
	void CountThFreq(const Distribution& dis, int _samVol);
	void CountEmpFreq(const BaseSampleGenerator* bsg);
	/// <summary>
	/// Массив эмпирических частот
	/// </summary>
	int* empFreq;
	/// <summary>
	/// Массив теоретических частот
	/// </summary>
	double* thFreq;
	/// <summary>
	/// Диапазон частотных значений
	/// </summary>
	int freqLen;
	/// <summary>
	/// Степень свободы
	/// </summary>
	int dof;
	/// <summary>
	/// Значение хи-квадрат
	/// </summary>
	double chiSq;
	/// <summary>
	/// Пороговый уровень
	/// </summary>
	double pLevel;

};