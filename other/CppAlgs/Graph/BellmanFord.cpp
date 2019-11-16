#include "BellmanFord.hpp"
#include "BFS.hpp"



/*
 * 重建最短路径start->i(BellmanFord使用)
 * 特别注意此时可能已经有负权环了
 * 输入开始节点、目标节点和先导节点数组
 * 输出数组：开始节点到目标节点经过的所有节点序号
 */
vector<int> ReconstructPathBF(int st, int tar, vector<int> prev)
{
	vector<int> res;
	res.emplace_back(tar);
	int cptar = prev[tar];
	while (cptar != st && cptar != tar)
	{
		res.emplace_back(cptar);
		cptar = prev[cptar];
	}
	res.emplace_back(st);
	reverse(res.begin(), res.end());
	return res;
}

/*
 * BellmanFord接口
 * 输入图/开始节点/结束节点, 图为有向图，可能有负环，输出开始到结束的最小值
 * 对于输入graph, 值大于10000就认为未连接
 * 输出：两个pair, 外层的first为true表示可到达，后面的pair有用， 否则false不可到达后面的pair为空
 * 一个pair: 如果开始到结束最小值有限则true+路径，如果无穷小则false+路径（路径中插入“某一个”负环）
 */
pair<bool, pair<bool, vector<int>>> BellmanFordInterface(vector<vector<signed int>> graph, int start, int end)
{
	const signed int UNCONNECTED = 10000;

	int pSize = graph.size();
	vector<int> distance(pSize, 0x1f1f1f1f);
	vector<int> prev(pSize, -1);
	distance[start] = 0;

	//先V-1次迭代，原始BellmanFord算法
	for (int i = 1; i < pSize; ++i)
	{
		//对所有edge尝试松弛操作
		for (int stp = 0; stp < pSize; ++stp)
		{
			for (int enp = 0; enp < pSize; ++enp)
			{
				if ((graph[stp][enp] < UNCONNECTED) && (distance[enp] > distance[stp] + graph[stp][enp]))
				{
					distance[enp] = distance[stp] + graph[stp][enp];
					prev[enp] = stp;
				}
			}
		}
	}
	if (prev[end] == -1) return { false,{} };

	//获得路径
	vector<int> path = ReconstructPathBF(start, end, prev);

	//然后判断是否有负权回路，方法是再一次迭代
	vector<int> vnegStartPoint;
	for (int stp = 0; stp < pSize; ++stp)
	{
		for (int enp = 0; enp < pSize; ++enp)
		{
			if ((graph[stp][enp] < UNCONNECTED) && (distance[enp] > distance[stp] + graph[stp][enp]))
			{
				vnegStartPoint.emplace_back(enp);
			}
		}
	}

	if (vnegStartPoint.empty())  //无负权回路
	{
		return { true,{true, path } };
	}
	else  //判断负权回路是否会影响结果, 既然qnegStartPoint中的节点的distance被修改说明它们是可以被start到达的
	{
		//多源BFS查看qnegStartPoint中的节点是否可到达end
		vector<vector<bool>> graph2(pSize, vector<bool>(pSize, false));
		for (int stp = 0; stp < pSize; ++stp)
		{
			for (int enp = 0; enp < pSize; ++enp)
			{
				if (graph[stp][enp] < UNCONNECTED) graph2[stp][enp] = true;
			}
		}
		pair<vector<int>, vector<int>> res = multipleBFSInterface(graph2, vnegStartPoint);
		if (res.first[end] == INT_MAX)  //end不可由负权环到达
		{
			return { true,{ true, path } };
		}
		else  //end可由负权环到达，复现负权环
		{
			vector<int> endpath = ReconstructPathmBFS(end, res.second);
			int importantP = endpath[0];  //获得负权环起始点
			//从prev中得到负权环
			vector<int> midpath;
			int preP = prev[importantP];
			while (preP != importantP)
			{
				midpath.emplace_back(preP);
				preP = prev[preP];
			}
			reverse(midpath.begin(), midpath.end());
			//然后对原始起始点作start，来一次单源BFS获得startpath, 注意这个路径并不一定是start->importantP最优
			//但不影响结果，因为有负权环
			pair<vector<int>, vector<int>> stres = BFSInterface(graph2, start);
			vector<int> stpath = ReconstructPathBFS(start, importantP, stres.second);

			//合并三段path
			//注意：stpath和endpath都包括importantP, 而midpath首尾都没有importantP
			vector<int> totalpath;
			totalpath.insert(totalpath.end(), stpath.begin(), stpath.end());
			totalpath.insert(totalpath.end(), midpath.begin(), midpath.end());
			totalpath.insert(totalpath.end(), endpath.begin(), endpath.end());
			return { true,{ false, totalpath } };
		}
	}
}

void BFTest()
{
	const signed int INF = 10000;
	vector<vector<signed int>> graph = { 
		{INF, 2, INF, INF, INF},
		{INF, INF, INF, 3, INF},
		{INF, 3, INF, INF, INF},
		{INF, INF, INF, INF, -10},
		{INF, 5, INF, INF, INF},
	};
	pair<bool, pair<bool, vector<int>>> res = BellmanFordInterface(graph, 0, 1);
}
