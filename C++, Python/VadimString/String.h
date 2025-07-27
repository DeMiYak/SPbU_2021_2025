#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>
using namespace std;

const int bufferSize = 256;

class String
{
	char* str;
	int len;
	int IsEqual(const String& S) const
	{
		return strcmp(str, S.str);
	}
	int IsLessThan(const String& S) const
	{
		return (strcmp(str, S.str) <= 0);
	}
	void swap(String& other) noexcept;

public:
	String();
	explicit String(int nstr);
	String(const char* s);
	String(const String& s);
	String(String&& S) noexcept;
	~String();
	//String& operator= (const String& s);
	//String& operator= (String&& s) noexcept;
	String& operator= (String s);
	String& operator+= (const String& s); 
	String operator() (int i, int j); //возвращает подстроку
	operator char* (); //оператор преобразования типа String к char*
	friend bool operator == (const String& s1, const String& s2);
	friend bool operator < (const String& s1, const String& s2);
	friend bool operator != (const String& s1, const String& s2);
	friend bool operator > (const String& s1, const String& s2);
	friend bool operator <= (const String& s1, const String& s2);
	friend bool operator >= (const String& s1, const String& s2);
	friend String operator + (const String& s1, const String& s2);
	friend ostream& operator << (ostream& out, const String& s);
	friend istream& operator >> (istream& in, String& s);

	char operator [] (int index) const;
	char& operator[] (int index);

};
