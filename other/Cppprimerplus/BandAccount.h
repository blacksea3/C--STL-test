#pragma once
#include "global.h"

/*
 * “¯––’À∫≈
 */
class BandAccount
{
private:
	string name;
	string account;
	int saving;
public:
	BandAccount(string name, string account, int saving);
	~BandAccount();
	void displayAll();
	int depositMoney(int money);
	int drawMoney(int money);
};

void BandAccountClassTest();
