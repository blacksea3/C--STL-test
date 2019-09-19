#include "mSales.h"

mSales::bad_index::bad_index(int ix, const string & s) :
	logic_error(s), bi(ix)
{
}

mSales::mSales(int yy)
{
	year = yy;
	for (int i = 0; i < MONTHS; ++i)
		gross[i] = 0;
}

mSales::mSales(int yy, const double * gr, int n)
{
	year = yy;
	int lim = (n < MONTHS) ? n : MONTHS;
	int i;
	for (i = 0; i < lim; ++i)
	{
		gross[i] = gr[i];
	}
	for (; i < MONTHS; ++i)
	{
		gross[i] = 0;
	}
}

double mSales::operator[](int i) const
{
	if (i < 0 || i >= MONTHS)
		throw bad_index(i);
	return gross[i];
}

double & mSales::operator[](int i)
{
	if (i < 0 || i >= MONTHS)
		throw bad_index(i);
	return gross[i];
}

LabeledSales::nbad_index::nbad_index(const string & lb, int ix, const string & s) :
	mSales::bad_index(ix, s)
{
	lbl = lb;
}

LabeledSales::LabeledSales(const string & lb, int yy) : mSales(yy)
{
	label = lb;
}

LabeledSales::LabeledSales(const string & lb, int yy, const double * gr, int n) :
	mSales(yy, gr, n)
{
	label = lb;
}

double LabeledSales::operator[](int i) const
{
	if (i < 0 || i >= MONTHS)
		throw nbad_index(Label(), i);
	return mSales::operator[](i);
}

double & LabeledSales::operator[](int i)
{
	if (i < 0 || i >= MONTHS)
		throw nbad_index(Label(), i);
	return mSales::operator[](i);
}

void mSalesClassTest()
{
	double vals1[12] =
	{
		1220, 1100, 1122, 2212, 1232, 2334,
		2884, 2393, 3302, 2922, 3002, 3544
	};
	double vals2[12] =
	{
		12, 11, 22, 21, 32, 34,
		28, 29, 33, 29, 32, 35
	};
	mSales sales(2011, vals1, 12);
	LabeledSales sales2("Blogstar", 2012, vals2, 12);
	
	cout << "First try block:\n";
	try
	{
		cout << "Year = " << sales.Year() << endl;
		for (int i = 0; i < 12; ++i)
		{
			cout << sales[i] << ' ';
			if (i % 6 == 5)
				cout << endl;
		}
		cout << "Year = " << sales2.Year() << endl;
		cout << "Label = " << sales2.Label() << endl;
		for (int i = 0; i < 12; ++i)
		{
			cout << sales2[i] << ' ';
			if (i % 6 == 5)
				cout << endl;
		}
		cout << "End of try block 1." << endl;
	}
	//使用dynamic_cast消除显示对象所属类的判断
	catch (mSales::bad_index & bad)
	{
		cout << bad.what();
		cout << "bad index: " << bad.bi_val() << endl;
		//mSales::bad_index* pbad = &bad;
		LabeledSales::nbad_index* pnbad;
		if (pnbad = dynamic_cast<LabeledSales::nbad_index*>(&bad))
		{
			cout << "label: " << pnbad->label_val() << endl;
		}
	}

	cout << "Next try block:\n";
	try
	{
		sales2[2] = 37.5;
		sales[20] = 23345;
		cout << "End of try block 2.\n";
	}
	catch (mSales::bad_index & bad)
	{
		cout << bad.what();
		cout << "bad index: " << bad.bi_val() << endl;
		//mSales::bad_index* pbad = &bad;
		LabeledSales::nbad_index* pnbad;
		if (pnbad = dynamic_cast<LabeledSales::nbad_index*>(&bad))
		{
			cout << "label: " << pnbad->label_val() << endl;
		}
	}
}
