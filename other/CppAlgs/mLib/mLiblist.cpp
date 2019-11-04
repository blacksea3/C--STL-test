#include "mLiblist.hpp"

namespace mLib
{
	void mLib::mlistClassTest()
	{
		mLib::mlist<int> m;
		m.pushback(1);
		m.pushback(2);
		m.pushback(3);
		cout << m << endl;

		mLib::mlist<int> m2(m);
		cout << m2 << endl;
		mLib::mlist<int> m3;
		m3.pushback(4);
		m3.pushback(5);
		m3.pushback(6);
		cout << m3 << endl;
		m3 = m;
		cout << m3 << endl;

		m.erase(2);
		cout << m << endl;
	}
}
