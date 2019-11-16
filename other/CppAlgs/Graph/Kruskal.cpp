#include "Kruskal.hpp"

/*
 * kruskal最小生成树
 * 输入边：每一行表示一个节点的无向边，内部每一个pair的first表示另一个节点，second表示消耗（非负）
 * 输出最小代价
 * 外部应当确保edges的某个子集能够形成连通图, 确保节点个数等于edges.size()，节点ID合法
 */
int kruskalInterface(vector<vector<pair<int, unsigned int>>> edges)
{
	//将边存放到multimap中, 键为边消耗，值为pair<int, int>{start, end};
	multimap<unsigned int, pair<int, int>> mm;

	for (int i = 0; i < edges.size(); ++i)
	{
		for (auto& it : edges[i])
		{
			mm.insert(pair<unsigned int, pair<int, int>>{it.second, {i, it.first}});
		}
	}

	//使用并查集
	mLib::mvector<int> mv;
	for (int i = 0; i < edges.size(); ++i)
	{
		mv.push_back(i);
	}
	mLib::mDisjoint<int> mdj(mv);

	int res = 0;
	for (auto& itermm : mm)
	{
		int st = itermm.second.first;
		int en = itermm.second.second;
		if (mdj.Find(st) != mdj.Find(en))
		{
			res += itermm.first;
			mdj.Union(st, en);
		}
	}
	return res;
}

void kruskalTest()
{
	const unsigned int INF = 0x1f1f1f1f;
	vector<vector<pair<int, unsigned int>>> edges = {
		{ {1,4},{4,1},{5,2}},
		{ {0,4},{2,8},{3,6},{4,5} },
		{ {1,8},{3,1} },
		{{1,6},{2,1},{4,9}},
	    {{0,1},{1,5},{3,9},{5,3} },
		{{0,2},{4,3}}
	};
	int res = kruskalInterface(edges);
	int i = 1;
}
