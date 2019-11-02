#include "MinRefills.hpp"

using namespace std;

//Greedy, reach the gasstation as far as you can
//O(n)
void minRefills(int cap, vector<int> gasS)
{
	int res = 0;
	int curIndex = 0;
	while(curIndex < (int)gasS.size() - 1)
	{
		int lastIndex = curIndex;
		while(curIndex < ((int)gasS.size() - 1) && (gasS[curIndex + 1] - gasS[lastIndex]) <= cap)
			curIndex++;
		if (curIndex == lastIndex)
		{
			cout << "IMPOSSIBLE" << endl;
			return;
		}
		if (curIndex < ((int)gasS.size() - 1))
			res++;
	}
	cout << "refill " << res << " times" << endl;
}

void minRefillsInterface()
{
	cout << "carFuel:" << endl;
	int capacity = 100;
	vector<int> gasStations;
	for (int i = 1; i < 200; ++i)
	{
		gasStations.emplace_back(49*i + 2);
	}
	estimateFuncTime(minRefills, capacity, gasStations);
}

