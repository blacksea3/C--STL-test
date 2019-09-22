#pragma once
#include "global.h"

template<typename T>
class m2Stack
{
private:
	vector<T> elems;
public:
	//m2Stack();
	//~m2Stack();

	void push(T const& elem);
	T pop();
	T const& top() const;
	bool empty() const { return elems.empty(); };
	void printOn(ostream& os) const;
	friend ostream& operator<<(ostream& os, m2Stack<T> const& s);

};

//自定义类模板推导, c++17引入
//一个Aggregate是一个数组或者一个没有用户声明构造函数，
// 没有私有或保护类型的非静态数据成员，没有父类和虚函数的类型(class,
// struct, unions)
m2Stack(char const*) -> m2Stack<string>;

//aggregrate class
template<typename T>
struct ValueWithComment {
	T value;
	std::string comment;
};

ValueWithComment(char const*, char const*) -> ValueWithComment<std::string>;

void m2StackClassTest();
