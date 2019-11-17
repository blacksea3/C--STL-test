#include "tarjanUGedge.hpp"

/*
 * tarjanUGedge内部DFS
 * 输入 std::vector<std::vector<bool>> const& graph 图
 * std::vector<bool>& isInstack 是否在栈中
 * std::vector<int>& DFN, DFS访问顺序 std::vector<int>& LOW自己以及以其为根的子树中最小的DFS访问顺序值
 * int seq 当前访问顺序,
 *  int pren 当前节点, int root根节点, std::vector<pair<int, int>>& 割边结果
 */
void tarjanUGedgeDFS(std::vector<std::vector<int>> const& graph,
	std::vector<bool>& isInstack,
	std::vector<int>& DFN, std::vector<int>& LOW, int& seq,
	int pren, int parent, std::vector<vector<int>>& res)
{
	DFN[pren] = LOW[pren] = ++seq;
	isInstack[pren] = true;
	for (const auto& i : graph[pren])
	{
		if (i == parent) continue; //?存疑，原因未知

		if (!isInstack[i])  //从未访问过
		{
			tarjanUGedgeDFS(graph, isInstack, DFN, LOW, seq, i, pren, res);
			LOW[pren] = min(LOW[pren], LOW[i]);
			if (LOW[i] > DFN[pren])
			{
				res.emplace_back(vector<int>{ pren, i });
			}
		}
		else
		{
			LOW[pren] = min(LOW[pren], DFN[i]);
		}
	}
}

/*
 * tarjan求割边
 * 输入无向图
 * 输出分组后的强相连分量
 */
std::vector<vector<int>> tarjanUGedgeInterface(int n, std::vector<std::vector<int>> graph)
{
	std::vector<int> DFN(n, INT_MAX);
	std::vector<int> LOW(n, INT_MAX);
	std::vector<bool> isInstack(n, false);
	std::vector<vector<int>> res;
	int seq = 0;

	for (int i = 0; i < n; ++i)
	{
		if (DFN[i] == INT_MAX)
			tarjanUGedgeDFS(graph, isInstack, DFN, LOW, seq, i, i, res);
	}
	return res;
}

/*
 * 求强相连分量测试
 */
void tarjanUGedgeTest()
{
	std::vector<std::vector<int>> edges = { {0,1},{1,2},{1,4},{2,3},{3,4}, { 4,5 }, { 5,6 } };
	int points = 7;
	vector<vector<int>> graph(points, vector<int>{});
	for (auto& e : edges)
	{
		graph[e[0]].push_back(e[1]);
		graph[e[1]].push_back(e[0]);
	}
	std::vector<vector<int>> res = tarjanUGedgeInterface(points, graph);
	int i = 1;
}
