#include "mStack.h"

using namespace CPP_PRACTICE_CHAPTER9;

mStack::mStack()
{
	top = 0;
	totalPayment = 0.0;
}


mStack::~mStack()
{
}

bool mStack::isempty() const
{
	return top == 0;
}

bool mStack::isfull() const
{
	return top == MAX;
}

bool mStack::push(const Item & item)
{
	if (top < MAX)
	{
		items[top++] = item;
		return true;
	}
	else
	{
		return false;
	}
}

double mStack::pop(Item & item)
{
	if (top > 0)
	{
		item = items[--top];
		totalPayment += item.payment;
		return totalPayment;
	}
	else
	{
		return -1.0;
	}
}

void mStackClassTest()
{
	vector<customer> v(5);
	
	for (int index = 0; index < 5; ++index)
	{
		string tempn = "person" + to_string(index);
		customer tempc = customer(tempn.c_str(), (double)index + 1.0);
		v[index] = tempc;
	}
	customer para = customer();
	mStack ms = mStack();
	cout << ms.push(v[0]) << endl;
	cout << ms.push(v[1]) << endl;
	cout << ms.pop(para) << endl;
	cout << ms.pop(para) << endl;
	cout << ms.pop(para) << endl;
	cout << ms.push(v[2]) << endl;
	cout << ms.push(v[3]) << endl;
	cout << ms.push(v[4]) << endl;
	cout << ms.pop(para) << endl;
	cout << ms.pop(para) << endl;
	cout << ms.pop(para) << endl;
}

