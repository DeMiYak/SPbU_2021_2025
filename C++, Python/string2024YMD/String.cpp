#include "String.h"

String::operator char* ()
{
	char* temp = new char[n + 1];
	strcpy(temp, str);
	return temp;
}

char String::operator[](int index) const
{
	if(index >= 0 && index < n)
		return this->str[index];
	exit(2);
}

char& String::operator[](int index)
{
	if(index >= 0 && index < n)
		return this->str[index];
	exit(3);
}

void String::swap(String& S) noexcept
{
	std::swap(str, S.str);
	std::swap(n, S.n);
}

String::String(int nstr) : n(nstr), str(new char [nstr+1])
{
	for (int i = 0; i < n; i++) str[i] = '0';
	str[n] = '\0';
}

String::String(const char* s) : n(strlen(s))
{
	str = new char[n+1];
	strcpy(str, s);
}

String::String(const String& S) : n(S.n), str(new char[S.n+1])
{
	strcpy(str, S.str);
}

String::String(String&& S) : String()
{
	swap(S);
}

String::~String()
{
	n = 0;
	delete[] str;
	str = nullptr;
}

String& String::operator=(String S)
{
	swap(S);
	return *this;
}

//String& String::operator=(const String& S)
//{
//	if (this != &S) // проверка на присвоение самому себе
//	{
//		delete[] str;
//		n = S.n;
//		if (n) {
//			str = new char[n+1];
//			strcpy(str, S.str);
//			str[n] = '\0';
//		}
//		else str = nullptr;
//	}
//	return *this;
//}
//
//String& String::operator=(String&& S)
//{
//	if (this != &S) {
//		this->~String();
//		swap(S);
//	}
//	return *this;
//}

String& String::operator+=(const String& S)
{
	int nn = n + S.n;
	char* temp = new char[nn+1];
	strncpy(temp, str, n);
	strncpy(temp + n, S.str, S.n);
	temp[nn] = '\0';
	delete[] str;
	str = move(temp);
	n = nn;
	return *this;
}

String String::operator()(int i, int j)
{
	if(i >= 0 && j < n){
		int k = abs(j - i) + 1;
		char* ptr = str + i, *temp = new char[k+1];
		strncpy(temp, ptr, k);
		if (j < i) {
			for (int m = 0; m < k; m++) {
				// cout << ptr[-m] << ' ' << int(ptr[-m]) << endl;
				temp[m] = ptr[-m];
			}
		}
		temp[k] = '\0';
		return String(temp);
	}
	exit(1);
}

bool operator==(const String& S1, const String& S2)
{
	return !S1.IsEqual(S2);
}

bool operator<(const String& S1, const String& S2)
{
	return S1.IsLessThan(S2) && S1.IsEqual(S2);
}

bool operator>(const String& S1, const String& S2)
{
	return !S1.IsLessThan(S2);
}

bool operator<=(const String& S1, const String& S2)
{
	return S1.IsLessThan(S2);
}

bool operator>=(const String& S1, const String& S2)
{
	return !S1.IsLessThan(S2) || !S1.IsEqual(S2);
}

bool operator!=(const String& S1, const String& S2)
{
	return S1.IsEqual(S2);
}

String operator+(const String& S1, const String& S2)
{
	String A(S1);
	return A += S2;
}

ostream& operator<<(ostream& out, const String& S1)
{
	if(S1.n) out << S1.str << endl << endl;
	// out << S1.n << endl << endl;
	return out;
}

istream& operator>>(istream& in, String& S1)
{
	char* temp = new char[1024];
	in.getline(temp, 1024);
	if(S1.n) delete[] S1.str;
	S1.n = strlen(temp);
	S1.str = new char[S1.n+1];
	strncpy(S1.str, temp, S1.n);
	S1.str[S1.n] = '\0';
	return in;

}
