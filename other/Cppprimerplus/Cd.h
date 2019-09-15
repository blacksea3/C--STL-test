#pragma once
#include "global.h"

//基类, 表示CD光盘
class Cd
{
private:
	char* performers;
	char* label;
	int selections;
	double playtime;
public:
	Cd(const char* s1, const char* s2, int n, double x);
	Cd(const Cd& d);
	Cd();
	virtual ~Cd();
	virtual void Report() const;
	Cd& operator=(const Cd& d);
};


//典型Cd
class Classic : public Cd
{
private:
	char* mainWork;
public:
	Classic();
	Classic(const char* s1, const char* s2, const char* s3, int n, double x);
	Classic(const Classic& d);
	virtual void Report() const;
	virtual ~Classic();
	Classic& operator=(const Classic& d);
};

void CdClassTest();
