// Task4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
using namespace std;

const int BUFFER_SIZE = 4096;

int main()
{
	int m;
	cout << "Enter m (number of rows > 0): ";
	cin >> m;
	while (m < 1) {
		cout << "Incorrect number of rows (must be > 0), try again: ";
		cin >> m;
	}

	double x;
	double arrayX[BUFFER_SIZE][2];
	for (int i = 0; i < m; ++i) {
		cin >> x;
		arrayX[i][0] = x;
		arrayX[i][1] = x * x;
	}

	// printf

	printf("%-3s|%20s|%20s|%20s|\n","N", "x", "x^2", "Relation");
	
	const char* preset = "%-3d|% 20.3lf|% 20.3E|%20s|\n";
	for (int i = 0; i < m; ++i) {
		double x_One{ arrayX[i][0] }, x_Two{ arrayX[i][1] };
		if (x_Two > x_One) printf(preset, i + 1, x_One, x_Two, "More");
		else printf(preset, i + 1, x_One, x_Two, "Less");
	}

	cout << endl << endl;

	// endl

	cout << "N"; 
	cout << setw(3) << '|';
	cout << setw(21) << "x|"; 
	cout << setw(21) << "x^2|"; 
	cout << setw(21) << "Relation|\n";
	cout << setprecision(3);

	for (int i = 0; i < m; ++i) {
		double x_One{ arrayX[i][0] }, x_Two{ arrayX[i][1] };
		cout << setw(3) << left << i+1;
		cout << '|' << right;
		cout << setw(20) << fixed << x_One << '|';
		cout << setw(20) << scientific << x_Two << '|';
		cout << setw(20);
		if (x_Two > x_One) cout << "More|";
		else cout << "Less|";
		cout << endl;

	}

}

// test1:
//5
//
//1.2
//0.6
//7.134
//1.
//0.400005

// test2:
//13
//
//1
//2
//3
//.54343
//-.41235
//0.5231
//0.
//1242.3
//123.
//530512.1
//5.
//-71.
//0