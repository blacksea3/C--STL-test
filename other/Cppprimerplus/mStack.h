#pragma once

#include "global.h"

namespace CPP_PRACTICE_CHAPTER9
{
	struct customer
	{
		char fullname[35];
		double payment;
		customer()  //默认构造函数
		{
			fullname[0] = '\n';
			payment = 0.0;
		}
		customer(const char* inputname, double inputpayment)
		{
			size_t firstNameLength = strnlen_s(inputname, 35);
			if (firstNameLength == 35) //强制截断
			{
				this->fullname[34] = '\n';
				strncpy_s(this->fullname, inputname, 34);
			}
			else
			{
				strncpy_s(this->fullname, inputname, 34);
			}
			this->payment = inputpayment;
		}
	};

	typedef customer Item;

	class mStack
	{
	private:
		enum { MAX = 10 };
		Item items[MAX];
		int top;
		double totalPayment;
	public:
		mStack();
		~mStack();

		bool isempty() const;
		bool isfull() const;
		bool push(const Item & item);   //假定使用者的customer的payment总>0
		double pop(Item & item);   //若删除成功返回累积到当前的payment和, 不成功返回-1.0
	};
}

void mStackClassTest();
