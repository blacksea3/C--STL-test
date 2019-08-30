#include "Golf.h"

Golf::Golf(const char * name, int hc)
{
	size_t firstNameLength = strnlen_s(name, Golf::Len);
	if (firstNameLength == Golf::Len) //Ç¿ÖÆ½Ø¶Ï
	{
		this->fullname[Golf::Len - 1] = '\n';
		strncpy_s(this->fullname, name, Golf::Len - 1);
	}
	else
	{
		strncpy_s(this->fullname, name, Golf::Len - 1);
	}
	this->handicap = hc;
}

/*
Golf::Golf(const Golf & initGolf)
{
	strncpy_s(this->fullname, initGolf.fullname, Golf::Len - 1);
	this->handicap = initGolf.handicap;
}
*/

void Golf::setgolf()
{
	cout << "InputName:" << endl;
	char name[Golf::Len];
	cin >> name;
	cout << "InputHandicap" << endl;
	int hc;
	cin >> hc;

	Golf g(name, hc);
	*this = g;
}

void Golf::sethandicap(int hc)
{
	this->handicap = hc;
}

void Golf::showgolf() const
{
	cout << "name:" << this->fullname << endl;
	cout << "hc:" << this->handicap << endl;
}

Golf::~Golf()
{
}

void GolfClassTest()
{
	Golf g1("name", 10);
	g1.showgolf();
	g1.sethandicap(20);
	g1.showgolf();
	cout << endl;

	Golf g2;
	g2.showgolf();
	g2.setgolf();
	g2.showgolf();
	cout << endl;
}
