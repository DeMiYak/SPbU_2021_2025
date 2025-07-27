#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<iostream>

using namespace std;

class String
{
	char* str;
	int n;
	int IsEqual(const String& S) const
	{
		return strcmp(str, S.str);
	}
	int IsLessThan(const String& S) const
	{
		return(strcmp(str, S.str) <= 0);
	}
public:
	String() : str(nullptr), n(0) {};
	
	void swap(String& s) noexcept;
	explicit String(int nstr);
	String(const char* s);
	String(const String& S);
	String(String&& S);
	~String();
	String& operator = (String S);
	// String& operator = (const String& S);
	// String& operator = (String&& S);
	String& operator += (const String& S);
	String operator () (int i, int j);
	operator char* ();
	friend bool operator == (const String& S1, const String& S2);
	friend bool operator < (const String& S1, const String& S2);
	friend bool operator > (const String& S1, const String& S2);
	friend bool operator <= (const String& S1, const String& S2);
	friend bool operator >= (const String& S1, const String& S2);
	friend bool operator != (const String& S1, const String& S2);
	friend String operator + (const String& S1, const String& S2);
	friend ostream& operator << (ostream& out, const String& S1);
	friend istream& operator >> (istream& in, String& S1);

	char operator [](int index) const;
	char& operator [](int index);
};