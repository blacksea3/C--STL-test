#pragma once
#include "global.h"

//求调和平均数, 内部可抛出异常
double hmean(double a, double b);
//求几何平均数, 内部可抛出异常
double gmean(double a, double b);

/*
class bad_hmean : public logic_error
{
public:
	const char* what() { return "bad arguments to hmean()"; };
	explicit bad_hmean(const string& what_msg = "");
};

class bad_gmean : public logic_error
{
public:
	const char* what() { return "bad arguments to gmean()"; };
	explicit bad_gmean(const string& what_msg = "");
};
*/

class bad_mean : public logic_error
{
private:
	double op1;
	double op2;
	string funcname;
public:
	explicit bad_mean(double op1, double op2, string funcname);
	//注: 我这里修改了what返回参数类型
	const string what() {
		return "bad arguments to " + funcname +
			"ops:" + to_string(op1) + "and" + to_string(op2);
	};
};

void hmeanFuncTest();
