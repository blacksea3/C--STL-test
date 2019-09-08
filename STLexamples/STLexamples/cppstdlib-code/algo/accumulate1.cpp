/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference, 2nd Edition"
 * by Nicolai M. Josuttis, Addison-Wesley, 2012
 *
 * (C) Copyright Nicolai M. Josuttis 2012.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */

#include "algostuff.hpp"
using namespace std;

void test1()
{
	vector<int> coll;

	INSERT_ELEMENTS(coll, 1, 9);
	PRINT_ELEMENTS(coll);

	// process sum of elements
	cout << "sum: "
		<< accumulate(coll.cbegin(), coll.cend(),  // range
			0)                           // initial value
		<< endl;

	// process sum of elements less 100
	cout << "sum: "
		<< accumulate(coll.cbegin(), coll.cend(),  // range
			-100)                        // initial value
		<< endl;

	// process product of elements
	cout << "product: "
		<< accumulate(coll.cbegin(), coll.cend(),  // range
			1,                           // initial value
			multiplies<int>())           // operation
		<< endl;

	// process product of elements (use 0 as initial value)
	cout << "product: "
		<< accumulate(coll.cbegin(), coll.cend(),  // range
			0,                           // initial value
			multiplies<int>())           // operation
		<< endl;
}

void test_emplace_back_and_push_back()
{
	//����emplace_back��push_back
	clock_t startTime, startTime2;
	size_t size = 1000000;

	startTime = clock();//��ʱ��ʼ
	vector<string> v1;
	v1.reserve(size);
	for (size_t i = 0; i < size; ++i)
		v1.push_back("ceshi");
	cout << "push_back:" << clock() - startTime << endl;

	startTime2 = clock();//��ʱ��ʼ
	vector<string> v2;
	v2.reserve(size);
	for (size_t i = 0; i < size; ++i)
		v2.emplace_back("ceshi");
	cout << "emplace_back:" << clock() - startTime2 << endl;
}

void test_string_reserve()
{
	//����stringԤ����ռ�
	clock_t startTime;
	size_t size = 10000000;

	startTime = clock();//��ʱ��ʼ
	string s_no;
	for (size_t i = 0; i < size; ++i)
		//s_no.push_back('a');
		s_no += "a";
	cout << "δԤ����ռ�:" << clock() - startTime << endl;

	startTime = clock();//��ʱ��ʼ
	string s;
	s.reserve(size);
	for (size_t i = 0; i < size; ++i)
		//s.push_back('a');
		s += "a";
	cout << "Ԥ����ռ�reserve:" << clock() - startTime << endl;

	startTime = clock();//��ʱ��ʼ
	string s_resize;
	s_resize.resize(size);
	for (size_t i = 0; i < size; ++i)
		s_resize[i] = 'a';
		//s_resize += "a";
	cout << "Ԥ����ռ�resize:" << clock() - startTime << endl;
}

int main()
{
	test_string_reserve();
	return 0;
}
