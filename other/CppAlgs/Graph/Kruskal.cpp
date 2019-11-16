#include "Kruskal.hpp"

/*
 * kruskal��С������
 * ����ߣ�ÿһ�б�ʾһ���ڵ������ߣ��ڲ�ÿһ��pair��first��ʾ��һ���ڵ㣬second��ʾ���ģ��Ǹ���
 * �����С����
 * �ⲿӦ��ȷ��edges��ĳ���Ӽ��ܹ��γ���ͨͼ, ȷ���ڵ��������edges.size()���ڵ�ID�Ϸ�
 */
int kruskalInterface(vector<vector<pair<int, unsigned int>>> edges)
{
	//���ߴ�ŵ�multimap��, ��Ϊ�����ģ�ֵΪpair<int, int>{start, end};
	multimap<unsigned int, pair<int, int>> mm;

	for (int i = 0; i < edges.size(); ++i)
	{
		for (auto& it : edges[i])
		{
			mm.insert(pair<unsigned int, pair<int, int>>{it.second, {i, it.first}});
		}
	}

	//ʹ�ò��鼯
	mLib::mvector<int> mv;
	for (int i = 0; i < edges.size(); ++i)
	{
		mv.push_back(i);
	}
	mLib::mDisjoint<int> mdj(mv);

	int res = 0;
	for (auto& itermm : mm)
	{
		int st = itermm.second.first;
		int en = itermm.second.second;
		if (mdj.Find(st) != mdj.Find(en))
		{
			res += itermm.first;
			mdj.Union(st, en);
		}
	}
	return res;
}

void kruskalTest()
{
	const unsigned int INF = 0x1f1f1f1f;
	vector<vector<pair<int, unsigned int>>> edges = {
		{ {1,4},{4,1},{5,2}},
		{ {0,4},{2,8},{3,6},{4,5} },
		{ {1,8},{3,1} },
		{{1,6},{2,1},{4,9}},
	    {{0,1},{1,5},{3,9},{5,3} },
		{{0,2},{4,3}}
	};
	int res = kruskalInterface(edges);
	int i = 1;
}
