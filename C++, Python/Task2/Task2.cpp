#include <cmath>
#include<iostream>

using namespace std;

int main() {

	cout.precision(16);
	double p_1{ 2 }, p_2{ 1 };
	double S{ 0 };
	long long N;
	cin >> N;
	for (long long j{ 2 }; j <= N - 2; p_2 *= j,++j){}
	for (long long i{ 3 }; i <= N; ++i) {
		p_1 *= i;
		p_2 /= (N - i == 0) ? 1 : (N - i + 1);
		S += double(p_1) / p_2;
	}

	cout << S;
}

//	for (cin >> N, S = 0, long long i = 3, long long p_1 = 2, long long p_2 = 1, for (long long j = 2; j <= N - 2; p_2 *= j++); i <= N; S += double(p_1 *= i) / p_2 /= (N - i == 0 ? 1 : N - i)){}