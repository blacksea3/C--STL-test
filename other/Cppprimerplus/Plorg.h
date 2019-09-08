#pragma once

#include "global.h"

class Plorg
{
private:
	string name;
	int CI;
public:
	Plorg(string inputname = "Plorga");
	void setCI(int inputCI);
	void display() const;
	~Plorg();
};

void PlorgClassTest();
