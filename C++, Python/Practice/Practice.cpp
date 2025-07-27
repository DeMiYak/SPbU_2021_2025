#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <optional>

//const int NMARK = 5;
//const int NSIMB = 10;
//const int NSTUDENT = 100;
//
//struct STUDENT {
//	char name[NSIMB];
//	int mark[NMARK];
//	float avr;
//};

//int cmp_name(const void* stOne, const void* stTwo);

//int cmp_name(const STUDENT& stOne, const STUDENT& stTwo);
//
//void mysort(STUDENT* l, int n, int (*compare)(const STUDENT&, const STUDENT&));

int main()
{
	STUDENT stud[NSTUDENT] = {
		{"James", {1,1,2,3,3}},
		{"Jeremiah", {5,5,4,4,5}},
		{"Anthony", {2,2,3,4,4}}
	};
	size_t size = sizeof(stud) / sizeof(STUDENT);
	std::qsort((STUDENT*)stud, size, sizeof(STUDENT), cmp_name);
	//int(*compare)(const STUDENT&, const STUDENT&) = cmp_name;
	/*mysort(stud, size, compare);*/
	STUDENT** studptr = new STUDENT*[NSTUDENT];
	for (size_t i = 0; i < size; ++i) {
		*studptr = new STUDENT;
		(*studptr++) = &stud[i];
	}
	for (size_t i = 0; i < size; ++i) std::cout << stud[i].name << std::endl;
	for (size_t i = 0; i < size; ++i) std::cout << (*studptr++)->name << std::endl;
	return 0;
}

int cmp_name(const void* stOne, const void* stTwo) {
	STUDENT* s1 = (STUDENT*)stOne;
	STUDENT* s2 = (STUDENT*)stTwo;
	return strcmp(s1->name, s2->name);
}

//int cmp_name(const STUDENT& stOne, const STUDENT& stTwo) {
//	return strcmp(stOne.name, stTwo.name);
//}
//
//void mysort(STUDENT* l, int n, int (*compare)(const STUDENT&, const STUDENT&)) {
//	for (int i = 0; i < n; ++i) {
//		for (int j = i + 1; j < n; ++j) {
//			if (compare(l[j-1], l[j]) == 1) {
//				STUDENT& temp = l[i];
//				l[i] = l[j];
//				l[j] = temp;
//			}
//
//		}
//	}
//}

//int f(int i, ...) {
//	int s = 0;
//	int* ptr = &i;
//	while (i--) {
//		std::cout << *ptr << ' ';
//		s += *ptr;
//		++ptr;
//	}
//	std::cout << std::endl;
//	return s;
//}

//if (auto x = sqrt_opt(2.)) std::cout << x.value() << std::endl; else std::cout << "not ok\n";
//if (std::optional<double> x = sqrt_opt(4.)) std::cout << *x << std::endl; else std::cout << "not ok\n";
//if (auto x = sqrt_opt(-4.)) std::cout << x.value() << std::endl; else std::cout << "not ok\n";

//int res1 = f(0);
//int res2 = f(5, 1, 2, 3, 4, 10);
//std::cout << std::endl << res1 << ' ' << res2; 


/*int s = 0;
	for (int j = 0; j < i; ++j) {
		s += ;
}*/

//char str[100] = "(    2.231,			32.1230,1., 8, 0.1  )";
//char* strPtr;
//
//for (strPtr = str; (strPtr = strpbrk(strPtr,"0123456789"));) {
//	std::cout << strtod(strPtr, &strPtr) << std::endl;
//}

//FILE* fileRead = fopen("Practice.vcxproj.filters", "r");
//FILE* fileWrite = fopen("PracticeWrite.txt", "w");
//char c = fgetc(fileRead);
//fputc(c, fileWrite);
//while ((c = fgetc(fileRead)) != EOF) {
//	fputc(c, fileWrite);
//}
//
//fclose(fileRead);
//fclose(fileWrite);*/

	//FILE* fileRead = fopen("Practice.vcxproj", "r");
	//FILE* fileWrite = fopen("PraciceWrite.txt", "w");
	//char buffer[BUFFER_SIZE];

	//while(fgets(buffer, BUFFER_SIZE, fileRead)) fputs(buffer, fileWrite);

	//fclose(fileRead);
	//fclose(fileWrite);

	//FILE* fileRead = fopen("x64/Debug/Practice.exe", "rb");
	//FILE* fileWrite = fopen("Practice3.txt", "wb");
	//buffer_type buffer[BUFFER_SIZE];

	//while (!feof(fileRead)) {
	//	fread(buffer, sizeof(buffer_type), BUFFER_SIZE, fileRead);
	//	fwrite(buffer, sizeof(buffer_type), BUFFER_SIZE, fileWrite);
	//}

	//fclose(fileRead);
	// 	//fclose(fileWrite);
//
//struct A {
//	int m[10];
//};
//struct B {
//	A a[20];
//};
//struct C {
//	B b[30];
//};
//
//C c;
//c.b[15].a[10].m[2] = 3;
//std::cout << *(((c.b + 15)->a + 10)->m + 2) << std::endl;
//
//struct D {
//	char c;
//	long long i;
//	char k;
//};
//D d;
//std::cout << sizeof(D);

//
//const int BUFFER_SIZE = 20;
//
//using buffer_type = char;
//
//int f(int i, ...);
//
//template<typename T>
//T max(T i, T j) {
//	if (i >= j) return i;
//	return j;
//}
//
//std::optional<double> sqrt_opt(double x) {
//	if (x < 0) return std::nullopt;
//	return sqrt(x);
//}