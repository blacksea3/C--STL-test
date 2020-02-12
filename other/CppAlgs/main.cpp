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
//#include "TestData/TestTreeData.hpp"
//#include "TestData/TestStringData.hpp"
//#include "String/BWT.hpp"
//#include "String/Trie.hpp"
//#include "String/KMP.hpp"
//#include "String/SuffixArray.hpp"
//#include "Graph/graphMain.hpp"
//#include "mLib/mLibSimplifyBinaryTree.hpp"
//#include "Graph/topologicalSort.hpp"
//#include "Graph/strongConnectedComponents.hpp"
//#include "Graph/BFS.hpp"
//#include "Graph/dijkstra.hpp"
//#include "Graph/BellmanFord.hpp"
//#include "Graph/Kruskal.hpp"
//#include "Graph//Prim.hpp"
//#include "Graph/tarjanSCC.hpp"
//#include "Graph/tarjanUGNode.hpp"
//#include "Graph/tarjanUGedge.hpp"

//#include "json/test/official_unittest_interface.hpp"
//#include "json/test/m_unittest.hpp"
//#include "json/judgeFrame.hpp"

//#include "mLib/mLibTest.hpp"

#include "mptr/mPtr.hpp"

//���Զ�λ�������ڴ�й¶ ���ڵ��ļ��;�����һ�У����ڼ�� malloc ������ڴ�
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>

/* ��ʹ�����, ������Ϊ����Ҫʹ�ö�λnew�����ڴ�
//�ѷ����ڴ����Ϣ�������������Զ�λ����һ�з������ڴ�й¶�����ڼ�� new ������ڴ�
//#ifdef _DEBUG
//#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif
*/

//����
inline void EnableMemLeakCheck()
{
	//������ڳ����˳�ʱ�Զ����� _CrtDumpMemoryLeaks(),���ڶ���˳����ڵ����.
	//���ֻ��һ���˳�λ�ã������ڳ����˳�֮ǰ���� _CrtDumpMemoryLeaks()
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

int main(int argc, const char* argv[])
{
	EnableMemLeakCheck();
	

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

	//�����·������Զ�����/�ֵ���, �������������Ȼ�����, ÿ�ζ�����һ�麯��
	//for (int i = 0; i < 10; ++i)
	//{
		//GenTrieTestDataInterface();
		//TrieClassTestInterface();

		//genTestDataBinarySearchTreeInterface();
		//TestRedBlackTreeInterface();
		//TestBinarySearchTreeInterface();
		//TestSplayTreeInterface();

		//genTestDataAVLTreeInterface();
		//TestAVLTreeInterface();
	//}

	//BWTconversionTest();
    //SuffixTriePatternMatchingTest();
	//KMPtest();
	//SuffixArrayTest();
	//graphMainInterface();
	//msp_searchtreeTest();
	//topologicalSortTest();
	//sCCsTest();
	//BFSTest();
	//dijkstraTest();
	//BFTest();
	//kruskalTest();
	//primTest();
	//tarjansCCTest();
	//tarjanUGNodeTest();
	//tarjanUGedgeTest();

	//jsonUnitestTest();
	//m_json_unittest_interface();

	//m_JSONFrame::judgeFrame_unittest();

	//mLib::mLibTest_unittest();

	//_CrtSetBreakAlloc(191);

	//_CrtDumpMemoryLeaks(); //�����������������������ڴ������Ϣ;
	
	//mptr::mAutoPtr_unittest();
	//mptr::mScopedPtr_unittest();
	//mptr::mSharedPtr_unittest();

	mptr::mWeakPtr_unittest();

	return 0;
}
