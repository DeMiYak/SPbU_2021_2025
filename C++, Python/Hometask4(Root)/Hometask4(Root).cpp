#include "Hometask4.h"

int main()
{
	optd x_res = findRoot(f, 7, 20);
	if (!x_res) {
		std::cout << "Root not found";
		exit(1);
	}
	std::cout << "x = " << x_res.value() << "\n|f(x)| = " << fabs(f(x_res.value())) << std::endl;
}

double f(double x) {
	return 1e-7 - exp(-x);
}

inline bool checkRoot(double stVal, double endVal) {	
	return stVal >= 0 == endVal <= 0;
}

optd findRoot(func f, double segBeg, double segEnd, double eps) {
	double f_start = f(segBeg), f_end = f(segEnd);
	if (!checkRoot(f_start, f_end)) return std::nullopt;
	double mid = (segBeg + segEnd) / 2;
	double midVal = f(mid);
	
	if (f_start >= 0) {
		double temp = segBeg;
		segBeg = segEnd;
		segEnd = temp;
	}
	while (fabs(midVal) > eps) { // |f(x)| > eps
		if (midVal > 0) {
			segEnd = mid;
			mid = (segBeg + mid) / 2;
		}
		else {
			segBeg = mid;
			mid = (segEnd + mid) / 2;
		}
		midVal = f(mid);
	}
	return mid;
}