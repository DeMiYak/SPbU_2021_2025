#pragma once
#include "SampleModelling.h"
/// <summary>
/// @brief Генератор выборки гипергеометрического распределения методом 
/// распределения Бернулли
/// </summary>
class BernHypGeomSampleGenerator : public BaseSampleGenerator
{
public:
	BernHypGeomSampleGenerator(int _samVol = 1) : BaseSampleGenerator(_samVol) {};
	BernHypGeomSampleGenerator(int _samVol, const Distribution& dis) : BaseSampleGenerator(_samVol) {
		Simulate(dis, _samVol);
	};
	virtual void Simulate(const Distribution& dis, int _samVol) override;
};

