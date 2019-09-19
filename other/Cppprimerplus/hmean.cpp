#include "hmean.h"

double hmean(double a, double b)
{
	if (a == -b)
	{
		//throw bad_hmean();
		throw bad_mean(a, b, "hmean");
	}
	else
	{
		return 2.0 * a * b / (a + b);
	}
}

double gmean(double a, double b)
{
	if (a == 0.0 || b == 0.0)
	{
		//throw bad_gmean();
		throw bad_mean(a, b, "gmean");
	}
	else
	{
		return 2 * sqrt(a * b);
	}
}

/*
bad_hmean::bad_hmean(const string & what_msg) : logic_error(what_msg)
{

}

bad_gmean::bad_gmean(const string & what_msg) : logic_error(what_msg)
{

}
*/

void hmeanFuncTest()
{
	try
	{
		cout << "hmean(2, -2)" << hmean(2, -2) << endl;
	}
	catch (bad_mean& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		cout << "hmean(2, -1)" << hmean(2, -1) << endl;
	}
	catch (bad_mean& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		cout << "gmean(2, 2)" << gmean(2, 2) << endl;
	}
	catch (bad_mean& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		cout << "gmean(0, 2)" << gmean(0, 2) << endl;
	}
	catch (bad_mean& e)
	{
		cout << e.what() << endl;
	}
}

bad_mean::bad_mean(double op1, double op2, string funcname) : logic_error("")
{
	this->op1 = op1;
	this->op2 = op2;
	this->funcname = funcname;
}
