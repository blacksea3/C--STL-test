#include "BFS.hpp"

/*
 * BFS�ӿ�
 * ����ͼ�Ϳ�ʼ�ڵ�
 * ���pair:first�����ڵ㵽��ʼ�ڵ�����·���Լ�second���нڵ���ȵ��ڵ���ţ���ʼ�ڵ���ȵ��ڵ����Ϊ-1��
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
 * �ؽ����·��start->i
 * ���뿪ʼ�ڵ㡢Ŀ��ڵ���ȵ��ڵ�����
 * ������飺��ʼ�ڵ㵽Ŀ��ڵ㾭�������нڵ����
 */
vector<int> ReconstructPath(int st, int tar, vector<int> prev)
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

void BFSTest()
{
	vector<vector<int>> edge = { {0,1},{0,2},{1,2},{2,3} };
	int points = 4;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edge) graph[e[0]][e[1]] = true;
	pair<vector<int>, vector<int>> res = BFSInterface(graph, 0);
	vector<int> path = ReconstructPath(0, 3, res.second);
	int i = 1;
}
