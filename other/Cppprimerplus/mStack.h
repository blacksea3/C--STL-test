#pragma once

#include "global.h"

namespace CPP_PRACTICE_CHAPTER9
{
	struct customer
	{
		char fullname[35];
		double payment;
		customer()  //Ĭ�Ϲ��캯��
		{
			fullname[0] = '\n';
			payment = 0.0;
		}
		customer(const char* inputname, double inputpayment)
		{
			size_t firstNameLength = strnlen_s(inputname, 35);
			if (firstNameLength == 35) //ǿ�ƽض�
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
		bool push(const Item & item);   //�ٶ�ʹ���ߵ�customer��payment��>0
		double pop(Item & item);   //��ɾ���ɹ������ۻ�����ǰ��payment��, ���ɹ�����-1.0
	};
}

void mStackClassTest();
