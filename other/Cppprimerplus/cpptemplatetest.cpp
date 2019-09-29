#include "cpptemplatetest.h"

template<typename T>
T const mMax(T const& para1, T const & para2)
{
	return (para1 < para2) ? para2 : para1;
}

//cpp11特性，自动推断函数返回类型
template<typename T1, typename T2>
auto mMaxCpp11(T1 const& para1, T2 const& para2) -> decltype(true ? para1 : para2)
{
	return (para1 < para2) ? para2 : para1;
}

//cpp14特性，自动推断函数返回类型
template<typename T1, typename T2>
auto mMaxCpp14(T1 const& para1, T2 const& para2)
{
	return (para1 < para2) ? para2 : para1;
}

//cpp11特性，自动推断函数返回类型，std::decay<xxx>可将引用等特殊类型去除
template<typename T1, typename T2>
auto mMaxCpp11E(T1 const& para1, T2 const& para2) -> typename decay<decltype(true ? para1 : para2)>::type
{
	return (para1 < para2) ? para2 : para1;
}

//cpp14特性，返回common_type，common_type也有decay的功能：可将引用等特殊类型去除
template<typename T1, typename T2>
common_type_t<T1, T2> mMaxCpp14C(T1 const& para1, T2 const& para2)
{
	return (para1 < para2) ? para2 : para1;
}

//Val 非类型模板参数
template<typename T, int Val>
T const mAdd(T const& p1)
{
	return p1 + Val;
}

//可变数量模板参数
void print()
{

}

template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
	cout << firstArg << endl;
	cout << "remain1: " << sizeof...(Types) << endl;
	cout << "remain2: " << sizeof...(args) << endl;
	print(args...);
}

void pam(int i)
{
	cout << i << endl;
}

template<typename T, typename... Types>
void estimate(T firstArg, Types... args)
{
	time_t starttime = time(0);
	firstArg(args...);
	time_t endtime = time(0);
	cout << "used time: " << (endtime - starttime) << endl;
}

void cpptemplatetest1()
{
	void(*pf)(int);
	pf = pam;

	estimate(pf, 1);


	vector<int> v;
	//v.emplace_back(1, 2, 3);

	/*
	common_type<int, double>::type cpp11; //cpp11特性
	common_type_t<int, double> cpp14;     //cpp14特性

	double d1 = 2.1;
	int i1 = 1;
	cout << mMaxCpp11(d1, i1) << endl;
	cout << mMaxCpp14(d1, i1) << endl;
	cout << mMaxCpp11E(d1, i1) << endl;
	cout << mMaxCpp14C(d1, i1) << endl;
	*/

	//cout << mAdd<int, 5>(1) << endl;

	//print(7, 5, "hello", string("dsds"));

}
