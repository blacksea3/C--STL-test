#include "m2Stack.h"


template<typename T>
void m2Stack<T>::push(T const & elem)
{
	elems.emplace_back(elem);
}

template<typename T>
T m2Stack<T>::pop()
{
	assert(!elems.empty());
	T elem = elems.back();
	elems.pop_back();
	return elem;
}

template<typename T>
T const & m2Stack<T>::top() const
{
	assert(!elems.empty());
	return elems.back();
}

template<typename T>
void m2Stack<T>::printOn(ostream & os) const
{
	for (T const& elem : elems)
	{
		os << elem << ' ';
	}
}

template<typename T>
ostream& operator<<(ostream & os, m2Stack<T> const & s)
{
	s.printOn(os);
	return os;
}

void m2StackClassTest()
{
	ValueWithComment<string> vc2 = { "hello", "initial value" };
	int i = 1;
}
