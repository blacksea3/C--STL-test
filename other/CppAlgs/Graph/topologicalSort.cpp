#include "topologicalSort.hpp"

/*
 * ���������ڲ�DFS
 * ���� std::vector<int>& reverseRes ��������std::vector<std::vector<bool>> const& graph ͼ
 * std::vector<bool>& isVisited ���ʱ�ǣ�bool& isCyclic �Ƿ��⵽��
 * std::vector<bool>& isPath ������·��, int pren��ǰ�ڵ�
 */
void topologicalSortDFS(std::vector<int>& reverseRes, std::vector<std::vector<bool>> const& graph,
	std::vector<bool>& isVisited, bool& isCyclic, std::vector<bool>& isPath, int pren)
{
	if (isCyclic) return;
	isVisited[pren] = true;
	isPath[pren] = true;
	for (int i = 0; i < graph[pren].size(); ++i)
	{
		if (graph[pren][i])
		{
			if (isPath[i])
			{
				isCyclic = true;
				return;
			}
			if (!isVisited[i]) topologicalSortDFS(reverseRes, graph, isVisited,
				isCyclic, isPath, i);
		}
	}
	isPath[pren] = false;
	reverseRes.emplace_back(pren);
}

/*
 * ��������
 * ����std::vector<std::vector<bool>> graph ͼ, Ӧ����������ͬ
 * ���std::vector<int>����������DAG�����޻�ͼ��ͼ�ǿ������ǿգ�����Ϊ��
 */
std::vector<int> topologicalSortInterface(std::vector<std::vector<bool>> graph)
{
	std::vector<int> reverseRes;
	std::vector<bool> isVisited(graph.size(), false);
	std::vector<bool> isPath(graph.size(), false);
	bool isCyclic = false;
	int preNode = 0;
	while (preNode < graph.size())
	{
		if (!isVisited[preNode])
			topologicalSortDFS(reverseRes, graph, isVisited,
				isCyclic, isPath, preNode);
		if (isCyclic) break;
		preNode++;
	}
	if (isCyclic) return std::vector<int>{};
	else
	{
		std::reverse(reverseRes.begin(), reverseRes.end());
		return reverseRes;
	}
}

void topologicalSortTest()
{
	int numCourses = 2;
	vector<vector<int>> prerequisites = { {1, 0} };

	vector<vector<bool>> graph(numCourses, vector<bool>(numCourses, false));
	for (auto& prere : prerequisites)
	{
		graph[prere[1]][prere[0]] = true;
	}
	vector<int> res = topologicalSortInterface(graph);
	int i = 1;
}
