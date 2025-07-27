#include "String.h"

void String::swap(String& other) noexcept
{
	std::swap(str, other.str);
	std::swap(len, other.len);
}

String::String(): str(nullptr), len(0) 
{}

String::String(int nstr) : len(nstr)
{
	str = new char[len + 1];
	str[len] = '\0';
}

String::String(const char* s): len(strlen(s))
{
	str = new char[len + 1];
	strcpy(str, s);
}

String::String(const String& s): len(s.len)
{
	str = new char[len + 1];
	strcpy(str, s.str);
}

String::String(String&& s) noexcept: String()
{
	this->swap(s);
}

//String::String(String&& s) noexcept
//{
//	str = s.str;
//	len = s.len;
//	s.str = nullptr;
//	s.len = 0;
//}


String::~String()
{
	len = 0;
	delete[] str;
	str = nullptr;
}


//String& String::operator= (const String& s)
//{
//	if (this != &s)
//	{
//		delete[] str;
//		len = s.len;
//		if (len)
//		{
//			str = new char[len + 1];
//			strcpy(str, s.str);
//		}
//		else this->str = nullptr;
//	}
//	return *this;
//}


//String& String::operator= (String&& s) noexcept
//{
//	if (this != &s)
//	{
//		this->~String();
//		this->swap(s);
//	}
//	return *this;
//}


String& String::operator= (String s)
{
	this->swap(s);
	return *this;
}


String& String::operator+= (const String& s)
{
	int newLen = len + s.len;

	char* newStr = new char[newLen + 1];

	strncpy(newStr, str, len);
	strncpy(newStr + len, s.str, s.len);
	newStr[newLen] = '\0';
	delete[] str;
	str = newStr;
	len = newLen;
	return *this;
}

String String::operator() (int i, int j)
{
	String s;
	if (i < 0 || i >= len || j < 0 || i > j || !len)
		return s;

	s.len = std::min(j - i + 1, len - i);
	s.str = new char[s.len + 1];
	memcpy(s.str, str + i, s.len);
	s.str[s.len] = '\0';
	return s;
}

String::operator char* ()
{
	return str;
}

bool operator == (const String& s1, const String& s2)
{
	return s1.IsEqual(s2);
}

bool operator != (const String& s1, const String& s2)
{
	return !s1.IsEqual(s2);
}

bool operator< (const String& s1, const String& s2)
{
	return s1.IsLessThan(s2);
}

bool operator >= (const String& s1, const String& s2)
{
	return !s1.IsLessThan(s2);
}

bool operator > (const String& s1, const String& s2)
{
	return !s1.IsLessThan(s2) && !s1.IsEqual(s2);
}

bool operator <= (const String& s1, const String& s2)
{
	return s1.IsLessThan(s2) || s1.IsEqual(s2);
}

String operator+ (const String& s1, const String& s2)
{
	String result(s1);
	return result += s2;
}

ostream& operator << (ostream& out, const String& s)
{
	if (s.str != nullptr)
		out << s.str;
	return out;
}

istream& operator >> (istream& in, String& s)
{
	char buffer[bufferSize];
	in >> buffer;
	delete[] s.str;
	s.len = strlen(buffer);
	s.str = new char[s.len + 1];
	strncpy(s.str, buffer, s.len);
	s.str[s.len] = '\0';
	return in;
}

char String::operator [] (int index) const
{
	return str[index];
}

char& String::operator[] (int index)
{
	return str[index];
}

