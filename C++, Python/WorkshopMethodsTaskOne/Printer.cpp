#include "Printer.h"

/// ������ ����������, ������ ��
/// ������� ������ 3 � Teams:
/// 1. �������� ������, ������� ������
/// 2. ����� ��������� �� ��� X (N) � �� ��� Y (M)
/// 3. ������� �������� eps
/// 4. ���� ������������� ||F-AU^*||
/// 5. ����� �������� ��� U^0: ||F-AU^0||
/// 6. ����� �������� iter_num
/// 7. ������������ ������ ������� H (rho_H) (��� �������?)
/// 8. ������� ������������� �������
/// 9. �������� ���
/// 
/// ����� ��� ������� � ������� �����-������� �������:
/// 1. ����� �������� k
/// 2. ���� ������������� ��� k
/// 3. ������������� �������
/// 4. ���� �������� ||U^k-U^*||
/// 5. ������������� �����������
/// 6. ||U^k-U^{k-1}||
/// 7. ������������� ������
/// 8. ������������ ������ ������� (�����-��)
/// 
/// � ����� ������� ������������ � ������� �������

void PRINTER::PrintTable()
{
	int tablelimit = 500;
	const vector<vector<double>> U_0 = resolver.GetU();
	// ������ �������
	bmg->PrintName();
	const double AUstar = Discrepancy(Ustar, resolver);
	/// ������ �� 2.
	const double discr_0 = Discrepancy(U_0, resolver);
	// 5. ����� �������� U^0 � U^*
	const double difference_0 = norm_subtract(U_0, Ustar);
	cout << "\n\n2. N = " << resolver.GetNX() << ", M = " << resolver.GetMY();
	cout << "\n\n4. Measure of approximation: ||F-AU^*|| = " << AUstar;
	cout << "\n\n5. Difference norm: ||F-AU^0|| = " << discr_0;
	cout << "\n\n6. Iteration num = " << tablelimit << endl;
	cout << endl << "Printing table: " << endl;
	printf("%-5s|%11s |%11s |%12s |%12s| ", "k", "||F-AU^k||", "rel.d", "||U^k-U^*||", "rel.error");
	printf("%14s |%12s|%10s|\n", "||U^k-U^k-1||", "apost.est", "spec.rad");
	
	// 1. ����� ��������
	int k = 1;

	/// ����: ��� ���������� ������������� �������
	/// ��������� ����� U_k, U_k-1, U_k-2.
	/// ��� ����� ����� ��������� ����� ���������:
	/// 1. ������� vector<double> ��� ���������� ||U_k-U_k-1||
	/// 2. ������ ��������������� ���������� ����� ������ U_k,
	/// ��� �������� � ����� ����������, �� � ���� ����� ���������
	/// ����������
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
		// ���������� ��� �������
		if (k < 5) {
			++k;
		}
		else if (k < 50) {
			k += 5;
		}
		else{
			k += 50;
		}
		/// � ����� � ����, ��������� ���������:
		/// ����� ��������� k-1 � k � �� �� ���������
		/// �������� ���������� ��������. ������ � ������,
		/// ��������, ��� � Re_Calculate ����������� ��� ������

		bmg->Re_Calculate(k-1, resolver);
		vector<vector<double>> U_k_2 = bmg->GetPrevResU();

		bmg->Re_Calculate(k, resolver);
		vector<vector<double>> U_k = bmg->GetResU();
		// ������� ||F-AU^k|| - 2. ���� �������������.
		// ���������� ����� ��������������, �� ���-�� ����
		double dis_u_k = Discrepancy(U_k, resolver);
		vector<vector<double>> U_k_1 = bmg->GetPrevResU();
		
		/*double dis_u_k_1 = Discrepancy(U_k_1, resolver);*/
		
		// 3. ������������� �������
		double rel_discr = dis_u_k / discr_0;
		// 4. ���� �������� U^k � U^*
		double diffResU = norm_subtract(U_k, Ustar);

		// 5. ������������� �����������
		double rel_diff = diffResU / difference_0;

		// 6. ����� �������� ���� �������� ����������� (main_diff)
		aux_diff = norm_subtract(U_k_1, U_k_2);
		main_diff = norm_subtract(U_k, U_k_1);

		/// 8. ������������ ������ ������� H
		/// ������, ����� ������ ���� �������� �� ���������
		/// �� ������ ������������ � ������������� ����������� �����
		/// ������� H. � ������ ���� ������, �������� ��������� ��������
		/// ��������� hx � hy.
		/// �������� ����� ����������������� �������� �� �����������
		double spec_radius = main_diff / aux_diff;
		
		// 7. ������������� ������ (��� ������� 1-4)
		double apost_est = spec_radius / (1 - spec_radius) * main_diff;
		printf("%-5d|%11.3lf |%11.3lf |%12.3lf |%12.3lf| ", k, dis_u_k, rel_discr, diffResU, rel_diff);
		printf("%14.3lf |%12.3lf|%10.3lf|", main_diff, apost_est, spec_radius);
		cout << endl;
	}


	// ������ ����������� ��������
	bmg->PrintData();
	// ������ ������ ��������
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
/// ���������� �������
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
