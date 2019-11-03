#pragma once

namespace mLib
{
	/*
	template<typename T>
	T infinity()
	{
		if (std::is_same<T, int>) return INT_MAX;
		else if (std::is_same<T, double>) return (double)INT_MAX;
		else throw "not support type";
	}
	*/

	template<typename T>
	void swap(T& t1, T& t2)
	{
		T temp;
		temp = t1;
		t1 = t2;
		t2 = temp;
	}

	template<typename T>
	inline T min(T t1, T t2)
	{
		return (t1 <= t2) ? t1 : t2;
	}
}
