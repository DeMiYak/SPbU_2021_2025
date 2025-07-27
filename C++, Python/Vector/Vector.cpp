#include"Array.h"
int main()
{
	array<int> a(5, 2), b(5, 3);
	
	std::cout << "\nTest 1\n";
	a = a;
	a.print();

	std::cout << "\nTest 2\n";
	(a += b).print();
	(a + b).print();
	
	std::cout << "\nTest 3\n";
	a = b;
	a.print();

	std::cout << "\nTest 4\n";
	array<int> c(b);
	c.print();
	a = array<int>(5, 8) + c;
	(a + b + c + array<int>(5, 6)).print();
	(c += b += array<int>(5, 1) + a).print();

	std::cout << "\nTest 5\n";
	array<int> d(array<int>(5, 2) + a += b + b);
	d.print();

	std::cout << "\nTest 6\n";
	(b = b += b = b + b).print();

	/*a.refill().print();*/

	std::cout << "\nTest 7\n";
	array<int> sm(3, 1);
	(sm += a += b).print();
}