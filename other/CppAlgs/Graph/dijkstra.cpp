#include "dijkstra.hpp"

/*
 * dijkstra�ӿ�
 * ����ͼ�Ϳ�ʼ�ڵ�, ͼΪ����ͼ���ڵ����ǷǸ���
 * ���pair:first�����ڵ㵽��ʼ�ڵ�����·���Լ�second���нڵ���ȵ��ڵ���ţ���ʼ�ڵ���ȵ��ڵ����Ϊ-1��
 */
pair<vector<int>, vector<int>> dijkstraInterface(vector<vector<unsigned int>> graph, int start)
{
	vector<int> distance(graph.size(), INT_MAX);
	vector<int> prev(graph.size(), -1);
	distance[start] = 0;

	//ʵ���϶���ͷ���ǰ���{���·������Ӧ�ڵ�}��pair��ʹ��Ĭ��greater ��pair������ʽ
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;  //�ŵ�ǰ���룬�ڵ���� pair
	q.push({ 0, start });
	while (!q.empty())
	{
		pair<int, int> tmp = q.top();   //ȡ����ǰ�����д�ʹ�õ����·���Ľڵ�
		q.pop();
		int pren = tmp.second;
		if (distance[pren] < tmp.first) //pren�Ѿ����̣������ɳ�prenָ�����ı�
			continue;
		for (int i = 0; i < graph.size(); ++i)
		{
			if (distance[i] > distance[tmp.second] + graph[tmp.second][i])   //��Ҫ�ɳ����·��
			{
				distance[i] = distance[tmp.second] + graph[tmp.second][i];
				q.push({ distance[i] , i });
				prev[i] = tmp.second;
			}
		}
	}
	return { distance, prev };
}

/*
 * �ؽ����·��start->i(dijkstraʹ��)
 * ���뿪ʼ�ڵ㡢Ŀ��ڵ���ȵ��ڵ�����
 * ������飺��ʼ�ڵ㵽Ŀ��ڵ㾭�������нڵ����
 */
vector<int> ReconstructPathdij(int st, int tar, vector<int> prev)
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

void dijkstraTest()
{
	const unsigned int HALFMAX = 0x3f3f3f3f;
	vector<vector<unsigned int>> graph = { 
		{HALFMAX, 200, 10, HALFMAX, 100},
	    {HALFMAX, HALFMAX, HALFMAX, HALFMAX, HALFMAX},
		{HALFMAX, HALFMAX, HALFMAX, 10, HALFMAX},
		{HALFMAX, HALFMAX, HALFMAX, HALFMAX, 10},
		{HALFMAX, HALFMAX, HALFMAX, HALFMAX, HALFMAX}
	};

	pair<vector<int>, vector<int>> res = dijkstraInterface(graph, 0);
	vector<int> path = ReconstructPathdij(0, 4, res.second);
	int i = 1;
}
