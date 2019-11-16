#include "Prim.hpp"

/*
 * Prim��С������
 * ����ߣ�ÿһ�б�ʾһ���ڵ������ߣ��ڲ�ÿһ��pair��first��ʾ��һ���ڵ㣬second��ʾ���ģ��Ǹ���
 * �����С����
 * �ⲿӦ��ȷ��edges��ĳ���Ӽ��ܹ��γ���ͨͼ, ȷ���ڵ��������edges.size()���ڵ�ID�Ϸ�
 */
int PrimInterface(vector<vector<pair<int, unsigned int>>> edges)
{
	//ʵ���϶���ͷ���ǰ���{���·������Ӧ�ڵ��}��pair��ʹ��Ĭ��greater ��pair������ʽ
	priority_queue<pair<unsigned int, pair<int, int>>, vector<pair<unsigned int, pair<int, int>>>,
		greater<pair<unsigned int, pair<int, int>>>> q;  //�ŵ�ǰ���룬�ڵ���Ŷ�{start, end}��pair

	//ѡ��һ����ʼ��, Ϊ0, ��ʼ�����ȶ���

	for (auto& it:edges[0])
	{
		q.push({ it.second, {0, it.first} });
	}
	unordered_set<int> us;
	us.insert(0);

	int res = 0;
	while (!q.empty())
	{
		pair<unsigned int, pair<int, int>> tmp = q.top();   //ȡ����ǰ�����д�ʹ�õ����·���Ľڵ�
		q.pop();

		if (us.find(tmp.second.first) == us.end()) //���ڿ��Լ���tmp.second.first�ڵ�
		{
			int newadd = tmp.second.first;
			us.insert(newadd);
			res += tmp.first;
			for (auto& it : edges[newadd])
			{
				q.push({ it.second, {newadd, it.first} });
			}
		}
		else if (us.find(tmp.second.second) == us.end())
		{
			int newadd = tmp.second.second;
			us.insert(newadd);
			res += tmp.first;
			for (auto& it : edges[newadd])
			{
				q.push({ it.second, {newadd, it.first} });
			}
		}
	}
	return res;
}

void primTest()
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
	int res = PrimInterface(edges);
	int i = 1;
}
