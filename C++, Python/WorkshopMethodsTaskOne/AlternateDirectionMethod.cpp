#include "AlternateDirectionMethod.h"

void AlternateDirectionMethod::Calculate(const RESOLVER& resolver)
{
	resU = resolver.GetU();
	for (sizetype i = 0; i < iter_num; ++i) {
		IterateOnce(resolver);
	}
}

void AlternateDirectionMethod::ChangeIterNum(sizetype _iter_num)
{
	iter_num = _iter_num;
}

void AlternateDirectionMethod::PrintName()
{
	cout << endl << "Alternate Direction Method. Variant 4." << endl;
}

//void AlternateDirectionMethod::ApplyTriagonalAlg()
//{
//}

/// <summary>
/// Функция для посчёта одной итерации с прогонкой.
/// Замечание: в этот метод не добавлены вычисления
/// в случае функции с независимым временем. Можно обговорить
/// с преподавателем.
/// </summary>
/// <param name="resolver"></param>
void AlternateDirectionMethod::IterateOnce(const RESOLVER& resolver)
{
	const sizetype nx = resolver.GetNX() + 1, my = resolver.GetMY() + 1;
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	// Предыдущий ResU, или k
	prevResU = resU;
	// resU_halfer - промежуточный ResU (k->k+1/2)
	vector<vector<double>> resU_halfer = resU;
	
	// Первый вектор G для промежуточных результатов
	vector<vector<double>> G_first(my, vector<double>(nx, 0));
	// Вычисление G_first
	for (sizetype i = 1; i < nx-1; ++i) {
		for (sizetype j = 1; j < my-1; ++j) {
			G_first[j][i] = -prevResU[i][j] - t / 2 * 
				hy_2 * (prevResU[i][j - 1] + 
					prevResU[i][j + 1] - 2*prevResU[i][j]);
		}
	}
	// Коэффициенты для метода прогонки по горизонтали
	const double A_1 = t / 2 * hx_2, B_1 = t * hx_2 + 1, C_1 = t / 2 * hx_2;
	vector<double> vecA_1(nx-2, A_1), vecB_1(nx-2, -B_1), vecC_1(nx-2, C_1);
	// Вычисление resU_halfer
	for (sizetype i = 1; i < my - 1; ++i) {
		// const_iterator предназначен для выделения подвектора
		vector<double>::const_iterator first = G_first[i].begin() + 1;
		vector<double>::const_iterator last = G_first[i].end() - 1;
		vector<double> vecD_1(first, last);
		vecD_1[0] -= A_1 * prevResU[0][i];
		vecD_1[nx - 3] -= A_1 * prevResU[nx - 1][i];
		vector<double> Uline = SolveTriagonalMatrix(vecA_1, vecB_1, vecC_1, vecD_1);
		for (sizetype j = 1; j < nx - 1; ++j) {
			resU_halfer[j][i] = Uline[j - 1];
		}
	}


	// Коэффициенты для метода прогонки по вертикали
	const double A_2 = t / 2 * hy_2, B_2 = t * hy_2 + 1, C_2 = t / 2 * hy_2;
	// Второй вектор G для промежуточных вычислений
	vector<vector<double>> G_second(nx, vector<double>(my, 0));
	// Вычисление G_second
	for (sizetype i = 1; i < nx - 1; ++i) {
		for (sizetype j = 1; j < my - 1; ++j) {
			G_second[i][j] = -resU_halfer[i][j] - t / 2 *
				hx_2 * (resU_halfer[i-1][j] 
					+ resU_halfer[i+1][j] - 2 * resU_halfer[i][j]);
		}
	}

	vector<double> vecA_2(my - 2, A_2), vecB_2(my - 2, -B_2), vecC_2(my - 2, C_2);
	// Вычисление resU_halfer
	for (sizetype i = 1; i < nx - 1; ++i) {
		// const_iterator предназначен для выделения подвектора
		vector<double>::const_iterator first = G_second[i].begin() + 1;
		vector<double>::const_iterator last = G_second[i].end() - 1;
		vector<double> vecD_2(first, last);
		vecD_2[0] -= A_2 * resU_halfer[i][0];
		vecD_2[my - 3] -= A_2 * resU_halfer[i][my-1];
		vector<double> Uline = SolveTriagonalMatrix(vecA_2, vecB_2, vecC_2, vecD_2);
		for (sizetype j = 1; j < my - 1; ++j) {
			resU[i][j] = Uline[j - 1];
		}
	}
}
