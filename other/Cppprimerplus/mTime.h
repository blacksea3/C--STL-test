#pragma once
#include "global.h"

//ʱ����
//ע��: ������Сʱ�ͷ���, 24Сʱ��
class mTime
{
private:
	int hours;
	int minutes;
public:
	mTime();
	mTime(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h = 0, int m = 0);
	friend mTime operator+(const mTime& t1, const mTime& t2);
	friend mTime operator-(const mTime& t1, const mTime& t2);
	friend mTime operator*(const mTime& t, double n);
	friend mTime operator*(double n, const mTime& t);
	friend std::ostream & operator<<(std::ostream& os, const mTime& t);
	~mTime();
};

void mTimeClassTest();
