#include "tarjan.hpp"

/*
 * tarjan内部DFS
 * 输入 std::vector<std::vector<bool>> const& graph 图
 * std::vector<bool>& isInstack 是否在栈中, std::stack<int>& st DFS访问栈
 * std::vector<int>& DFN, DFS访问顺序 std::vector<int>& LOW自己以及以其为根的子树中最小的DFS访问顺序值
 * int seq 当前访问顺序, 
 *  int pren 当前节点, std::vector<std::vector<int>>& res强连通分量分组结果
 */
void tarjanDFS(std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isInstack, std::stack<int>& st,
	std::vector<int>& DFN, std::vector<int>& LOW, int& seq,
	int pren, std::vector<std::vector<int>>& res)
{
	DFN[pren] = LOW[pren] = ++seq;
	st.push(pren);
	isInstack[pren] = true;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (DFN[i] == INT_MAX)  //从未访问过
			{
				tarjanDFS(graph, isInstack, st, DFN, LOW, seq, i, res);
				LOW[pren] = min(LOW[pren], LOW[i]);
			}
			else if(isInstack[i])   //当前访问过
			{
				LOW[pren] = min(LOW[pren], DFN[i]);
			}
		}
	}
	//到这里: 如果节点是强连通分量的根 把栈中节点pop出来，直到当前节点被pop出来了作为一组强连通分量
	if (DFN[pren] == LOW[pren])
	{
		vector<int> tempres;
		while (true)
		{
			int pr = st.top();
			st.pop();
			tempres.emplace_back(pr);
			isInstack[pr] = false;
			if (pr == pren) break;
		}
		res.emplace_back(tempres);
	}
}

/*
 * tarjan求强相连分量接口
 * 输入有向图
 * 输出分组后的强相连分量
 */
std::vector<std::vector<int>> tarjanSCCInterface(std::vector<std::vector<bool>> graph)
{
	int gSize = graph.size();
	std::vector<int> DFN(gSize, INT_MAX);
	std::vector<int> LOW(gSize, INT_MAX);
	std::vector<bool> isInstack(gSize, false);
	std::stack<int> st;
	std::vector<std::vector<int>> res;
	int seq = 0;

	for (int i = 0; i < gSize; ++i)
	{
		if (DFN[i] == INT_MAX)
			tarjanDFS(graph, isInstack, st, DFN, LOW, seq, i, res);
	}
	return res;
}

/*
 * 求强相连分量测试
 */
void tarjansCCTest()
{
	std::vector<std::vector<int>> edges = { {1,2},{2,4},{1,3},{3,4},{4,1},{4,5},{6,5},
	{6,7},{7,6},{1,7},{8,7},{9,8},{9,2} };
	int points = 10;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edges)
	{
		graph[e[0]][e[1]] = true;
	}
	std::vector<std::vector<int>> res = tarjanSCCInterface(graph);
	int i = 1;
}
