#include "Plorg.h"


Plorg::Plorg(string inputname)
{
	if (inputname.size() > 18)
	{
		this->name = inputname.substr(0, 18);
	}
	else
	{
		this->name = inputname;
	}
	this->CI = 50;
}

void Plorg::setCI(int inputCI)
{
	this->CI = inputCI;
}

void Plorg::display() const
{
	cout << "name:" << this->name.c_str() << " CI:" << this->CI << endl;
}

Plorg::~Plorg()
{
}

void PlorgClassTest()
{
	Plorg pl_1 = Plorg("abcde");
	pl_1.display();
	pl_1.setCI(20);
	pl_1.display();

	Plorg pl_2 = Plorg();
	pl_2.display();
}
