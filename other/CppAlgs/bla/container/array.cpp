#include "array.hpp"
#include "../test/noTrivalClass.hpp"
#include <iostream>
using std::cout;
using std::endl;

namespace bla {
	void array_unittest() {
		{
			cout << "array<int, 10> a1 will construct" << endl;
			array<int, 10> a1;
			cout << "size of a1:" << a1.size() << endl;
			cout << "capacity of a1:" << a1.capacity() << endl;
			cout << "a1 will push back 0" << endl;
			a1.push_back(0);
			cout << "size of a1:" << a1.size() << endl;
			cout << "capacity of a1:" << a1.capacity() << endl;
			cout << "*a1.begin() of a1:" << *a1.begin() << endl;

			cout << "use copy construct: a2(a1)" << endl;
			array<int, 10> a2(a1);
			cout << "size of a2:" << a2.size() << endl;
			cout << "capacity of a2:" << a2.capacity() << endl;
			cout << "*a2.begin() of a2:" << *a2.begin() << endl;
			
			cout << "use copy construct: a3 = a1" << endl;
			array<int, 10> a3(a1);
			cout << "size of a3:" << a3.size() << endl;
			cout << "capacity of a3:" << a3.capacity() << endl;
			cout << "*a3.begin() of a3:" << *a3.begin() << endl;

			cout << "array<int, 10> a4 will construct" << endl;
			array<int, 10> a4;
			cout << "a1 will push back 2" << endl;
			a4.push_back(2);
			cout << "size of a4:" << a4.size() << endl;
			cout << "capacity of a4:" << a4.capacity() << endl;
			cout << "*a4.begin() of a4:" << *a4.begin() << endl;
			cout << "use operator=: a4 = a1" << endl;
			a4 = a1;
			cout << "size of a4:" << a4.size() << endl;
			cout << "capacity of a4:" << a4.capacity() << endl;
			cout << "*a4.begin() of a4:" << *a4.begin() << endl;

			cout << "array<int, 10> a5 will construct" << endl;
			array<int, 10> a5;
			cout << "a5 will push back 10,100" << endl;
			a5.push_back(10);
			a5.push_back(100);
			cout << "size of a5:" << a5.size() << endl;
			cout << "capacity of a5:" << a5.capacity() << endl;
			cout << "*a5.begin() of a5:" << *a5.begin() << endl;
			cout << "*(a5.begin()+1) of a5:" << *(a5.begin()+1) << endl;
			cout << "use operator=: a5 = a1" << endl;
			a5 = a1;
			cout << "size of a5:" << a5.size() << endl;
			cout << "capacity of a5:" << a5.capacity() << endl;
			cout << "*a5.begin() of a5:" << *a5.begin() << endl;
		}
		{
			cout << "array<_noTrivalClass, 3> b1 will construct" << endl;
			array<_noTrivalClass, 3> b1;
			cout << "size of b1:" << b1.size() << endl;
			cout << "capacity of b1:" << b1.capacity() << endl;
			cout << "b1 will push back _noTrivalClass('a')" << endl;
			b1.push_back(_noTrivalClass('a'));
			cout << "*(b1.begin())->ptr of b1:" << *(b1.begin())->ptr << endl;

			cout << "use copy construct: b2(b1)" << endl;
			array<_noTrivalClass, 3> b2(b1);
			cout << "size of b2:" << b2.size() << endl;
			cout << "capacity of b2:" << b2.capacity() << endl;
			cout << "*(b2.begin())->ptr of b2:" << *(b2.begin())->ptr << endl;

			cout << "use copy construct: b3 = a1" << endl;
			array<_noTrivalClass, 3> b3 = b1;
			cout << "size of b3:" << b3.size() << endl;
			cout << "capacity of b3:" << b3.capacity() << endl;
			cout << "*(b3.begin())->ptr of b3:" << *(b3.begin())->ptr << endl;

			cout << "array<_noTrivalClass, 3> b4 will construct" << endl;
			array<_noTrivalClass, 3> b4;
			cout << "b4 will push back _noTrivalClass('b')" << endl;
			b4.push_back(_noTrivalClass('b'));
			cout << "size of b4:" << b4.size() << endl;
			cout << "capacity of b4:" << b4.capacity() << endl;
			cout << "*(b4.begin())->ptr of b4:" << *(b4.begin())->ptr << endl;
			cout << "use operator=: b4 = b1" << endl;
			b4 = b1;
			cout << "size of b4:" << b4.size() << endl;
			cout << "capacity of b4:" << b4.capacity() << endl;
			cout << "*(b4.begin())->ptr of b4:" << *(b4.begin())->ptr << endl;

			cout << "array<_noTrivalClass, 3> b5 will construct" << endl;
			array<_noTrivalClass, 3> b5;
			cout << "b5 will push back _noTrivalClass('!') _noTrivalClass('&') _noTrivalClass('*')" << endl;
			b5.push_back(_noTrivalClass('!'));
			b5.push_back(_noTrivalClass('&'));
			b5.push_back(_noTrivalClass('*'));
			cout << "size of b5:" << b5.size() << endl;
			cout << "capacity of b5:" << b5.capacity() << endl;
			cout << "*(b5.begin())->ptr of b5:" << *(b5.begin())->ptr << endl;
			cout << "*(b5.begin()+1)->ptr of b5:" << *(b5.begin() + 1)->ptr << endl;
			cout << "*(b5.begin()+2->ptr of b5:" << *(b5.begin() + 2)->ptr << endl;

			cout << "use operator=: b4 = b5" << endl;
			b4 = b5;
			cout << "size of b4:" << b4.size() << endl;
			cout << "capacity of b4:" << b4.capacity() << endl;
			cout << "*(b4.begin())->ptr of b4:" << *(b4.begin())->ptr << endl;
			cout << "*(b4.begin()+1)->ptr of b4:" << *(b4.begin() + 1)->ptr << endl;
			cout << "*(b4.begin()+2->ptr of b4:" << *(b4.begin() + 2)->ptr << endl;

			cout << "use operator=: b2 = b4" << endl;
			b2 = b4;
			cout << "size of b2:" << b2.size() << endl;
			cout << "capacity of b2:" << b2.capacity() << endl;
			cout << "*(b2.begin())->ptr of b2:" << *(b2.begin())->ptr << endl;
			cout << "*(b2.begin()+1)->ptr of b2:" << *(b2.begin() + 1)->ptr << endl;
			cout << "*(b2.begin()+2->ptr of b2:" << *(b2.begin() + 2)->ptr << endl;

			cout << "use operator=: b2 = b5" << endl;
			b2 = b5;
			cout << "size of b2:" << b2.size() << endl;
			cout << "capacity of b2:" << b2.capacity() << endl;
			cout << "*(b2.begin())->ptr of b2:" << *(b2.begin())->ptr << endl;
			cout << "*(b2.begin()+1)->ptr of b2:" << *(b2.begin() + 1)->ptr << endl;
			cout << "*(b2.begin()+2->ptr of b2:" << *(b2.begin() + 2)->ptr << endl;

			cout << "use operator=: b5 = b1" << endl;
			b5 = b1;
			cout << "size of b5:" << b5.size() << endl;
			cout << "capacity of b5:" << b5.capacity() << endl;
			cout << "*(b5.begin())->ptr of b5:" << *(b5.begin())->ptr << endl;
		}
	}
}
