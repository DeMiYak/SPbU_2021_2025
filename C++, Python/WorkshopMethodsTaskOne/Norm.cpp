#include "Norm.h"

double norm(const vector<vector<double>>& vec)
{
	//double sum = 0;
	//for (size_t i = 0; i < vec.size(); ++i) {
	//	for (size_t j = 0; j < vec[0].size(); ++j) {
	//		sum += vec[i][j] * vec[i][j];
	//	}
	//}
	//return sqrt(sum);
	double maxi = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		for (size_t j = 0; j < vec[0].size(); ++j) {
			maxi = max(maxi, fabs(vec[i][j]));
		}
	}
	return maxi;
}

double norm_subtract(const vector<vector<double>>& vec_main, const vector<vector<double>>& vec_sub)
{
	if (vec_main.size() != vec_sub.size() || vec_main[0].size() != vec_sub[0].size()) {
		exit(2);
	}
	//double sum = 0;
	//size_t vecL = vec_main.size(), vecW = vec_main[0].size();
	//for (size_t i = 0; i < vecL; ++i) {
	//	for (size_t j = 0; j < vecW; ++j) {
	//		sum += pow(vec_main[i][j] - vec_sub[i][j], 2);
	//	}
	//}
	//return sqrt(sum);
	double maxi = 0;
	size_t vecL = vec_main.size(), vecW = vec_main[0].size();
	for (size_t i = 0; i < vecL; ++i) {
		for (size_t j = 0; j < vecW; ++j) {
			maxi = max(maxi, fabs(vec_main[i][j] - vec_sub[i][j]));
		}
	}
	return maxi;
}

/// <summary>
/// Функция для расчёта вектора решений
/// для трёхдиагональной матрицы (метод перегонки)
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="d"></param>
/// <returns></returns>
vector<double> SolveTriagonalMatrix(vector<double> a, vector<double> b, vector<double> c, vector<double> d)
{
	// По идее, здесь нужно проверять на корректность размерностей векторов,
	// но в условиях классов это можно опустить на время
	int n = a.size();
	n--; // since we start from x0 (not x1)
	c[0] /= b[0];
	d[0] /= b[0];

	for (int i = 1; i < n; i++) {
		c[i] /= b[i] - a[i] * c[i - 1];
		d[i] = (d[i] - a[i] * d[i - 1]) / (b[i] - a[i] * c[i - 1]);
	}

	d[n] = (d[n] - a[n] * d[n - 1]) / (b[n] - a[n] * c[n - 1]);

	for (int i = n; i-- > 0;) {
		d[i] -= c[i] * d[i + 1];
	}
	return d;
}
