#include "mList.h"

using namespace CPP_PRACTICE_CHAPTER9;

mList::mList()
{
	top = 0;
}


mList::~mList()
{
}

bool CPP_PRACTICE_CHAPTER9::mList::isempty() const
{
	return top == 0;
}

bool CPP_PRACTICE_CHAPTER9::mList::isfull() const
{
	return top == MAX;
}

bool CPP_PRACTICE_CHAPTER9::mList::push_back(const ListItem & item)
{
	if (top < MAX)
	{
		this->items[top++] = item;
		return true;
	}
	else return false;
}

bool CPP_PRACTICE_CHAPTER9::mList::visit(ListItem &item, int index)
{
	if (index < 0 || index >= top)
	{
		return false;
	}
	else
	{
		item = this->items[index];
		return true;
	}
}

void mListClassTest()
{
	mList ml = mList();
	cout << ml.isempty() << endl;
	ml.push_back(2);
	cout << ml.isempty() << endl;
	cout << ml.isfull() << endl;
	cout << ml.push_back(3) << endl;
	cout << ml.push_back(4) << endl;
	cout << ml.push_back(5) << endl;
	cout << ml.push_back(6) << endl;
	cout << ml.push_back(7) << endl;
	cout << ml.push_back(8) << endl;
	cout << ml.push_back(9) << endl;
	cout << ml.push_back(10) << endl;
	cout << ml.push_back(11) << endl;
	cout << ml.push_back(12) << endl;
	ListItem li1;
	cout << ml.visit(li1, -1) << endl;
	cout << ml.visit(li1, 2) << endl;
	cout << li1 << endl;
}
