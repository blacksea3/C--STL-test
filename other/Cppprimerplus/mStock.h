#pragma once
#include "global.h"

class mStock
{
private:
	static const size_t MAXSTRLEN = 20;
	char* company;
	int shares;
	double share_val;
	double total_val;
	void set_tot() { total_val = shares * share_val; };
public:
	mStock();
	mStock(const mStock& ms);
	mStock(const char* co, long n = 0, double pr = 0.0);
	mStock& operator=(const mStock& ms);
	~mStock();

	void buy(long num, double price);
	void sell(long num, double price);
	void update(double price);
	friend ostream& operator<<(ostream& os, const mStock& ms);
	const mStock& topval(const mStock& s) const;
};

void mStockClassTest();
