#include "tarjanUGedge.hpp"

/*
 * tarjanUGedge�ڲ�DFS
 * ���� std::vector<std::vector<bool>> const& graph ͼ
 * std::vector<bool>& isInstack �Ƿ���ջ��
 * std::vector<int>& DFN, DFS����˳�� std::vector<int>& LOW�Լ��Լ�����Ϊ������������С��DFS����˳��ֵ
 * int seq ��ǰ����˳��,
 *  int pren ��ǰ�ڵ�, int root���ڵ�, std::vector<pair<int, int>>& ��߽��
 */
void tarjanUGedgeDFS(std::vector<std::vector<int>> const& graph,
	std::vector<bool>& isInstack,
	std::vector<int>& DFN, std::vector<int>& LOW, int& seq,
	int pren, int parent, std::vector<vector<int>>& res)
{
	DFN[pren] = LOW[pren] = ++seq;
	isInstack[pren] = true;
	for (const auto& i : graph[pren])
	{
		if (i == parent) continue; //?���ɣ�ԭ��δ֪

		if (!isInstack[i])  //��δ���ʹ�
		{
			tarjanUGedgeDFS(graph, isInstack, DFN, LOW, seq, i, pren, res);
			LOW[pren] = min(LOW[pren], LOW[i]);
			if (LOW[i] > DFN[pren])
			{
				res.emplace_back(vector<int>{ pren, i });
			}
		}
		else
		{
			LOW[pren] = min(LOW[pren], DFN[i]);
		}
	}
}

/*
 * tarjan����
 * ��������ͼ
 * ���������ǿ��������
 */
std::vector<vector<int>> tarjanUGedgeInterface(int n, std::vector<std::vector<int>> graph)
{
	std::vector<int> DFN(n, INT_MAX);
	std::vector<int> LOW(n, INT_MAX);
	std::vector<bool> isInstack(n, false);
	std::vector<vector<int>> res;
	int seq = 0;

	for (int i = 0; i < n; ++i)
	{
		if (DFN[i] == INT_MAX)
			tarjanUGedgeDFS(graph, isInstack, DFN, LOW, seq, i, i, res);
	}
	return res;
}

/*
 * ��ǿ������������
 */
void tarjanUGedgeTest()
{
	std::vector<std::vector<int>> edges = { {0,1},{1,2},{1,4},{2,3},{3,4}, { 4,5 }, { 5,6 } };
	int points = 7;
	vector<vector<int>> graph(points, vector<int>{});
	for (auto& e : edges)
	{
		graph[e[0]].push_back(e[1]);
		graph[e[1]].push_back(e[0]);
	}
	std::vector<vector<int>> res = tarjanUGedgeInterface(points, graph);
	int i = 1;
}
