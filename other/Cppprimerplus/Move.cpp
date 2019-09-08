#include "Move.h"

Move::Move(double a, double b)
{
	x = a;
	y = b;
}

void Move::showmove() const
{
	cout << "x = " << this->x << "  y = " << this->y << endl;
}

Move Move::add(const Move & m) const
{
	return Move(this->x + m.x, this->y + m.y);
}

void Move::reset(double a, double b)
{
	this->x = a;
	this->y = b;
}

Move::~Move()
{
}

void MoveClassTest()
{
	Move m = Move(1.0, 1.0);
	m.showmove();
	Move ano = m.add(Move(2.0));
	ano.showmove();
	m.showmove();

	ano.reset(3.0, 3.0);
	ano.showmove();
}
