// Hometask2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include"hometask2.h"


int main()
{

    setlocale(LC_ALL, "Russian");
    cout << "Enter * as a line to stop." << endl;
    size_t capacity = CAPDEFAULT;
    size_t size = 0;
    char** charArray;
    initCharArray(charArray, capacity);
    fillCharArray(charArray, size, capacity);
    cout << "\n\n" << "Resulting line array:" << endl;
    printCharArray(charArray, size);
    deleteCharArray(charArray, size);
}

void initCharArray(char** &array, const size_t& capacity) {
	array = new char* [capacity];
}

void increaseCapacity(size_t& capacity) { capacity *= 2; }

void resizeCharArrayAtCap(char** &array, const size_t& size, size_t& capacity) {
	increaseCapacity(capacity);
	char** temp = new char* [capacity];
	for (size_t i = 0; i < size; temp[i] = array[i], ++i);
	array = temp;
}

void fillCharArray(char** &array, size_t& size, size_t& capacity) {
	char* word = new char[BUFFER_SIZE];
	size_t tempSize = 0;
	cin.getline(word, BUFFER_SIZE);
	while (*word != '*' || *(word + 1)) {
		array[tempSize++] = word;

		if (tempSize == capacity) resizeCharArrayAtCap(array, tempSize, capacity);
		word = new char[BUFFER_SIZE];
		cin.getline(word, BUFFER_SIZE);
	}
	size = tempSize;
}

void printCharArray(char** array, const size_t& size) {
	for (size_t i = 0; i < size; ++i)
		cout << array[i] << '\n';
}

void deleteCharArray(char** array, const size_t& size) {
	for (size_t i = 0; i < size; delete[] array[i++]);
	delete[] array;
}


// задача: ввод с клавиатуры неизвестного числа строк с символом-терминатором.
// необходимо, чтобы получился массив строк char**
//по поводу этой программы(и прошлой) :
//    В файле h вы только прототипы делаете, а реализации функций — в файле cpp, который включаете в проект.
//
//    Никаких malloc - calloc
//
//    Не поняла сложности с вводом строки.Там или gets(...) или cin.getline(...);
//
//Из каких соображений ставите - не ставите & в параметрах char**& array ?
//
//НЭ