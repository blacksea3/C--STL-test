#include "strongConnectedComponents.hpp"

/*
 * 强相连分量内部内部DFS
 * 输入 std::vector<int>& postOrder 后序顺序，std::vector<std::vector<bool>> const& graph 图
 * std::vector<bool>& isVisited 访问标记, int pren当前节点
 */
void sCCsDFS(std::vector<int>& postOrder, std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isVisited, int pren)
{
	isVisited[pren] = true;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (!isVisited[i]) sCCsDFS(postOrder, graph, isVisited, i);
		}
	}
	postOrder.emplace_back(pren);
}

/*
 * 反向图+双DFS 求强相连分量接口
 * 输入图
 * 输出分组后的强相连分量
 */
std::vector<std::vector<int>> sCCsInterface(std::vector<std::vector<bool>> graph)
{
	std::vector<int> postOrder;
	std::vector<bool> isVisited(graph.size(), false);
	//生成反向图
	std::vector<std::vector<bool>> revG(graph.size(), std::vector<bool>(graph.size(), false));
	for (int i = 0; i < graph.size(); ++i)
	{
		for (int j = 0; j < graph.size(); ++j)
		{
			if (graph[i][j]) revG[j][i] = true;
		}
	}
	//主DFS
	int preNode = 0;
	while (preNode < graph.size())
	{
		if (!isVisited[preNode])
			sCCsDFS(postOrder, revG, isVisited, preNode);
		preNode++;
	}
	//反序postOrder 再次DFS 获得结果
	std::reverse(postOrder.begin(), postOrder.end());
	std::vector<int> dumpPostOrder;
	int preLoc = 0;
	std::vector<std::vector<int>> res;
	for (int i = 0; i < isVisited.size(); ++i) isVisited[i] = false;
	while (preLoc < graph.size())
	{
		if (!isVisited[postOrder[preLoc]])
		{
			std::vector<bool> cpisVisited = isVisited;
			sCCsDFS(dumpPostOrder, graph, isVisited, postOrder[preLoc]);
			std::vector<int> tempre;
			for (int i = 0; i < cpisVisited.size(); ++i)
				if (cpisVisited[i] != isVisited[i])
					tempre.emplace_back(i);
			res.emplace_back(tempre);
		}
		preLoc++;
	}
	return res;
}

/*
 * 求强相连分量测试
 */
void sCCsTest()
{
	std::vector<std::vector<int>> edges = { {1,2},{2,4},{1,3},{3,4},{4,1},{4,5},{6,5},
	{6,7},{7,6},{1,7},{8,7},{9,8},{9,2} };
	int points = 10;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edges)
	{
		graph[e[0]][e[1]] = true;
	}
	std::vector<std::vector<int>> res = sCCsInterface(graph);
	int i = 1;
}
