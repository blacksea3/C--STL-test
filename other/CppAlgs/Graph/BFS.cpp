#include "BFS.hpp"

/*
 * BFS接口
 * 输入图和开始节点
 * 输出pair:first其他节点到开始节点的最短路径以及second所有节点的先导节点序号（开始节点的先导节点序号为-1）
 */
pair<vector<int>, vector<int>> BFSInterface(vector<vector<bool>> graph, int start)
{
	vector<int> distance(graph.size(), INT_MAX);
	vector<int> prev(graph.size(), -1);
	distance[start] = 0;

	queue<int> q;
	q.push(start);
	while (!q.empty())
	{
		int tmp = q.front();
		q.pop();
		for (int i = 0; i < graph.size(); ++i)
		{
			if (graph[tmp][i])
				if (distance[i] == INT_MAX)
				{
					q.push(i);
					distance[i] = distance[tmp] + 1;
					prev[i] = tmp;
				}
		}
	}
	return { distance, prev };
}

/*
 * 重建最短路径start->i
 * 输入开始节点、目标节点和先导节点数组
 * 输出数组：开始节点到目标节点经过的所有节点序号
 */
vector<int> ReconstructPathBFS(int st, int tar, vector<int> prev)
{
	vector<int> res;
	while (tar != st)
	{
		res.emplace_back(tar);
		tar = prev[tar];
	}
	res.emplace_back(st);
	reverse(res.begin(), res.end());
	return res;
}

/*
 * 多源BFS接口
 * 输入图和开始节点
 * 输出pair:first其他节点到开始节点的最短路径以及second所有节点的先导节点序号（开始节点的先导节点序号为-1）
 */
pair<vector<int>, vector<int>> multipleBFSInterface(vector<vector<bool>> graph, vector<int> start)
{
	vector<int> distance(graph.size(), INT_MAX);
	vector<int> prev(graph.size(), -1);
	queue<int> q;
	for (auto& s : start)
	{
		distance[s] = 0;
		q.push(s);
	}

	while (!q.empty())
	{
		int tmp = q.front();
		q.pop();
		for (int i = 0; i < graph.size(); ++i)
		{
			if (graph[tmp][i])
				if (distance[i] == INT_MAX)
				{
					q.push(i);
					distance[i] = distance[tmp] + 1;
					prev[i] = tmp;
				}
		}
	}
	return { distance, prev };
}

/*
 * 重建最短路径start->i(BellmanFord使用2，多源BFS之后使用)
 * 输入目标节点和先导节点数组
 * 输出数组：开始节点到目标节点经过的所有节点序号
 */
vector<int> ReconstructPathmBFS(int tar, vector<int> prev)
{
	vector<int> res;
	while (tar != -1)
	{
		res.emplace_back(tar);
		tar = prev[tar];
	}
	reverse(res.begin(), res.end());
	return res;
}

void BFSTest()
{
	vector<vector<int>> edge = { {0,1},{0,2},{1,2},{2,3} };
	int points = 4;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edge) graph[e[0]][e[1]] = true;
	pair<vector<int>, vector<int>> res = BFSInterface(graph, 0);
	vector<int> path = ReconstructPathBFS(0, 3, res.second);
	int i = 1;
}
