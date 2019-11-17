#include "tarjanUGNode.hpp"

/*
 * tarjanUGNode�ڲ�DFS
 * ���� std::vector<std::vector<bool>> const& graph ͼ
 * std::vector<bool>& isInstack �Ƿ���ջ��, std::stack<int>& st DFS����ջ
 * std::vector<int>& DFN, DFS����˳�� std::vector<int>& LOW�Լ��Լ�����Ϊ������������С��DFS����˳��ֵ
 * int seq ��ǰ����˳��,
 *  int pren ��ǰ�ڵ�, int root���ڵ�, std::vector<int>& �����
 */
void tarjanUGNodeDFS(std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isInstack, std::stack<int>& st,
	std::vector<int>& DFN, std::vector<int>& LOW, int& seq,
	int pren, int root, std::vector<int>& res)
{
	DFN[pren] = LOW[pren] = ++seq;
	st.push(pren);
	isInstack[pren] = true;
	int flag = 0;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (!isInstack[i])  //��δ���ʹ�
			{
				tarjanUGNodeDFS(graph, isInstack, st, DFN, LOW, seq, i, root, res);
				LOW[pren] = min(LOW[pren], LOW[i]);
				if (LOW[i] >= DFN[pren])
				{
					flag++;
					if (pren != root || flag > 1) res.emplace_back(pren);
				}
			}
			else          //��ǰ���ʹ�
			{
				LOW[pren] = min(LOW[pren], DFN[i]);
			}
		}
	}
}

/*
 * tarjan����
 * ��������ͼ
 * ���������ǿ��������
 */
std::vector<int> tarjanUGNodeInterface(std::vector<std::vector<bool>> graph)
{
	int gSize = graph.size();
	std::vector<int> DFN(gSize, INT_MAX);
	std::vector<int> LOW(gSize, INT_MAX);
	std::vector<bool> isInstack(gSize, false);
	std::stack<int> st;
	std::vector<int> res;
	int seq = 0;

	for (int i = 0; i < gSize; ++i)
	{
		if (DFN[i] == INT_MAX)
			tarjanUGNodeDFS(graph, isInstack, st, DFN, LOW, seq, i, i, res);
	}
	return res;
}

/*
 * ��ǿ������������
 */
void tarjanUGNodeTest()
{
	std::vector<std::vector<int>> edges = { {0,1},{1,2},{1,4},{2,3},{3,4},{4,5},{5,6} };
	int points = 7;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edges)
	{
		graph[e[0]][e[1]] = true;
		graph[e[1]][e[0]] = true;
	}
	std::vector<int> res = tarjanUGNodeInterface(graph);
	int i = 1;
}
