#pragma once
#include "SampleModelling.h"
/// <summary>
/// @brief Генератор выборки гипергеометрического распределения методом обратной функции
/// </summary>
class InvFunHypGeomSampleGenerator : public BaseSampleGenerator
{
public:
	InvFunHypGeomSampleGenerator(int _samVol = 1) : BaseSampleGenerator(_samVol) {};
	InvFunHypGeomSampleGenerator(int _samVol, const Distribution& dis) : BaseSampleGenerator(_samVol) {
		Simulate(dis, _samVol);
	};
	virtual void Simulate(const Distribution& dis, int _samVol) override;
};


