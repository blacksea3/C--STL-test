#pragma once
#include "global.h"

namespace SALES
{
	class Sales
	{
	private:
		const static int QUARTERS = 4;
		double sales[QUARTERS];
		double average;
		double smax;
		double smin;
		int validSales;
	public:
		Sales(const double ar[], int n);
		Sales();
		void showSales() const;
		~Sales();
	};
}

void SalesClassTest();
