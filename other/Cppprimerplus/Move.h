#pragma once

#include "global.h"

class Move
{
private:
	double x, y;
public:
	Move(double a = 0, double b = 0);  //设置a->x, b->y
	void showmove() const; //展示x和y
	Move add(const Move & m) const; //把m的x和y加到当前的x和y上并且创建一个新对象Move然后返回
	void reset(double a = 0, double b = 0); //设置a->x, b->y
	~Move();
};

void MoveClassTest();
