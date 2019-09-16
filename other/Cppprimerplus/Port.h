#pragma once
#include "global.h"

//Port基类
class Port
{
private:
	char* brand;
	char style[20];
	int bottles;
public:
	Port(const char* br = "none", const char* st = "none", int b = 0);
	Port(const Port& p);
	inline virtual ~Port() { delete[] brand; };
	Port& operator=(const Port& p);
	Port& operator+=(int b);
	Port& operator-=(int b);
	inline int BottleCount() const { return bottles; };
	virtual void Show() const;
	friend ostream& operator<<(ostream& os, const Port& p);
};

//VintagePort派生至Port
class VintagePort : public Port
{
private:
	char* nickname;
	int year;
public:
	VintagePort();
	VintagePort(const char* br, int b, const char* nn, int y);
	VintagePort(const VintagePort& vp);
	inline virtual ~VintagePort() { delete[] nickname; };
	VintagePort& operator=(const VintagePort& vp);
	virtual void Show() const;
	friend ostream& operator<<(ostream& os, const VintagePort& p);
 };

void PortClassTest();
