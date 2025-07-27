// Две структуры:
// + 1) Фамилия, должность, зарплата
// + 2) Номер отдела и массив из 1)
// Действия:
// + ввод из файла неупорядоченного списка из 2) структур
// + двойное упорядочивание по номеру отдела и по фамилии
// + поиск по номеру отдела
// + вывод на экран упорядоченного списка
// Как:
// + библиотечная функция сортировки по зад. критерию с использованием указателя на функцию сравнения;
// - сортировка структур по указателям.
// + свой последовательный поиск 
#include"Employee.h"

int main()
{
	int numDept = 4;
	PERSONNEL list[NPERS] = {
	{404, {
		{"Santa", "Engineer", 20000}
		}
	},
	{403, 
		{
		{"Jane", "Fireworker", 15000},
		{"Stephany", "Clerk", 16000}
		}
	},
	{402, 
		{
		{"Daniel", "PR-manager", 30000},
		{"Perry", "Clerk", 16000},
		{"Arthur", "Chairman", 50000}
		}
	},
	{401, 
		{
		{"Jim", "Mechanic", 19000},
		{"Santa", "Engineer", 20000},
		{"Bill", "Stapler", 18000},
		{"Michael", "Janitor", 12500},
		}
	},
	};
	PERSONNEL* plist[NPERS];
	for (int i = 0; i < numDept; ++i) {
		plist[i] = &list[i];
	}

	In_File("Data.txt", list, numDept);
	From_File("Data.txt", list, &numDept);
	std::cout << "Unsorted print:\n";
	Print(plist, numDept);

	std::cout << "Sorted print:\n";
	Double_Sort(plist, numDept, cmp_NumDept, cmp_Surname);
	Print(plist, numDept);

	PERSONNEL dep402 = {
		402,
		{
		{"Daniel", "PR-manager", 30000},
		{"Perry", "Clerk", 16000},
		{"Arthur", "Chairman", 50000},
		}
	},
	dep407 = {
		407,
		{
		{"Arthur", "Chairman", 50000},
		}
	};

	std::cout << "Search:\n";
	std::cout << "Existing department:\n";
	PERSONNEL* sample = Search_By_Dept(&dep402, plist, numDept, cmp_NumDept);
	Print_Dept(*sample);
	std::cout << "\nNon-existing department:\n";
	sample = Search_By_Dept(&dep407, plist, numDept, cmp_NumDept);
	Print_Dept(*sample);
	std::cout << std::endl;
	
}