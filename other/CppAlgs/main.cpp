//#include "Fibonacci/fibonacci.hpp"
//#include "mGCD/mGCD.hpp"
//#include "Greedy/minRefills.hpp"
//#include "DivideConquer/BinarySearch.hpp"
//#include "mLib/mLibvector.hpp"
//#include "mLib/mLibpriorityQueue.hpp"
//#include "Sort/Sort.hpp"
//#include "mLib/mLibDisjointSet.hpp"

//#include "mLib/mLibunordered_map.hpp"
//#include "mLib/mLiblist.hpp"
//#include "mLib/mLibunordered_map.hpp"
//#include "String/RabinKarp.hpp"
//#include "mLib/mLibBinaryTree.hpp"
#include "TestData/TestData.hpp"

int main()
{
	//fibonacci_main();
	//minRefillsInterface();
	//BinarySearchTest();
	//mvectorClassTest();
	//mLib::mvectorClassTimeTest();
	//mLib::mLibpriorityQueueClassTimeTest();
	//SortInterface();
	//mLib::mLibDisjointSetClassTest();

	//mLib::mLibunorderedmapClassTest();
	//mLib::mlistClassTest();
	//mLib::mLibunordered_mapClassTest();
	//RabinKarpInterface();
	//mLib::mLibBinaryTreeClassTest();

	//�����·������Զ�����, �������������Ȼ�����, ÿ�ζ�����һ�麯��
	for (int i = 0; i < 10; ++i)
	{
		genTestDataBinarySearchTreeInterface();
		TestBinarySearchTreeInterface();

		genTestDataAVLTreeInterface();
		TestAVLTreeInterface();
	}

	return 0;
}
