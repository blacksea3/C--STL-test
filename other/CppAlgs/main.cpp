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

//可以定位到发生内存泄露 所在的文件和具体那一行，用于检测 malloc 分配的内存
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>

/* 不使用这个, 这是因为我需要使用定位new分配内存
//把分配内存的信息保存下来，可以定位到那一行发生了内存泄露。用于检测 new 分配的内存
//#ifdef _DEBUG
//#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif
*/

//有用
inline void EnableMemLeakCheck()
{
	//该语句在程序退出时自动调用 _CrtDumpMemoryLeaks(),用于多个退出出口的情况.
	//如果只有一个退出位置，可以在程序退出之前调用 _CrtDumpMemoryLeaks()
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

	//按以下方法测试二叉树/字典树, 先生成随机输入然后测试, 每次都调用一组函数
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

	//_CrtDumpMemoryLeaks(); //这个代码好像会输出额外多余的内存分配信息;
	
	//mptr::mAutoPtr_unittest();
	//mptr::mScopedPtr_unittest();
	//mptr::mSharedPtr_unittest();

	mptr::mWeakPtr_unittest();

	return 0;
}
