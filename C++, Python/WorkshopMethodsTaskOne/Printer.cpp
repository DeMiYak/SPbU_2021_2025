#include "Printer.h"

/// Список требований, исходя из
/// примера задачи 3 в Teams:
/// 1. Название метода, вариант задачи
/// 2. Число сегментов по оси X (N) и по оси Y (M)
/// 3. Степень точности eps
/// 4. Мера аппроксимации ||F-AU^*||
/// 5. Норма разности для U^0: ||F-AU^0||
/// 6. Число итераций iter_num
/// 7. Спектральный радиус матрицы H (rho_H) (как считать?)
/// 8. Квадрат спектрального радиуса
/// 9. Параметр тау
/// 
/// Затем идёт таблица в которой слева-направо указаны:
/// 1. Номер итерации k
/// 2. Мера аппроксимации при k
/// 3. Относительная невязка
/// 4. Мера разности ||U^k-U^*||
/// 5. Относительная погрешность
/// 6. ||U^k-U^{k-1}||
/// 7. Апостериорная оценка
/// 8. Спектральный радиус матрицы (какой-то)
/// 
/// А также таблицы приближённого и точного решений

void PRINTER::PrintTable()
{
	int tablelimit = 500;
	const vector<vector<double>> U_0 = resolver.GetU();
	// Печать таблицы
	bmg->PrintName();
	const double AUstar = Discrepancy(Ustar, resolver);
	/// Делаем по 2.
	const double discr_0 = Discrepancy(U_0, resolver);
	// 5. Норма разности U^0 и U^*
	const double difference_0 = norm_subtract(U_0, Ustar);
	cout << "\n\n2. N = " << resolver.GetNX() << ", M = " << resolver.GetMY();
	cout << "\n\n4. Measure of approximation: ||F-AU^*|| = " << AUstar;
	cout << "\n\n5. Difference norm: ||F-AU^0|| = " << discr_0;
	cout << "\n\n6. Iteration num = " << tablelimit << endl;
	cout << endl << "Printing table: " << endl;
	printf("%-5s|%11s |%11s |%12s |%12s| ", "k", "||F-AU^k||", "rel.d", "||U^k-U^*||", "rel.error");
	printf("%14s |%12s|%10s|\n", "||U^k-U^k-1||", "apost.est", "spec.rad");
	
	// 1. Номер итерации
	int k = 1;

	/// Идея: для вычисления спектрального радиуса
	/// требуется знать U_k, U_k-1, U_k-2.
	/// Для этого можно поступить двумя способами:
	/// 1. Сделать vector<double> для сохранения ||U_k-U_k-1||
	/// 2. Делать предварительное вычисление перед каждым U_k,
	/// что выгоднее в плане вычислений, но в коде может оказаться
	/// некрасивым
	/// 
	bmg->Re_Calculate(1, resolver);
	vector<vector<double>> U_1 = bmg->GetResU();
	double main_diff = norm_subtract(U_1, U_0), aux_diff;
	const double discr_1 = Discrepancy(U_1, resolver);
	const double difference_1 = norm_subtract(U_1, Ustar);
	printf("%-5d|%11.3lf |%11.3lf |%12.3lf |%12.3lf| ", k, discr_1, discr_1/discr_0, difference_1, difference_1/difference_0);
	printf("%14.3lf |%12s|%10s|\n", main_diff,"","");
	/*for (; k <= tablelimit; ++k)*/
	while(k<tablelimit){
		// Приращения для таблицы
		if (k < 5) {
			++k;
		}
		else if (k < 50) {
			k += 5;
		}
		else{
			k += 50;
		}
		/// В связи с этим, небольшие изменения:
		/// Будем вычислять k-1 и k и на их основании
		/// выводить полученные значения. Просто и надёжно,
		/// учитывая, что в Re_Calculate рассмотрены все случаи

		bmg->Re_Calculate(k-1, resolver);
		vector<vector<double>> U_k_2 = bmg->GetPrevResU();

		bmg->Re_Calculate(k, resolver);
		vector<vector<double>> U_k = bmg->GetResU();
		// Невязка ||F-AU^k|| - 2. Мера аппроксимации.
		// Вычисления можно оптимизировать, но как-то лень
		double dis_u_k = Discrepancy(U_k, resolver);
		vector<vector<double>> U_k_1 = bmg->GetPrevResU();
		
		/*double dis_u_k_1 = Discrepancy(U_k_1, resolver);*/
		
		// 3. Относительная невязка
		double rel_discr = dis_u_k / discr_0;
		// 4. Мера разности U^k и U^*
		double diffResU = norm_subtract(U_k, Ustar);

		// 5. Относительная погрешность
		double rel_diff = diffResU / difference_0;

		// 6. Норма разности двух соседних приближений (main_diff)
		aux_diff = norm_subtract(U_k_1, U_k_2);
		main_diff = norm_subtract(U_k, U_k_1);

		/// 8. Спектральный радиус матрицы H
		/// Вообще, здесь должна быть проверка на равенство
		/// по модуль минимального и максимального собственных чисел
		/// матрицы H. В случае этой задачи, условием равенства является
		/// равенство hx и hy.
		/// Проверим позже экспериментальным способом на ошибочность
		double spec_radius = main_diff / aux_diff;
		
		// 7. Апостериорная оценка (для методов 1-4)
		double apost_est = spec_radius / (1 - spec_radius) * main_diff;
		printf("%-5d|%11.3lf |%11.3lf |%12.3lf |%12.3lf| ", k, dis_u_k, rel_discr, diffResU, rel_diff);
		printf("%14.3lf |%12.3lf|%10.3lf|", main_diff, apost_est, spec_radius);
		cout << endl;
	}


	// Печать приближённых значений
	bmg->PrintData();
	// Печать точных значений
	PrintUstar();
	
}

void PRINTER::PrintUstar()
{
	sizetype Nx = Ustar.size(), My = Ustar[0].size();
	cout << endl << "Solution table:" << endl;
	for (int i = My - 1; i >= 0; --i) {
		for (int j = 0; j < Nx; ++j) {
			cout << Ustar[j][i] << setw(7);
		}
		cout << endl;
	}
	cout << endl;
}

/// <summary>
/// Вычисление невязки
/// </summary>
/// <param name="vec"></param>
/// <param name="resolver"></param>
/// <returns></returns>
double PRINTER::Discrepancy(const vector<vector<double>>& vec, const RESOLVER& resolver)
{	
	size_t vecL = vec.size(), vecW = vec[0].size();
	double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	vector<vector<double>> vecDis(vecL, vector<double>(vecW, 0));
	for (size_t i = 1; i < vecL-1; ++i) {
		for (size_t j = 1; j < vecW-1; ++j) {
			vecDis[i][j] = (vec[i + 1][j] + vec[i-1][j]-2*vec[i][j])*hx_2+
				(vec[i][j-1]+vec[i][j+1]-2*vec[i][j])*hy_2;
		}
	}
	return norm(vecDis);
}
