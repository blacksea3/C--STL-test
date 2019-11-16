#include "Prim.hpp"

/*
 * Prim最小生成树
 * 输入边：每一行表示一个节点的无向边，内部每一个pair的first表示另一个节点，second表示消耗（非负）
 * 输出最小代价
 * 外部应当确保edges的某个子集能够形成连通图, 确保节点个数等于edges.size()，节点ID合法
 */
int PrimInterface(vector<vector<pair<int, unsigned int>>> edges)
{
	//实际上队列头部是包含{最短路径，对应节点对}的pair，使用默认greater 对pair的排序方式
	priority_queue<pair<unsigned int, pair<int, int>>, vector<pair<unsigned int, pair<int, int>>>,
		greater<pair<unsigned int, pair<int, int>>>> q;  //放当前距离，节点序号对{start, end}的pair

	//选择一个起始点, 为0, 初始化优先队列

	for (auto& it:edges[0])
	{
		q.push({ it.second, {0, it.first} });
	}
	unordered_set<int> us;
	us.insert(0);

	int res = 0;
	while (!q.empty())
	{
		pair<unsigned int, pair<int, int>> tmp = q.top();   //取出当前队列中待使用的最短路径的节点
		q.pop();

		if (us.find(tmp.second.first) == us.end()) //现在可以加入tmp.second.first节点
		{
			int newadd = tmp.second.first;
			us.insert(newadd);
			res += tmp.first;
			for (auto& it : edges[newadd])
			{
				q.push({ it.second, {newadd, it.first} });
			}
		}
		else if (us.find(tmp.second.second) == us.end())
		{
			int newadd = tmp.second.second;
			us.insert(newadd);
			res += tmp.first;
			for (auto& it : edges[newadd])
			{
				q.push({ it.second, {newadd, it.first} });
			}
		}
	}
	return res;
}

void primTest()
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
	int res = PrimInterface(edges);
	int i = 1;
}
