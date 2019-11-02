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

//�Զ�����ģ���Ƶ�, c++17����
//һ��Aggregate��һ���������һ��û���û��������캯����
// û��˽�л򱣻����͵ķǾ�̬���ݳ�Ա��û�и�����麯��������(class,
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
