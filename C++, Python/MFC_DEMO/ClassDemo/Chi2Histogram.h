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
	/// <summary>
	/// Стандартный конструктор класса
	/// </summary>
	ChiSqHistogram() : 
		freqLen(0), 
		empFreq(nullptr), 
		thFreq(nullptr), 
		dof(0), 
		chiSq(0), 
		pLevel(0) {};
	ChiSqHistogram(const BaseSampleGenerator* bsg, const Distribution& dis);
	/// <summary>
	/// Конструктор копирования
	/// </summary>
	ChiSqHistogram(const ChiSqHistogram& csh);
	/// <summary>
	/// Конструктор перемещения
	/// </summary>
	ChiSqHistogram(ChiSqHistogram&& csh);
	/// <summary>
	/// Оператор присваивания с копированием
	/// </summary>
	/// <returns>Элемент класса ChiSqHistogram</returns>
	ChiSqHistogram& operator=(const ChiSqHistogram& csh);
	/// <summary>
	/// Оператор присваивания с перемещением
	/// </summary>
	/// <returns>Элемент класса ChiSqHistogram</returns>
	ChiSqHistogram& operator=(ChiSqHistogram && csh);
	/// <summary>
	/// Оператор вывода класса ChiSqHistogram
	/// </summary>
	friend std::ostream& operator<<(std::ostream& os, const ChiSqHistogram& csh);
	void SetData(const BaseSampleGenerator* bsg, const Distribution& dis);
	void Resize(int _freqLen);
	void CalcChiSq();
	/// <summary>
	/// Получение числа степеней свободы
	/// </summary>
	/// <returns>Число степеней свободы</returns>
	int GetDegreeOfFreedom() const { return dof; }
	/// <summary>
	/// Получение значения хи-квадрата
	/// </summary>
	/// <returns>Значение хи-квадрата</returns>
	double GetChi() const { return chiSq; }
	/// <summary>
	/// Получение порогового значения (p-level)
	/// </summary>
	/// <returns>p-level</returns>
	double GetPLevel() const { return pLevel; }
	/// <summary>
	/// Получение диапазона частот
	/// </summary>
	/// <returns>Диапазон частот</returns>
	int GetFreqLen() const { return freqLen; }
	/// <summary>
	/// Получение теоретических частот
	/// </summary>
	/// <returns>Указатель на массив теоретических частот</returns>
	double* GetThFreq() const { return thFreq; }
	/// <summary>
	/// Получение эмпирических частот
	/// </summary>
	/// <returns>Указатель на массив эмпирических частот</returns>
	int* GetEmpFreq() const { return empFreq; }
	/// <summary>
	/// Деструктор класса
	/// </summary>
	~ChiSqHistogram() {
		delete[] empFreq;
		delete[] thFreq;
		freqLen = 0;
	}
private:
	/// <summary>
	/// Приватный метод для подсчёта теоретических частот
	/// </summary>
	/// <param name="dis">Распределение</param>
	/// <param name="_samVol">Объём выборки</param>
	void CountThFreq(const Distribution& dis, int _samVol);
	/// <summary>
	/// Приватный метод для подсчёта эмпирических частот
	/// </summary>
	/// <param name="bsg">Выборка "после эксперимента"</param>
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