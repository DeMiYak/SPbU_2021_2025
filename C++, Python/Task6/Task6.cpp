#define _CRT_SECURE_NO_WARNINGS
#include"replace.h"
int main()
{
	char* charLine_One = new char[BUFFER_SIZE];
	char* charLine_Two = new char[BUFFER_SIZE];
	int replace = 0;

	std::cin.getline(charLine_One, BUFFER_SIZE - 1);
	strcpy(charLine_Two, charLine_One);

	std::cout << "String before *-replacement:\n" << charLine_One << std::endl;

	// 6.1.

	// 6.1.1.

	starReplace(charLine_One, replace);

	std::cout << "String after *-replacement:\n" << charLine_One << "\nTotal *-replaces: " << replace << std::endl;

	replace = 0;

	// 6.1.2.

	std::cout << "String before *-replacement:\n" << charLine_Two << std::endl;

	starReplace_Two(charLine_Two, replace);

	std::cout << "String after *-replacement:\n" << charLine_Two << "\nTotal *-replaces: " << replace << std::endl;

	// 6.2.
}

// Задача 6. замените все символы, не являющиеся буквами на "*".
// Запишите число замен.