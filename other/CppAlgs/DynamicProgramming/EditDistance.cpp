#include "../public/public.hpp"

//return all min editdistance of two string s1[0:i] and s2[0:j]
vector<vector<int>> EditDistance(string& s1, string& s2)
{
	int s1Size = s1.size();
	int s2Size = s2.size();
	vector<vector<int>> dp(s1Size + 1, vector<int>(s2Size + 1, 0));

	//init
	for (int i = 1; i <= s1Size; ++i) dp[i][0] = i;
	for (int j = 1; j <= s2Size; ++j) dp[0][j] = j;

	for (int i = 1; i <= s1Size; ++i)
	{
		for (int j = 1; j <= s2Size; ++j)
		{
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
			if (s1[i - 1] == s2[j - 1]) dp[i][j] = min(dp[i - 1][j - 1], dp[i][j]);
			else dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i][j]);
		}
	}
	return dp;
}

void EditDistanceInterface(string& s1, string& s2)
{
	cout << "input s1:" << s1 << " s2:" << s2 << endl;
	vector<vector<int>> res = EditDistance(s1, s2);
	cout << "Editance:" << endl;
	for (auto& row : res)
	{
		cout << "  ";
		for (auto& v : row) cout << v << " ";
		cout << endl;
	}
	
	cout << "optimal two strings:" << endl;
	int indexOne = s1.size();
	int indexTwo = s2.size();

	string afs1;
	string afs2;

	while (indexOne > 0 && indexTwo > 0)
	{
		if ((res[indexOne][indexTwo - 1] < res[indexOne - 1][indexTwo - 1]) &&
			(res[indexOne][indexTwo - 1] < res[indexOne - 1][indexTwo]))
		{
			afs1.push_back('-');
			afs2.push_back(s2[indexTwo - 1]);
			indexTwo--;
		}
		else if ((res[indexOne - 1][indexTwo] < res[indexOne - 1][indexTwo - 1]) &&
			(res[indexOne - 1][indexTwo] < res[indexOne][indexTwo - 1]))
		{
			afs1.push_back(s1[indexTwo - 1]);
			afs2.push_back('-');
			indexOne--;
		}
		else
		{
			afs1.push_back(s1[indexOne - 1]);
			afs2.push_back(s2[indexTwo - 1]);
			indexOne--;
			indexTwo--;
		}
	}
	reverse(afs1.begin(), afs1.end());
	reverse(afs2.begin(), afs2.end());
	cout << afs1 << endl << afs2 << endl;
}

/*
int main()
{
	string s1 = "ATCGA";
	string s2 = "AATCGCA";
	EditDistanceInterface(s1, s2);
	return 0;
}
*/
