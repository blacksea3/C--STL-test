#include "graphMain.hpp"

/*
 * 拓扑排序内部DFS
 * 输入 std::vector<int>& reverseRes 反向结果，std::vector<std::vector<bool>> const& graph 图
 * std::vector<bool>& isVisited 访问标记，bool& isCyclic 是否检测到环
 * std::vector<bool>& isPath 经历的路径, int pren当前节点
 */
void topologicalSortDFS(std::vector<int>& reverseRes, std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isVisited, bool& isCyclic, std::vector<bool>& isPath, int pren)
{
	if (isCyclic) return;
	isVisited[pren] = true;
	isPath[pren] = true;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (isPath[i])
			{
				isCyclic = true;
				return;
			}
			if (!isVisited[i]) topologicalSortDFS(reverseRes, graph, isVisited,
				isCyclic, isPath, i);
		}
	}
	isPath[pren] = false;
	reverseRes.emplace_back(pren);
}

/*
 * 拓扑排序
 * 输入std::vector<std::vector<bool>> graph 图, 应当行列数相同
 * 输出std::vector<int>结果，如果是DAG有向无环图且图非空则结果非空，否则为空
 */
std::vector<int> topologicalSortInterface(std::vector<std::vector<bool>> graph)
{
	std::vector<int> reverseRes;
	std::vector<bool> isVisited(graph.size(), false);
	std::vector<bool> isPath(graph.size(), false);
	bool isCyclic = false;
	int preNode = 0;
	while (preNode < graph.size())
	{
		if (!isVisited[preNode])
			topologicalSortDFS(reverseRes, graph, isVisited,
				isCyclic, isPath, preNode);
		if (isCyclic) break;
		preNode++;
	}
	if (isCyclic) return std::vector<int>{};
	else
	{
		std::reverse(reverseRes.begin(), reverseRes.end());
		return reverseRes;
	}
}

void graphMainInterface()
{
	/*
	system(string("D:").c_str());
	system(string("cd /PC/GitFiles/Cpp-STL-test/other/CppAlgs/Graph").c_str());
	string command_rd = "python mainGraph.py";
	system(command_rd.c_str());
	*/
}
