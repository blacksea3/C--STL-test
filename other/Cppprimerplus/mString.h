#pragma once
#include "global.h"

class mString
{
private:
	char* str;
	size_t len;
	static int num_strings;
public:
	static const int CINLIM = 80;
public:
	mString();
	mString(const char* s);
	mString(const mString& ms);
	~mString();
	inline size_t length() const { return len; };
	mString& operator=(const mString& ms);
	mString& operator=(const char* s);
	char& operator[](size_t i);
	const char& operator[](size_t i) const;
	mString operator+(const mString& m);
	mString operator+(const char* s);
	void stringlow();
	void stringup();
	int has(char c);

	friend mString operator+(const char* s, const mString& m);
	friend bool operator<(const mString &ms, const mString& ms2);
	friend bool operator>(const mString &ms, const mString& ms2);
	friend bool operator==(const mString &ms, const mString& ms2);
	friend ostream& operator<<(ostream& os, const mString& ms);
	friend istream& operator>>(istream& is, const mString& ms);

	static int HowMany();
};

void mStringClassTest();
