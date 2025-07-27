#include"Employee.h"
void From_File(const char* fname, PERSONNEL* l, int* pn) {
	FILE* fFrom = fopen(fname, "r");
	if (!fFrom) {
		std::cout << "No such file.";
		exit(1);
	}
	fread(pn, sizeof(int), 1, fFrom);
	fread(l, sizeof(PERSONNEL), *pn, fFrom);
	fclose(fFrom);
}

void In_File(const char* fname, PERSONNEL* l, int n) {
	FILE* fIn = fopen(fname, "r");
	if (!fIn) {
		std::cout << "No such file.";
		exit(1);
	}
	fclose(fIn);
	fIn = fopen(fname, "w");
	fwrite(&n, sizeof(int), 1, fIn);
	fwrite(l, sizeof(PERSONNEL), n, fIn);
	fclose(fIn);
}

void Double_Sort(PERSONNEL** pl, int n, int(*comparePer)(const void*, const void*), int(*compareEmp)(const void*, const void*)) {
	std::qsort(pl, n, sizeof(PERSONNEL*), comparePer);

	for (int i = 0; i < n; ++i) {
		int count = 0;
		while (count < NEMPL && pl[i]->EmpList[count].surname[0] != '\0')
			++count;
		std::qsort(pl[i]->EmpList, count, sizeof(EMPLOYEE), compareEmp);
	}
}


int cmp_NumDept(const void* pOne, const void* pTwo) 
{
	const PERSONNEL** tOne = (const PERSONNEL**)pOne;
	const PERSONNEL** tTwo = (const PERSONNEL**)pTwo;
	if ((*tOne)->NumDept > (*tTwo)->NumDept) return 1;
	if ((*tOne)->NumDept == (*tTwo)->NumDept) return 0;
	return -1;
}

int cmp_Surname(const void* pOne, const void* pTwo) 
{
	const EMPLOYEE* tOne = (EMPLOYEE*)pOne;
	const EMPLOYEE* tTwo = (EMPLOYEE*)pTwo;
	return strcmp(tOne->surname, tTwo->surname);
}

PERSONNEL* Search_By_Dept(const PERSONNEL* dept, PERSONNEL** pl, int n, int(*comparePer)(const void*, const void*)){
	const PERSONNEL** p{&dept};
	for (int i = 0; i < n; ++i) {
		if (!comparePer(p, pl+i)) return pl[i];
	}
	return nullptr;
}

void Print(PERSONNEL** l, int n)
{
	printf("%-10s|%12s|%12s|%12s|\n", "Department", "Surname", "Position", "Salary (Rub)");
	for (int i = 0; i < n; ++i) {
		Print_Dept(*l[i]);
	}
	std::cout << std::endl;
}

void Print_Dept(const PERSONNEL& l)
{
	if (!&l) { std::cout << "Have not found department"; return; }
	for (int i = 0; i < NPERS; ++i) {
		if (l.EmpList[i].surname[0] == '\0') break;
		printf("%-10d|", l.NumDept);
		Print_Employee(l.EmpList[i]);
	}
}

void Print_Employee(const EMPLOYEE& emp) {
	printf("%12s|%12s|%12d|\n", emp.surname, emp.position, emp.salary);
}