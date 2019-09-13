#include "mTime.h"

mTime::mTime()
{
	this->hours = 0;
	this->minutes = 0;
}

mTime::mTime(int h, int m)
{
	this->hours = (h + m/60)%24;
	this->minutes = m % 60;
}

void mTime::AddMin(int m)
{
	this->minutes = (this->minutes + m) % 60;
	this->hours = (this->hours + (m / 60))%24;
}

void mTime::AddHr(int h)
{
	this->hours = (this->hours + h)%24;
}

void mTime::Reset(int h, int m)
{
	this->hours = (h + m / 60) % 24;
	this->minutes = m % 60;
}


mTime::~mTime()
{
}

mTime operator+(const mTime & t1, const mTime & t2)
{
	return mTime((t1.hours + t2.hours + (t1.minutes + t2.minutes)/60)%24, (t1.minutes + t2.minutes)%60);
}

mTime operator-(const mTime & t1, const mTime & t2)
{
	return mTime((t1.hours - t2.hours + (t1.minutes - t2.minutes) / 60) % 24, (t1.minutes - t2.minutes) % 60);
}

mTime operator*(const mTime & t, double n)
{
	long totalminutes = t.hours * n * 60 + t.minutes * n;
	return mTime((totalminutes / 60)%24, totalminutes % 60);
}

mTime operator*(double n, const mTime & t)
{
	return t * n;
}

std::ostream & operator<<(std::ostream & os, const mTime & t)
{
	// TODO: 在此处插入 return 语句
	os << t.hours << " hours, " << t.minutes << " minutes";
	return os;
}

void mTimeClassTest()
{
	mTime aida(3, 35);
	mTime tosca(2, 48);
	mTime temp;
	cout << "Aida and Tosca:\n";
	cout << aida << "; " << tosca << endl;
	temp = aida + tosca;
	cout << "Aida + Tosca: " << temp << endl;
	temp = aida * 1.17;
	cout << "Aida * 1.17: " << temp << endl;
	cout << "10.0 * Tosca: " << 10.0 * tosca << endl;
}
