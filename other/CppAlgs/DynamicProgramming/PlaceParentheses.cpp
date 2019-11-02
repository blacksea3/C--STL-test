#include "../public/public.hpp"

using namespace std;

//放置括号,
//对于一个字符串表达式: d1 op1 d2 op2... d(n-1) op(n-1) dn
//返回通过放置括号在特定位置能得到的最大值, 括号数量==(n-1)
//例如: 1 - 2 * 3, 可以放((1 - 2) * 3) = -1, 或者(1 - (2*3)) = -5, 那么返回-1
//保证输入合法, 没有空格, 只有数字和+ - *, 开头结尾都是数字, 数字不会int溢出, 数字默认都是正的
int PlaceParentheses(string& s)
{
	//格式化s
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
