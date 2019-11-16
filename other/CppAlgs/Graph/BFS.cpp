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
 * ��ԴBFS�ӿ�
 * ����ͼ�Ϳ�ʼ�ڵ�
 * ���pair:first�����ڵ㵽��ʼ�ڵ�����·���Լ�second���нڵ���ȵ��ڵ���ţ���ʼ�ڵ���ȵ��ڵ����Ϊ-1��
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
 * �ؽ����·��start->i(BellmanFordʹ��2����ԴBFS֮��ʹ��)
 * ����Ŀ��ڵ���ȵ��ڵ�����
 * ������飺��ʼ�ڵ㵽Ŀ��ڵ㾭�������нڵ����
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
