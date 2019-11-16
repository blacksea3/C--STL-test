#include "dijkstra.hpp"

/*
 * dijkstra接口
 * 输入图和开始节点, 图为有向图，节点间距是非负数
 * 输出pair:first其他节点到开始节点的最短路径以及second所有节点的先导节点序号（开始节点的先导节点序号为-1）
 */
pair<vector<int>, vector<int>> dijkstraInterface(vector<vector<unsigned int>> graph, int start)
{
	vector<int> distance(graph.size(), INT_MAX);
	vector<int> prev(graph.size(), -1);
	distance[start] = 0;

	//实际上队列头部是包含{最短路径，对应节点}的pair，使用默认greater 对pair的排序方式
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;  //放当前距离，节点序号 pair
	q.push({ 0, start });
	while (!q.empty())
	{
		pair<int, int> tmp = q.top();   //取出当前队列中待使用的最短路径的节点
		q.pop();
		int pren = tmp.second;
		if (distance[pren] < tmp.first) //pren已经更短，无需松弛pren指出来的边
			continue;
		for (int i = 0; i < graph.size(); ++i)
		{
			if (distance[i] > distance[tmp.second] + graph[tmp.second][i])   //需要松弛这个路径
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
 * 重建最短路径start->i(dijkstra使用)
 * 输入开始节点、目标节点和先导节点数组
 * 输出数组：开始节点到目标节点经过的所有节点序号
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
