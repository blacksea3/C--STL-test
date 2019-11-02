#include "../public/public.hpp"

//weights and values are the same size, one weight and one value means one item
//NOT allows Repetition!
int KnapsackNoRepetition(vector<int>& weights, vector<int>& values, int capacity)
{
	int itemSize = weights.size();
	vector<vector<int>> dp(capacity + 1, vector<int>(itemSize + 1, 0));
	for (int i = 1; i <= itemSize; ++i)
	{
		for (int w = 1; w <= capacity; ++w)
		{
			dp[w][i] = dp[w][i - 1];
			if (w >= weights[i - 1])
				dp[w][i] = max(dp[w][i], dp[w - weights[i - 1]][i - 1] + values[i - 1]);
		}
	}
	return dp[capacity][itemSize];
}

void KnapsackNoRepetitionInterface(vector<int>& weights, vector<int>& values, int capacity)
{
	cout << "not allow repetition" << endl;
	cout << "weights:";
	for (auto& w : weights) cout << " " << w;
	cout << endl;
	cout << "values:";
	for (auto& v : values) cout << " " << v;
	cout << endl;
	cout << "capacity:" << capacity << endl;
	cout << "res:" << KnapsackNoRepetition(weights, values, capacity);
}

//weights and values are the same size, one weight and one value means one item
//allows Repetition
int KnapsackRepetition(vector<int>& weights, vector<int>& values, int capacity)
{
	vector<int> dp(capacity + 1, 0);
	for (int i = 1; i <= capacity; ++i)
	{
		for (int j = 0; j < weights.size(); ++j)
		{
			if ((i - weights[j]) >= 0)
			{
				dp[i] = max(dp[i], dp[i - weights[j]] + values[j]);
			}
		}
	}
	return dp[capacity];
}

void KnapsackRepetitionInterface(vector<int>& weights, vector<int>& values, int capacity)
{
	cout << "allow repetition" << endl;
	cout << "weights:";
	for (auto& w : weights) cout << " " << w;
	cout << endl;
	cout << "values:";
	for (auto& v : values) cout << " " << v;
	cout << endl;
	cout << "capacity:" << capacity << endl;
	cout << "res:" << KnapsackRepetition(weights, values, capacity);
}

/*
int main()
{
	vector<int> weights = { 6,4,3,2 };
	vector<int> values = { 30,16,14,9 };
	int capacity = 10;
	KnapsackNoRepetitionInterface(weights, values, capacity);
	return 0;
}
*/
