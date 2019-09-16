#include "Wine.h"

Wine::Wine()
{
	name = "";
	numYear = 0;
	numYearRelation.first.resize(0);
	numYearRelation.second.resize(0);
}

Wine::Wine(const char * l, int y, const int yr[], const int bot[])
{
	name = l;
	numYear = y;
	numYearRelation.first = valarray<int>(yr, y);
	numYearRelation.second = valarray<int>(bot, y);
}

Wine::Wine(const char * l, int y)
{
	name = l;
	numYear = y;
	numYearRelation.first.resize(y);
	numYearRelation.second.resize(y);
}

void Wine::GetBottles()
{
	cout << "Input " << numYear << "years of bottles" << endl;
	for (int index = 0; index < numYear; ++index)
	{
		cout << endl;
		cout << "Input year 1:";
		cin >> numYearRelation.first[index];
		cout << "Input bottles 1:";
		cin >> numYearRelation.second[index];
	}
	cout << "end input" << endl;
}

const string & Wine::Label() const
{
	return name;
}

int Wine::sum()
{
	return numYearRelation.second.sum();
}

void Wine::Show() const
{
	cout << "Name: " << name << endl;
	cout << "Show " << numYear << "years of bottles" << endl;
	for (int index = 0; index < numYear; ++index)
	{
		cout << "Year 1:" << numYearRelation.first[index]
			<< ", Bottles 1:" << numYearRelation.second[index];
	}
}


Wine::~Wine()
{
}

void WineClassTest()
{
	cout << "Enter name of wine: ";
	char lab[50];
	cin.getline(lab, 50);
	cout << "Enter number of years: ";
	int yrs;
	cin >> yrs;

	Wine holding(lab, yrs);
	holding.GetBottles();
	holding.Show();

	const int YRS = 3;
	int y[YRS] = { 1993, 1995, 1998 };
	int b[YRS] = { 48, 60, 72 };
	Wine more("Guiding Grape Res", YRS, y, b);
	cout << "Total bottles for " << more.Label()
		<< ": " << more.sum() << endl;
	cout << "Bye" << endl;
}
