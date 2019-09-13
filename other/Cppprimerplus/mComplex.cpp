#include "mComplex.h"

mComplex::mComplex()
{
	real = 0.0;
	image = 0.0;
}

mComplex::mComplex(double r, double i)
{
	real = r;
	image = i;
}


mComplex::~mComplex()
{
}

std::ostream& operator<<(std::ostream & os, const mComplex & c)
{
	os << "(" << c.real << "," << c.image << "i)" << endl;
	return os;
}

//注意, 内部会提示如何输入, 直接使用cin 命令行提示
bool operator>>(std::istream & is, mComplex & c)
{
thisFuncStart:
	cout << "real: ";
	double r;
	double i;
	string temp;
	cin >> temp;
	size_t effectSize;
	try
	{
		r = stod(temp, &effectSize);
	}
	catch (std::invalid_argument)
	{
		cout << "I think you want to exit this program!\n";
		return false;
	}
	catch (std::out_of_range)
	{
		cout << "input num is out_of_range of double :(, please enter real again!\n";
		goto thisFuncStart;
	}
thisFuncMiddleStart:
	cout << "imaginary: ";
	cin >> temp;
	try
	{
		i = stod(temp, &effectSize);
	}
	catch (std::invalid_argument)
	{
		cout << "I think you want to exit this program!\n";
		return false;
	}
	catch (std::out_of_range)
	{
		cout << "input num is out_of_range of double :(, please enter image again!\n";
		goto thisFuncMiddleStart;
	}
	c = mComplex(r, i);
	return true;
}

void mComplexClassTest()
{
	mComplex a(3.0, 4.0);
	mComplex c;

	cout << "Enter a complex number (q to quit):\n";
	while (cin >> c)
	{
		cout << "c is " << c << endl;
		cout << "complex conjugate is " << ~c << endl;
		cout << "a is " << a << endl;
		cout << "a + c is " << a + c << endl;
		cout << "a - c is " << a - c << endl;
		cout << "a * c is " << a * c << endl;
		cout << "2 * c is " << 2 * c << endl;
		cout << "Enter a complex number (q to quit):\n";
	}
	cout << "Done!\n";
}
