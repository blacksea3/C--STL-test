#pragma once
#include "global.h"

class mStack2
{
	typedef unsigned long Item;
private:
	enum {MAX = 10};
	Item* pitems;
	int size;
	int top;
public:
	mStack2(int n = MAX);
	mStack2(const mStack2& mst);
	~mStack2();
	bool isempty() const;
	bool isfull() const;
	bool push(const Item& item);
	bool pop(Item& item);
	mStack2& operator=(const mStack2& mst);
};

void mStackClasstest();
