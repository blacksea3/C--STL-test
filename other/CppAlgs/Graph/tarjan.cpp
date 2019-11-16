#include "tarjan.hpp"

/*
 * tarjan�ڲ�DFS
 * ���� std::vector<std::vector<bool>> const& graph ͼ
 * std::vector<bool>& isInstack �Ƿ���ջ��, std::stack<int>& st DFS����ջ
 * std::vector<int>& DFN, DFS����˳�� std::vector<int>& LOW�Լ��Լ�����Ϊ������������С��DFS����˳��ֵ
 * int seq ��ǰ����˳��, 
 *  int pren ��ǰ�ڵ�, std::vector<std::vector<int>>& resǿ��ͨ����������
 */
void tarjanDFS(std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isInstack, std::stack<int>& st,
	std::vector<int>& DFN, std::vector<int>& LOW, int& seq,
	int pren, std::vector<std::vector<int>>& res)
{
	DFN[pren] = LOW[pren] = ++seq;
	st.push(pren);
	isInstack[pren] = true;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (DFN[i] == INT_MAX)  //��δ���ʹ�
			{
				tarjanDFS(graph, isInstack, st, DFN, LOW, seq, i, res);
				LOW[pren] = min(LOW[pren], LOW[i]);
			}
			else if(isInstack[i])   //��ǰ���ʹ�
			{
				LOW[pren] = min(LOW[pren], DFN[i]);
			}
		}
	}
	//������: ����ڵ���ǿ��ͨ�����ĸ� ��ջ�нڵ�pop������ֱ����ǰ�ڵ㱻pop��������Ϊһ��ǿ��ͨ����
	if (DFN[pren] == LOW[pren])
	{
		vector<int> tempres;
		while (true)
		{
			int pr = st.top();
			st.pop();
			tempres.emplace_back(pr);
			isInstack[pr] = false;
			if (pr == pren) break;
		}
		res.emplace_back(tempres);
	}
}

/*
 * tarjan��ǿ���������ӿ�
 * ��������ͼ
 * ���������ǿ��������
 */
std::vector<std::vector<int>> tarjanSCCInterface(std::vector<std::vector<bool>> graph)
{
	int gSize = graph.size();
	std::vector<int> DFN(gSize, INT_MAX);
	std::vector<int> LOW(gSize, INT_MAX);
	std::vector<bool> isInstack(gSize, false);
	std::stack<int> st;
	std::vector<std::vector<int>> res;
	int seq = 0;

	for (int i = 0; i < gSize; ++i)
	{
		if (DFN[i] == INT_MAX)
			tarjanDFS(graph, isInstack, st, DFN, LOW, seq, i, res);
	}
	return res;
}

/*
 * ��ǿ������������
 */
void tarjansCCTest()
{
	std::vector<std::vector<int>> edges = { {1,2},{2,4},{1,3},{3,4},{4,1},{4,5},{6,5},
	{6,7},{7,6},{1,7},{8,7},{9,8},{9,2} };
	int points = 10;
	vector<vector<bool>> graph(points, vector<bool>(points, false));
	for (auto& e : edges)
	{
		graph[e[0]][e[1]] = true;
	}
	std::vector<std::vector<int>> res = tarjanSCCInterface(graph);
	int i = 1;
}
