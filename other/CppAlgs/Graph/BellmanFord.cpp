#include "BellmanFord.hpp"
#include "BFS.hpp"



/*
 * �ؽ����·��start->i(BellmanFordʹ��)
 * �ر�ע���ʱ�����Ѿ��и�Ȩ����
 * ���뿪ʼ�ڵ㡢Ŀ��ڵ���ȵ��ڵ�����
 * ������飺��ʼ�ڵ㵽Ŀ��ڵ㾭�������нڵ����
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
 * BellmanFord�ӿ�
 * ����ͼ/��ʼ�ڵ�/�����ڵ�, ͼΪ����ͼ�������и����������ʼ����������Сֵ
 * ��������graph, ֵ����10000����Ϊδ����
 * ���������pair, ����firstΪtrue��ʾ�ɵ�������pair���ã� ����false���ɵ�������pairΪ��
 * һ��pair: �����ʼ��������Сֵ������true+·�����������С��false+·����·���в��롰ĳһ����������
 */
pair<bool, pair<bool, vector<int>>> BellmanFordInterface(vector<vector<signed int>> graph, int start, int end)
{
	const signed int UNCONNECTED = 10000;

	int pSize = graph.size();
	vector<int> distance(pSize, 0x1f1f1f1f);
	vector<int> prev(pSize, -1);
	distance[start] = 0;

	//��V-1�ε�����ԭʼBellmanFord�㷨
	for (int i = 1; i < pSize; ++i)
	{
		//������edge�����ɳڲ���
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

	//���·��
	vector<int> path = ReconstructPathBF(start, end, prev);

	//Ȼ���ж��Ƿ��и�Ȩ��·����������һ�ε���
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

	if (vnegStartPoint.empty())  //�޸�Ȩ��·
	{
		return { true,{true, path } };
	}
	else  //�жϸ�Ȩ��·�Ƿ��Ӱ����, ��ȻqnegStartPoint�еĽڵ��distance���޸�˵�������ǿ��Ա�start�����
	{
		//��ԴBFS�鿴qnegStartPoint�еĽڵ��Ƿ�ɵ���end
		vector<vector<bool>> graph2(pSize, vector<bool>(pSize, false));
		for (int stp = 0; stp < pSize; ++stp)
		{
			for (int enp = 0; enp < pSize; ++enp)
			{
				if (graph[stp][enp] < UNCONNECTED) graph2[stp][enp] = true;
			}
		}
		pair<vector<int>, vector<int>> res = multipleBFSInterface(graph2, vnegStartPoint);
		if (res.first[end] == INT_MAX)  //end�����ɸ�Ȩ������
		{
			return { true,{ true, path } };
		}
		else  //end���ɸ�Ȩ��������ָ�Ȩ��
		{
			vector<int> endpath = ReconstructPathmBFS(end, res.second);
			int importantP = endpath[0];  //��ø�Ȩ����ʼ��
			//��prev�еõ���Ȩ��
			vector<int> midpath;
			int preP = prev[importantP];
			while (preP != importantP)
			{
				midpath.emplace_back(preP);
				preP = prev[preP];
			}
			reverse(midpath.begin(), midpath.end());
			//Ȼ���ԭʼ��ʼ����start����һ�ε�ԴBFS���startpath, ע�����·������һ����start->importantP����
			//����Ӱ��������Ϊ�и�Ȩ��
			pair<vector<int>, vector<int>> stres = BFSInterface(graph2, start);
			vector<int> stpath = ReconstructPathBFS(start, importantP, stres.second);

			//�ϲ�����path
			//ע�⣺stpath��endpath������importantP, ��midpath��β��û��importantP
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
