#include "Port.h"

Port::Port(const char * br, const char * st, int b)
{
	brand = new char[strlen(br) + 1];
	strcpy(brand, br);
	size_t stSize = strlen(st);
	if (stSize > 19)
	{
		strncpy_s(style, 19, st, 19);
		style[19] = '\0';
	}
	else
	{
		strcpy(style, st);
	}
	bottles = b;
}

Port::Port(const Port & p)
{
	brand = new char[strlen(p.brand) + 1];
	strcpy(brand, p.brand);
	size_t stSize = strlen(p.style);
	if (stSize > 19)
	{
		strncpy_s(style, 19, p.style, 19);
		style[19] = '\0';
	}
	else
	{
		strcpy(style, p.style);
	}
	bottles = p.bottles;
}

Port & Port::operator=(const Port & p)
{
	if (&p == this)
	{
		return *this;
	}
	else
	{
		brand = new char[strlen(p.brand) + 1];
		strcpy(brand, p.brand);
		size_t stSize = strlen(p.style);
		if (stSize > 19)
		{
			strncpy_s(style, 19, p.style, 19);
			style[19] = '\0';
		}
		else
		{
			strcpy(style, p.style);
		}
		bottles = p.bottles;
		return *this;
	}
}

Port & Port::operator+=(int b)
{
	bottles += b;
	return *this;
}

Port & Port::operator-=(int b)
{
	bottles = max(bottles - b, 0);
	return *this;
}

void Port::Show() const
{
	cout << "brand: " << brand << endl;
	cout << "style: " << style << endl;
	cout << "bottles: " << bottles << endl;
}

ostream & operator<<(ostream & os, const Port & p)
{
	os << p.brand << p.style << p.bottles;
	return os;
}

VintagePort::VintagePort() : Port()
{
	nickname = new char[1];
	nickname[0] = '\n';
	year = 0;
}

VintagePort::VintagePort(const char * br, int b, const char * nn, int y) :
	Port(br, "vintage", b)
{
	nickname = new char[strlen(nn) + 1];
	strcpy(nickname, nn);
	year = y;
}

VintagePort::VintagePort(const VintagePort & vp) :
	Port(vp)
{
	nickname = new char[strlen(vp.nickname) + 1];
	strcpy(nickname, vp.nickname);
	year = vp.year;
}

VintagePort & VintagePort::operator=(const VintagePort & vp)
{
	if (&vp == this)
	{
		return *this;
	}
	else
	{
		Port::operator=(vp);
		nickname = new char[strlen(vp.nickname) + 1];
		strcpy(nickname, vp.nickname);
		year = vp.year;
		return *this;
	}
}

void VintagePort::Show() const
{
	Port::Show();
	cout << "nickname: " << nickname << endl;
	cout << "year: " << year << endl;
}

ostream & operator<<(ostream & os, const VintagePort & p)
{
	os << (Port)p;
	os << p.nickname << p.year;
	return os;
}

void PortClassTest()
{
	Port p1("Gallo", "tawny", 20);
	cout << "p1.Show():" << endl;
	p1.Show();
	cout << "cout << p1;" << endl;
	cout << p1;
	cout << "p1+=1;" << endl;
	p1 +=1;
	cout << "cout << p1;" << endl;
	cout << p1;
	cout << "p1-=2;" << endl;
	p1 -=2;
	cout << "cout << p1;" << endl;
	cout << p1;

	VintagePort vp1("brand", 20, "nn", 2019);
	cout << "vp1.Show():" << endl;
	vp1.Show();
	cout << "cout << vp1;" << endl;
	cout << vp1;
	cout << "vp1+=1;" << endl;
	vp1 += 1;
	cout << "cout << vp1;" << endl;
	cout << vp1;
	cout << "vp1-=2;" << endl;
	vp1 -= 2;
	cout << "cout << vp1;" << endl;
	cout << vp1;
}
