#include "../public/public.hpp"

//time: min of (O(m*n) and O(mlogm), m=changes.size(), n=total
int DPchange(vector<int>& changes, int total)
{
	vector<int> v(total + 1, 0);
	sort(changes.begin(), changes.end());

	for (int i = 1; i <= total; ++i)
	{
		int pre = INT_MAX;
		for (auto& change : changes)
		{
			if ((i - change) < 0) break;
			else
			{
				pre = min(pre, v[i - change] + 1);
			}
		}
		v[i] = pre;
	}
	return v[total];
}

void DPChangeInterface(vector<int>& changes, int total)
{
	cout << "changes:";
	for (auto& c : changes) cout << " " << c;
	cout << endl << "total:" << total << endl;
	cout << "res:" << DPchange(changes, total);
}

/*
int main()
{
	vector<int> changes = { 5,1,6 };
	int total = 9;
	DPChangeInterface(changes, total);
	return 0;
}
*/
