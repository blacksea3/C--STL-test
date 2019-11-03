#include "../public/public.hpp"
#include "mLibvector.hpp"

namespace mLib
{
	void mLibvectorpushback(size_t outloop, int sizet)
	{
		mLib::mvector<int> v;
		for (size_t i = 0; i < outloop; ++i)
		{
			for (int i = 0; i < sizet; ++i)
			{
				v.push_back(i);
			}
		}
	}

	void stdvectorpushback(size_t outloop, int sizet)
	{
		vector<int> v;
		for (size_t i = 0; i < outloop; ++i)
		{
			for (int i = 0; i < sizet; ++i)
			{
				v.push_back(i);
			}
		}
	}

	void mLibvectorinsert(size_t outloop, int sizet)
	{
		mLib::mvector<int> v;
		for (size_t i = 0; i < outloop; ++i)
		{
			for (int i = 0; i < sizet; ++i)
			{
				v.insert(0, i);
			}
		}
		;
	}

	void stdvectorinsert(size_t outloop, int sizet)
	{
		vector<int> v;
		for (size_t i = 0; i < outloop; ++i)
		{
			for (int i = 0; i < sizet; ++i)
			{
				v.insert(v.begin(), i);
			}
		}
		;
	}

	void mvectorClassTimeTest()
	{
		cout << "mLibvector:pushback";
		estimateFuncTime(mLibvectorpushback, 1, 1000000);
		cout << "stdvector:pushback";
		estimateFuncTime(stdvectorpushback, 1, 1000000);

		cout << "mLibvector:insert(0)";
		estimateFuncTime(mLibvectorinsert, 1, 10000);
		cout << "stdvector:insert(0)";
		estimateFuncTime(stdvectorinsert, 1, 10000);
	}

	void mvectorClassTest()
	{
		mLib::mvector<int> v;
		for (size_t i = 0; i < 10; ++i)
		{
			v.push_back(i);
		}
		cout << "origin v:";
		for (size_t i = 0; i < v.getSize(); ++i) cout << v[i] << " ";
		cout << endl;

		mLib::mvector<int> v2(v);
		mLib::mvector<int> v3;
		v3 = v;

		for (size_t i = 0; i < v.getSize(); ++i) v[i] += 10;
		cout << "after add 10 to all values of v:";
		for (size_t i = 0; i < v.getSize(); ++i) cout << v[i] << " ";
		cout << endl;

		for (size_t i = 0; i < 5; ++i) v.pop_back();
		cout << "after pop_back 5 items, v:";
		for (size_t i = 0; i < v.getSize(); ++i) cout << v[i] << " ";
		cout << endl;
		cout << "v2(v) from origin v";
		for (size_t i = 0; i < v2.getSize(); ++i) cout << v2[i] << " ";
		cout << endl;
		cout << "v3 = v from origin v";
		for (size_t i = 0; i < v3.getSize(); ++i) cout << v3[i] << " ";
		cout << endl;
	}
}
