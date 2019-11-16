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
#include "Graph/strongConnectedComponents.hpp"
//#include "Graph/BFS.hpp"
//#include "Graph/dijkstra.hpp"
//#include "Graph/BellmanFord.hpp"
//#include "Graph/Kruskal.hpp"
//#include "Graph//Prim.hpp"
#include "Graph/tarjan.hpp"

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
	sCCsTest();
	//BFSTest();
	//dijkstraTest();
	//BFTest();
	//kruskalTest();
	//primTest();
	tarjansCCTest();

	return 0;
}
