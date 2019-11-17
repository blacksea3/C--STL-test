#include "tarjanUGNode.hpp"

/*
 * tarjanUGNode内部DFS
 * 输入 std::vector<std::vector<bool>> const& graph 图
 * std::vector<bool>& isInstack 是否在栈中, std::stack<int>& st DFS访问栈
 * std::vector<int>& DFN, DFS访问顺序 std::vector<int>& LOW自己以及以其为根的子树中最小的DFS访问顺序值
 * int seq 当前访问顺序,
 *  int pren 当前节点, int root根节点, std::vector<int>& 割点结果
 */
void tarjanUGNodeDFS(std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isInstack, std::stack<int>& st,
	std::vector<int>& DFN, std::vector<int>& LOW, int& seq,
	int pren, int root, std::vector<int>& res)
{
	DFN[pren] = LOW[pren] = ++seq;
	st.push(pren);
	isInstack[pren] = true;
	int flag = 0;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (!isInstack[i])  //从未访问过
			{
				tarjanUGNodeDFS(graph, isInstack, st, DFN, LOW, seq, i, root, res);
				LOW[pren] = min(LOW[pren], LOW[i]);
				if (LOW[i] >= DFN[pren])
				{
					flag++;
					if (pren != root || flag > 1) res.emplace_back(pren);
				}
			}
			else          //当前访问过
			{
				LOW[pren] = min(LOW[pren], DFN[i]);
			}
		}
	}
}

/*
 * tarjan求割点
 * 输入无向图
 * 输出分组后的强相连分量
 */
std::vector<int> tarjanUGNodeInterface(std::vector<std::vector<bool>> graph)
{
	int gSize = graph.size();
	std::vector<int> DFN(gSize, INT_MAX);
	std::vector<int> LOW(gSize, INT_MAX);
	std::vector<bool> isInstack(gSize, false);
	std::stack<int> st;
	std::vector<int> res;
	int seq = 0;

	for (int i = 0; i < gSize; ++i)
	{
		if (DFN[i] == INT_MAX)
			tarjanUGNodeDFS(graph, isInstack, st, DFN, LOW, seq, i, i, res);
	}
	return res;
}

/*
 * 求强相连分量测试
 */
void tarjanUGNodeTest()
{
	std::vector<std::vector<int>> edges = { {0,1},{1,2},{1,4},{2,3},{3,4},{4,5},{5,6} };
	int points = 7;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edges)
	{
		graph[e[0]][e[1]] = true;
		graph[e[1]][e[0]] = true;
	}
	std::vector<int> res = tarjanUGNodeInterface(graph);
	int i = 1;
}
