#include "BFS.hpp"

vector<int> BFSInterface(vector<vector<bool>> graph, int start)
{
	vector<int> distance(graph.size(), INT_MAX);
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
				}
		}
	}
	return distance;
}

void BFSTest()
{
	vector<vector<int>> edge = { {0,1},{0,2},{1,2},{2,3} };
	int points = 4;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edge) graph[e[0]][e[1]] = true;
	vector<int> res = BFSInterface(graph, 0);
	int i = 1;
}
