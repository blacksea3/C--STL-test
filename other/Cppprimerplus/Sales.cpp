#include "Sales.h"

SALES::Sales::Sales(const double ar[], int n)
{
	double tempSum = 0.0;
	double tempMax = INT_MIN;
	double tempMin = INT_MAX;
	for (int index = 0; index < min(n, 3); ++index)
	{
		this->sales[index] = ar[index];
		tempMax = max(ar[index], tempMax);
		tempMin = min(ar[index], tempMin);
		tempSum += ar[index];
	}
	this->average = tempSum / (double)min(n, 3);
	this->smax = tempMax;
	this->smin = tempMin;
	this->validSales = n;
}

SALES::Sales::Sales()
{
	int n = -1;
	do
	{
		cout << "input number of sales: range:[1, 4]" << endl;
		cin >> n;
		if (0 <= n && n <= 4) break;
		cout << "ÊäÈë´íÎó" << endl;
	} while (true);

	double tempSum = 0.0;
	double tempMax = INT_MIN;
	double tempMin = INT_MAX;
	for (int index = 0; index < n; ++index)
	{
		cout << "input sale" << endl;
		cin >> this->sales[index];
		tempMax = max(this->sales[index], tempMax);
		tempMin = min(this->sales[index], tempMin);
		tempSum += this->sales[index];
	}
	this->average = tempSum / (double)min(n, 3);
	this->smax = tempMax;
	this->smin = tempMin;
	this->validSales = n;
}

void SALES::Sales::showSales() const
{
	for (int index = 0; index < this->validSales; ++index)
	{
		cout << "sale" << index << ":" << this->sales[index] << endl;
	}
	cout << "average:" << this->average << endl;
	cout << "min:" << this->smin << endl;
	cout << "max:" << this->smax << endl;
}


SALES::Sales::~Sales()
{
}

void SalesClassTest()
{
	double d[3] = { 1.5, 2.5, 3.5 };
	SALES::Sales s1(d, 3);
	s1.showSales();

	SALES::Sales s2;
	s2.showSales();
}
