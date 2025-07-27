#include"Forfeit.h"
void CreateFile(const char* fileName, int dataCount, double* array) {
	/*std::mt19937 gen(time(0));
	std::uniform_real_distribution<> dobble(-100, 100);*/
	FILE* file = fopen(fileName, "wb");
	for (int i = 0; i < dataCount; ++i) {
		fwrite(&array[i], sizeof(double), 1, file);
	}
	fclose(file);
}

void ReadFile(const char* fileName, int dataCount, double* array)
{
	FILE* file = fopen(fileName, "rb");
	fread(array, sizeof(double), dataCount, file);
	fclose(file);
}

bool ChangeByCriteria(FILE* file, bool (*cmpFunc)(const double& num), void(*cngFunc)(double& num))
{
	double num;
	while (!feof(file)) {
		fread(&num, sizeof(double), 1, file);
		if (cmpFunc(num)) {
			cngFunc(num);
			fseek(file, -1*sizeof(double), SEEK_CUR);
			fwrite(&num, sizeof(double), 1, file);
			return true;
		}
	}
	return false;
}

bool GTZero(const double& num) { return num > 0; }
bool LTZero(const double& num) { return num < 0; }

void MakeSquare(double& num) { num *= num; }
void ChangeSign(double& num) { num = -num; }

///
/// cell_is_filled()
/// cell_is_clear()
/// cell_fill()
/// move_up()
/// free_from_up()
/// wall_from_up()
/// 
/// def fill_plain(){
/// 
/// }
/// 