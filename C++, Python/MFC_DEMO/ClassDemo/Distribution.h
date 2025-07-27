#pragma once
#include<utility>
#include<cstring>
#include<iostream>

/// <summary>
/// @brief Класс гипергеометрического распределения
/// </summary>
class Distribution {
public:
	Distribution(int _whBalls = 20, int _blBalls = 30, int _pickNum = 10);
	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="dis">Распределение</param>
	Distribution(const Distribution& dis) :
		whBalls(dis.whBalls),
		blBalls(dis.blBalls),
		pickNum(dis.pickNum)
	{
		int len = pickNum + 1;
		thProb = new double[len];
		for (int i = 0; i < len; i++) {
			thProb[i] = dis.thProb[i];
		}
	}
	/// <summary>
	/// Конструктор перемещения
	/// </summary>
	/// <param name="dis">Распределение</param>
	Distribution(Distribution&& dis) noexcept : 
		whBalls(std::exchange(dis.whBalls, 0)), 
		blBalls(std::exchange(dis.blBalls, 0)), 
		pickNum(std::exchange(dis.pickNum, 0)), 
		thProb(std::move(dis.thProb)) {
		dis.thProb = nullptr;
	}
	/// <summary>
	/// Оператор присваивания с копированием
	/// </summary>
	/// <param name="dis">Распределение</param>
	/// <returns>Распределение</returns>
	Distribution& operator=(const Distribution& dis) {
		if (this != &dis) {
			// SetParameters(dis.whBalls, dis.blBalls, dis.pickNum);
			whBalls = dis.whBalls;
			blBalls = dis.blBalls;
			pickNum = dis.pickNum;
			delete[] thProb;
			int len = pickNum + 1;
			thProb = new double[len];
			for (int i = 0; i < len; i++) {
				thProb[i] = dis.thProb[i];
			}
		}
		return *this;
	}
	/// <summary>
	/// Оператор присваивания с перемещением
	/// </summary>
	/// <param name="dis">Распределение</param>
	/// <returns>Распределение</returns>
	Distribution& operator=(Distribution&& dis) noexcept {
		if (this != &dis) {
			whBalls = std::exchange(dis.whBalls, 0);
			blBalls = std::exchange(dis.blBalls, 0);
			pickNum = std::exchange(dis.pickNum, 0);
			thProb = std::move(dis.thProb);
			dis.thProb = nullptr;
		}
		return *this;
	}
	/// <summary>
	/// Оператор вывода класса Distribution
	/// </summary>
	friend std::ostream& operator<<(std::ostream& os, const Distribution& dis) {
		os << std::endl << "Белые шарики: " << dis.whBalls;
		os << ", чёрные шарики: " << dis.blBalls;
		os << ", число вытаскиваний: " << dis.pickNum;
		os << "\nТеоретические вероятности: [" << dis.thProb[0];
		for (int i = 1; i < dis.pickNum + 1; i++) {
			os << ", " << dis.thProb[i];
		}
		os << "]" << std::endl;
		return os;
	}
	/// <summary>
	/// Деструктор класса
	/// </summary>
	~Distribution() {
		delete[] thProb;
		whBalls = 0;
		blBalls = 0;
		pickNum = 0;
	}
	/// <summary>
	/// Задаёт параметры и перестраивает массив теоретических вероятностей
	/// </summary>
	/// <param name="_whBalls">Белые шарики</param>
	/// <param name="_blBalls">Чёрные шарики</param>
	/// <param name="_pickNum">Число вытаскиваний</param>
	void SetParameters(int _whBalls = 20, int _blBalls = 30, int _pickNum = 10);
	/// <summary>
	/// Получение числа белых шариков
	/// </summary>
	/// <returns>Число белых шариков</returns>
	int GetWhBalls() const { return whBalls; }
	/// <summary>
	/// Получение числа чёрных шариков
	/// </summary>
	/// <returns>Число чёрных шариков</returns>
	int GetBlBalls() const { return blBalls; }
	/// <summary>
	/// Получение числа вытаскиваний
	/// </summary>
	/// <returns>Число вытаскиваний</returns>
	int GetPickNum() const { return pickNum; }
	/// <summary>
	/// Получение теоретических вероятностей
	/// </summary>
	/// <returns>Указатель на массив теоретических вероятностей</returns>
	double* GetThProb() const { return thProb; }
	/// <summary>
	/// Имя гипергеометрического распределения
	/// </summary>
	/// <returns>Указатель на имя распределения</returns>
	const wchar_t* GetName();
	
private:
	/// <summary>
	/// Метод построения теоретических вероятностей гипергеометрического распределения 
	/// по его параметрам
	/// </summary>
	void TheorProb();
	
	/// <summary>
	/// Белые шарики
	/// </summary>
	int whBalls;
	/// <summary>
	/// Чёрные шарики
	/// </summary>
	int blBalls; 
	/// <summary>
	/// Число вытаскиваний
	/// </summary>
	int pickNum;
	/// <summary>
	/// Массив теоретических вероятностей
	/// </summary>
	double* thProb;
};

