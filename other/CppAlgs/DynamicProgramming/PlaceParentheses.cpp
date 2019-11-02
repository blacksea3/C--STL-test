#include "../public/public.hpp"

using namespace std;

//��������,
//����һ���ַ������ʽ: d1 op1 d2 op2... d(n-1) op(n-1) dn
//����ͨ�������������ض�λ���ܵõ������ֵ, ��������==(n-1)
//����: 1 - 2 * 3, ���Է�((1 - 2) * 3) = -1, ����(1 - (2*3)) = -5, ��ô����-1
//��֤����Ϸ�, û�пո�, ֻ�����ֺ�+ - *, ��ͷ��β��������, ���ֲ���int���, ����Ĭ�϶�������
int PlaceParentheses(string& s)
{
	//��ʽ��s
	vector<int> num;
	vector<char> op;
	string pre;
	for (auto& iter : s)
	{
		if (isdigit(iter))
		{
			pre.push_back(iter);
		}
		else
		{
			num.emplace_back(stoi(pre));
			pre = "";
			op.emplace_back(iter);
		}
	}
	num.emplace_back(stoi(pre));

	int nSize = num.size();
	vector<vector<int>> dpmin(nSize, vector<int>(nSize, 0));
	vector<vector<int>> dpmax(nSize, vector<int>(nSize, 0));
	//init
	for (int i = 0; i < nSize; ++i)
	{
		dpmin[i][i] = num[i];
		dpmax[i][i] = num[i];
	}
	//expand
	for (int len = 2; len <= nSize; ++len)
	{
		for (int st = 0, en = st + len - 1; en < nSize; ++st, ++en)
		{
			dpmin[st][en] = INT_MAX;
			dpmax[st][en] = INT_MIN;
			for (int mid = st; mid <= en - 1; ++mid)
			{
				switch (op[mid])
				{
				case '+':
				{
					dpmin[st][en] = min(dpmin[st][mid] + dpmin[mid + 1][en], dpmin[st][en]);
					dpmax[st][en] = max(dpmax[st][mid] + dpmax[mid + 1][en], dpmax[st][en]);
					break;
				}
				case '-':
				{
					dpmin[st][en] = min(dpmin[st][mid] - dpmax[mid + 1][en], dpmin[st][en]);
					dpmax[st][en] = max(dpmax[st][mid] - dpmin[mid + 1][en], dpmax[st][en]);
					break;
				}
				case '*':
				{
					dpmin[st][en] = min(dpmin[st][mid] * dpmin[mid + 1][en], dpmin[st][en]);
					dpmin[st][en] = min(dpmin[st][mid] * dpmax[mid + 1][en], dpmin[st][en]);
					dpmin[st][en] = min(dpmax[st][mid] * dpmin[mid + 1][en], dpmin[st][en]);
					dpmin[st][en] = min(dpmax[st][mid] * dpmax[mid + 1][en], dpmin[st][en]);
					dpmax[st][en] = max(dpmin[st][mid] * dpmin[mid + 1][en], dpmax[st][en]);
					dpmax[st][en] = max(dpmin[st][mid] * dpmax[mid + 1][en], dpmax[st][en]);
					dpmax[st][en] = max(dpmax[st][mid] * dpmin[mid + 1][en], dpmax[st][en]);
					dpmax[st][en] = max(dpmax[st][mid] * dpmax[mid + 1][en], dpmax[st][en]);
				}
				default:
					break;
				}
				
			}
		}
	}
	return dpmax[0][nSize - 1];
}

void PlaceParenthesesInterface(string& s)
{
	cout << "s:" << s << endl;
	cout << "max res:" << PlaceParentheses(s);
}

/*
int main()
{
	string s = "1+2-3*4-5";
	PlaceParenthesesInterface(s);
}
*/
