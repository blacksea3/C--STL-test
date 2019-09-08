#pragma once

#include "global.h"

namespace CPP_PRACTICE_CHAPTER9
{
	typedef int ListItem;
	class mList
	{
	private:
		enum { MAX = 10 };
		ListItem items[MAX];
		int top;
		double totalPayment;
	public:
		mList();
		~mList();

		bool isempty() const;
		bool isfull() const;
		bool push_back(const ListItem & item);
		bool visit(ListItem & item, int index);
	};
}

void mListClassTest();
