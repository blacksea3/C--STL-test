#pragma once

#include "global.h"

class Move
{
private:
	double x, y;
public:
	Move(double a = 0, double b = 0);  //����a->x, b->y
	void showmove() const; //չʾx��y
	Move add(const Move & m) const; //��m��x��y�ӵ���ǰ��x��y�ϲ��Ҵ���һ���¶���MoveȻ�󷵻�
	void reset(double a = 0, double b = 0); //����a->x, b->y
	~Move();
};

void MoveClassTest();
