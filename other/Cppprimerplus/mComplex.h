#pragma once
#include "global.h"

//�Զ��帴����
class mComplex
{
private:
	double real;
	double image;
public:
	mComplex();
	mComplex(double r, double i);
	inline mComplex operator+(const mComplex& c) const { return mComplex(real + c.real, image + c.image); };
	inline mComplex operator-(const mComplex& c) const { return mComplex(real - c.real, image - c.image); };
	inline mComplex operator*(const mComplex& c) const
	{
		return mComplex(real*c.real - image * c.image,
			real*c.image + image * c.real);
	};
	inline friend mComplex operator*(double n, const mComplex& c)
	{
		return mComplex(n*c.real, n*c.image);
	};
	inline mComplex operator~() const { return mComplex(real, -image); };
	friend std::ostream& operator<<(std::ostream& os, const mComplex& c);
	friend bool operator>>(std::istream& is, mComplex& c); //ע��, �ڲ�����ʾ�������, ֱ��ʹ��cin ��������ʾ
	~mComplex();
};

void mComplexClassTest();
