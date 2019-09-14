#include "mStack2.h"

mStack2::mStack2(int n)
{
	if (n > MAX || n < 1)
	{
		cout << "n not valid, aborted" << endl;
		cout << "I will set n = 10" << endl;
		n = 10;
	}
	pitems = new Item[n];
	top = 0;
	size = n;
}

mStack2::mStack2(const mStack2 & mst)
{
	size = mst.size;
	pitems = new Item[size];
	
	//copy data from mst
	top = mst.top;
	for (int index = 0; index < top; ++index)
	{
		pitems[index] = mst.pitems[index];
	}
}

mStack2::~mStack2()
{
}

bool mStack2::isempty() const
{
	return top == 0;
}

bool mStack2::isfull() const
{
	return top == size;
}

bool mStack2::push(const Item & item)
{
	if (top < size)
	{
		pitems[top++] = item;
		return true;
	}
	else
	{
		return false;
	}
}

bool mStack2::pop(Item & item)
{
	if (top > 0)
	{
		item = pitems[--top];
		return true;
	}
	else
	{
		return false;
	}
}

mStack2 & mStack2::operator=(const mStack2 & mst)
{
	if (&mst == this)
	{
		return *this;
	}
	else
	{
		delete[] pitems;
		size = mst.size;
		pitems = new Item[size];

		//copy data from mst
		top = mst.top;
		for (int index = 0; index < top; ++index)
		{
			pitems[index] = mst.pitems[index];
		}
		return *this;
	}
}

void mStackClasstest()
{
	mStack2 ms1(2);
	cout << ms1.push(100) << endl;
	cout << ms1.push(200) << endl;
	cout << ms1.push(300) << endl;

	cout << "mStack2 ms2(ms1)" << endl;
	mStack2 ms2(ms1);
	unsigned long u11;
	cout << ms2.pop(u11) << endl;
	cout << u11 << endl;
	unsigned long u21;
	cout << ms2.pop(u21) << endl;
	cout << u21 << endl;
	unsigned long u31;
	cout << ms2.pop(u31) << endl;
	cout << u31 << endl;

	cout << "mStack2 ms3 = ms1" << endl;
	mStack2 ms3 = ms1;
	unsigned long u12;
	cout << ms3.pop(u12) << endl;
	cout << u12 << endl;
	unsigned long u22;
	cout << ms3.pop(u22) << endl;
	cout << u22 << endl;
	unsigned long u32;
	cout << ms3.pop(u32) << endl;
	cout << u32 << endl;

	cout << "mStack2 ms4; ms4 = ms1" << endl;
	mStack2 ms4;
	ms4 = ms1;
	unsigned long u13;
	cout << ms4.pop(u13) << endl;
	cout << u13 << endl;
	unsigned long u23;
	cout << ms4.pop(u23) << endl;
	cout << u23 << endl;
	unsigned long u33;
	cout << ms4.pop(u33) << endl;
	cout << u33 << endl;
}
