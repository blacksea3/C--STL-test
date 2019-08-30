#pragma once
#include "global.h"

class Person
{
private:
	static const int LIMIT = 25;
	string lname;   //firstname
	char fname[LIMIT]; //lastname
public:
	Person() { lname = ""; fname[0] = '\0'; }
	Person(const string &ln, const char* fn = "heyyou");
	void Show() const;
	void FormalShow() const;
	~Person();
};

void PersonClassTest();
