#pragma once
#include"Distribution.h"
#include<random>
#include<utility>
#include"Method.h"
#include "PROBDIST.H"
#include<iostream>

/// <summary>
/// @brief Базовый генератор выборки
/// </summary>
class BaseSampleGenerator
{
public:
	// Выделение памяти для выборки
	BaseSampleGenerator(int _samVol) :
		samVol(_samVol), 
		sample(new int[_samVol]) {
	};
	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="bsg"></param>
	BaseSampleGenerator(const BaseSampleGenerator& bsg) :
		samVol(bsg.samVol)
	{
		sample = new int[samVol];
		for (int i = 0; i < samVol; i++) {
			sample[i] = bsg.sample[i];
			}
	};
	/// <summary>
	/// Конструктор перемещения
	/// </summary>
	/// <param name="bsg"></param>
	BaseSampleGenerator(BaseSampleGenerator&& bsg) noexcept : 
		samVol(std::exchange(bsg.samVol,0)), 
		sample(std::move(bsg.sample)) 
	{
		bsg.sample = nullptr;
	}
	/// <summary>
	/// Оператор присваивания с копированием
	/// </summary>
	/// <param name="bsg"></param>
	/// <returns></returns>
	BaseSampleGenerator& operator=(const BaseSampleGenerator& bsg) {
		if (this != &bsg) {
			samVol = bsg.samVol;
			delete[] sample;
			sample = new int[samVol];
			for (int i = 0; i < samVol; i++) {
				sample[i] = bsg.sample[i];
			}
		}
		return *this;
	}
	/// <summary>
	/// Оператор присваивания с перемещением
	/// </summary>
	/// <param name="bsg"></param>
	/// <returns></returns>
	BaseSampleGenerator& operator=(BaseSampleGenerator&& bsg) noexcept {
		if (this != &bsg) {
			sample = std::move(bsg.sample);
			samVol = std::exchange(bsg.samVol, 0);
			bsg.sample = nullptr;
		}
		return *this;
	}
	/// <summary>
	/// Вывод данных о выборке
	/// </summary>
	friend std::ostream& operator<<(std::ostream& os, const BaseSampleGenerator& bsg) {
		os << std::endl << "Объём выборки = " << bsg.samVol;
		os << "\nВыборка: [" << bsg.sample[0];
		for (int i = 1; i < bsg.samVol; i++) {
			os << ", " << bsg.sample[i];
		}
		os << "]" << std::endl;
		return os;
	}
	// Генерация выборки
	virtual void Simulate(const Distribution& dis, int _samVol) = 0;
	virtual ~BaseSampleGenerator() { delete[] sample; samVol = 0; };
	// virtual ~BaseSampleGenerator() = default;
	int* GetSample() const { return sample; };
	int GetSamVol() const { return samVol; };
protected:
	/// <summary>
	/// Массив выборочных значений
	/// </summary>
	int* sample;
	/// <summary>
	/// Объём выборки
	/// </summary>
	int samVol;
};