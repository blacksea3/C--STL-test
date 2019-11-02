#include "../public/public.hpp"
#include "mLibpriorityQueue.hpp"

namespace mLib
{
	void mLibpriorityQueueClassTest()
	{
		mLib::mpriorityqueue<int> mpq;

		mpq.insert(20);
		mpq.insert(12);
		mpq.insert(25);
		mpq.insert(15);
		mpq.insert(20);

		cout << mpq.extractmax() << endl;
		cout << mpq.getmax() << endl;
		cout << mpq.extractmax() << endl;
		cout << mpq.extractmax() << endl;
		cout << mpq.extractmax() << endl;
		cout << mpq.extractmax() << endl;
	}

	void stdpq(size_t loop, int vals)
	{
		std::priority_queue<int> pq;
		for (size_t i = 0; i < loop; ++i)
		{
			for (int v = 0; v < vals; v += 2) pq.push(v);
			for (int v = 1; v < vals; v += 2) pq.push(v);
			for (int v = 0; v < vals; ++v) pq.top();
		}
	}

	void mLibpq(size_t loop, int vals)
	{
		mLib::mpriorityqueue<int> pq;
		for (size_t i = 0; i < loop; ++i)
		{
			for (int v = 0; v < vals; v += 2) pq.insert(v);
			for (int v = 1; v < vals; v += 2) pq.insert(v);
			for (int v = 0; v < vals; ++v) pq.getmax();
		}
	}

	void mLibpriorityQueueClassTimeTest()
	{
		cout << "mLibpriorityqueue";
		estimateFuncTime(mLibpq, 1, 1000000);
		cout << "stdpriorityqueue";
		estimateFuncTime(stdpq, 1, 1000000);
	}
}
