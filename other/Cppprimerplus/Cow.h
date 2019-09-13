#pragma once
#include "global.h"

class Cow
{
private:
	char name[20];
	char* hobby;
	double weight;
public:
	Cow();
	Cow(const char* nm, const char* ho, double wt);
	Cow(const Cow& c);
	~Cow();
	Cow & operator=(const Cow& c);
	void ShowCow() const;
};

void callme1(Cow& c);   //pass by reference
void callme2(Cow c);    //pass by value
void CowClassTest();
