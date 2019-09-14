#include "mStock.h"



mStock::mStock()
{
	company = new char[1];
	company[0] = '\0';
	shares = 0;
	share_val = 0.0;
	total_val = 0.0;
}

mStock::mStock(const mStock & ms)
{
	int len = strlen(ms.company);
	company = new char[len + 1];
	strcpy(company, ms.company);
	shares = ms.shares;
	share_val = ms.share_val;
	total_val = ms.total_val;
}

mStock::mStock(const char * co, long n, double pr)
{
	int len = strlen(co);
	company = new char[len + 1];
	strcpy(company, co);
	shares = max((long)0, n);
	share_val = pr;
	set_tot();
}

mStock & mStock::operator=(const mStock & ms)
{
	if (&ms == this)
	{
		return *this;
	}
	else
	{
		delete[] company;
		company = new char[strlen(ms.company) + 1];
		strcpy(company, ms.company);
		shares = ms.shares;
		share_val = ms.share_val;
		total_val = ms.total_val;
		return *this;
	}
}


mStock::~mStock()
{
	delete[] company;
}

void mStock::buy(long num, double price)
{
	if (num < 0)
	{
		cout << "buy num shouldn't be negative, transaction aborted!" << endl;
	}
	else
	{
		shares += num;
		share_val = price;
		set_tot();
	}
}

void mStock::sell(long num, double price)
{
	if (num < 0)
	{
		cout << "sell num shouldn't be negative, transaction aborted!" << endl;
	}
	else
	{
		shares -= num;
		share_val = price;
		set_tot();
	}
}

void mStock::update(double price)
{
	share_val = price;
	set_tot();
}

const mStock & mStock::topval(const mStock & s) const
{
	if (s.total_val > total_val)
		return s;
	else
		return *this;
}

ostream & operator<<(ostream& os, const mStock & ms)
{
	//set format to #.###
	ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
	streamsize prec = cout.precision(3);
	os << "Company: " << ms.company
		<< "  Shares: " << ms.shares << endl;
	os << "  Share price: $" << ms.share_val;
	//set format to #.##
	cout.precision(2);
	os << "  Total Worth: $" << ms.total_val << endl;
	//restore original format
	cout.setf(orig, ios_base::floatfield);
	cout.precision(prec);
	return os;
}

void mStockClassTest()
{
	mStock stocks[4] =
	{
		mStock("NanoSmart", 12, 20.0),
		mStock("Boffo Objects", 200, 2.0),
		mStock("Monolithic Obelisks", 130, 3.25),
		mStock("Fleep Enterprices", 60, 6.5)
	};
	cout << "Stock holdings:" << endl;
	int st;
	for (st = 0; st < 4; ++st)
	{
		cout << stocks[st];
	}
	const mStock* top = &stocks[0];
	for (st = 1; st < 4; ++st)
	{
		top = &top->topval(stocks[st]);
	}
	cout << endl << "Most valuable holding:" << endl;
	cout << *top;
}
