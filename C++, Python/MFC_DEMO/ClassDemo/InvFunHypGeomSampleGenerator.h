#pragma once
#include "SampleModelling.h"
/// <summary>
/// @brief Генератор выборки гипергеометрического распределения методом обратной функции
/// </summary>
class InvFunHypGeomSampleGenerator : public BaseSampleGenerator
{
public:
	/// <summary>
	/// Конструктор класса
	/// </summary>
	/// <param name="_samVol">Объём выборки</param>
	InvFunHypGeomSampleGenerator(int _samVol = 1) : BaseSampleGenerator(_samVol) {};
	/// <summary>
	/// Конструктор класса с начальным распределением
	/// </summary>
	/// <param name="_samVol">Объём выборки</param>
	/// <param name="dis">Распределение</param>
	InvFunHypGeomSampleGenerator(int _samVol, const Distribution& dis) : BaseSampleGenerator(_samVol) {
		Simulate(dis, _samVol);
	};
	/// <summary>
	/// Виртуальная функция генерации выборки
	/// </summary>
	/// <param name="dis">Распределение</param>
	/// <param name="_samVol">Объём выборки</param>
	virtual void Simulate(const Distribution& dis, int _samVol) override;
};


