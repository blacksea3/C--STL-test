#include "mVector.h"

void mVector::set_x(double inputx)
{
	x = inputx;
}

void mVector::set_y(double inputy)
{
	y = inputy;
}

mVector::mVector()
{
}

mVector::mVector(double n1, double n2, Mode form)
{
	if (form == RECT)
	{
		x = n1;
		y = n2;
	}
	else if(form == POL)
	{
		x = n1 * cos(n2);
		y = n1 * sin(n2);
	}
	else
	{
		cout << "Invalid 3rd argument in mVector()";
		cout << " set x = y = 0.0";
		x = 0.0;
		y = 0.0;
	}
}

void mVector::reset(double n1, double n2, Mode form)
{
	if (form == RECT)
	{
		x = n1;
		y = n2;
	}
	else if (form == POL)
	{
		x = n1 * cos(n2);
		y = n1 * sin(n2);
	}
	else
	{
		cout << "Invalid 3rd argument in reset()";
		cout << " set x = y = 0.0";
		x = 0.0;
		y = 0.0;
	}
}


mVector::~mVector()
{
}

double mVector::magval() const
{
	return sqrt(x * x + y * y);
}

double mVector::angval() const
{
	if (x == 0.0 && y == 0.0) return 0.0;
	else return atan2(y, x);
}

mVector mVector::operator+(const mVector & b) const
{
	return mVector(x + b.x, y + b.y);
}

mVector mVector::operator-(const mVector & b) const
{
	return mVector(x - b.x, y - b.y);
}

mVector mVector::operator-() const
{
	return mVector(-x, -y);
}

mVector mVector::operator*(double n) const
{
	return mVector(n * x, n * y);
}

mVector operator*(double n, const mVector & a)
{
	return a * n;
}

std::ostream & operator<<(std::ostream & os, const mVector & v)
{
	// TODO: 在此处插入 return 语句
	os << "(x,y) = (" << v.x << ", " << v.y << ")";
	return os;
}

void mVectorClassTest()
{
	srand((unsigned int)time(0));
	double direction;
	mVector step;
	mVector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	unsigned long max_step = 0;
	unsigned long min_step = INT_MAX;
	unsigned long sum_step = 0;
	unsigned long num_of_step = 0;
	// 以写模式打开文件
	ofstream f;
	f.open("C:\\Users\\blacksea9\\Desktop\\mVectorClassTest.txt");  //路径按需修改

	cout << "Enter target distance (q to quit): ";
	while (cin >> target)
	{
		cout << "Enter step length: ";
		if (!(cin >> dstep))
		{
			break;
		}

		f << "=========================================" << endl;
		f << "Target Distance: " << target << ", Step Size: " << dstep << endl;

		while (result.magval() < target)
		{
			f << result << endl;
			direction = (rand() % 360) / 180.0;
			step.reset(dstep, direction, mVector::POL);
			result = result + step;
			steps++;
		}

		//输出至文件
		f << "After " << steps << " steps, the subject "
			"has the following location:\n";
		f << result << endl;
		f << "Avarage outward distance per step = "
			<< result.magval() / steps << endl;
		num_of_step++;
		max_step = max(max_step, steps);
		min_step = min(min_step, steps);
		sum_step += steps;
		steps = 0;
		result.reset(0.0, 0.0);

		cout << "Enter target distance (q to quit): ";
	}

	//最高、最低步数、平均步数放入最后的文件
	f << "=========================================" << endl;
	f << "Max steps: " << max_step  << endl;
	f << "Min steps: " << min_step << endl;
	f << "Average steps: " << (double)sum_step/num_of_step << endl;

	cout << "Bye!\n";
	cin.clear();
}
