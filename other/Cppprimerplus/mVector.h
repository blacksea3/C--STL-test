#pragma once

#include "global.h"

//向量类
class mVector
{
public:
	enum Mode{RECT, POL}; //rect: 直角坐标; POL: 极坐标
private:
	double x, y;
	//void set_mag(); //设置长度
	//void set_ang(); //设置角度
	void set_x(double inputx);     //设置x
	void set_y(double inputy);     //设置y
public:
	mVector();
	mVector(double n1, double n2, Mode form = RECT);
	void reset(double n1, double n2, Mode form = RECT);
	~mVector();

	double xval() const { return x; }
	double yval() const { return y; }
	double magval() const;
	double angval() const;
	//void polar_mode(); //set mode: polar
	//void rect_mode();  //set mode:rect

	mVector operator+(const mVector & b) const;
	mVector operator-(const mVector & b) const;
	mVector operator-() const;
	mVector operator*(double n) const;

	friend mVector operator*(double n, const mVector & a);
	friend std::ostream & operator<<(std::ostream & os, const mVector & v);
};

void mVectorClassTest();
