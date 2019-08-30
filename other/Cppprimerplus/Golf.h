#pragma once
#include "global.h"

class Golf
{
private:
	static const int Len = 40;
	char fullname[Len];
	int handicap;
public:
	Golf(const char* name, int hc);
	Golf() { fullname[0] = '\0'; handicap = 0; }
	//Golf(const Golf& initGolf);
	void setgolf();
	void sethandicap(int hc);
	void showgolf() const;
	~Golf();
};

void GolfClassTest();
