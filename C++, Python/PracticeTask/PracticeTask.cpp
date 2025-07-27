#include <iostream>

//template<typename T>
//void Swap(T& a, T& b) {
//	T temp(a);
//	a = b;
//	b = temp;
//}

template<typename T>
void Swap(T& a, T& b) {
	T temp(std::move(a));
	a = std::move(b);
	b = std::move(temp);
}

int main()
{
	int a(2), b(3);
	Swap<int>(a, b);
	std::cout << a << " " << b;
	return 0;
}

