#include "RabinKarp.hpp"

static size_t RabinKarpHashPOLX = 7;

static size_t RabinKarpHash(string s)
{
	size_t res = 0;
	size_t x = 1;
	for (auto& iters : s)
	{
		res += iters * x;
		x *= RabinKarpHashPOLX;
	}
	return res;
}

/*
 * 在str中找pattern, 返回数组:内容是从str中找到的与pattern相同的子串的起始坐标
 */
vector<size_t> RabinKarp(string const& str, string const& pattern)
{
	size_t tarSize = pattern.size();
	size_t tarHash = RabinKarpHash(pattern);
	vector<size_t> strHashes;
	vector<size_t> res;
	size_t lastPOLX = (size_t)pow(RabinKarpHashPOLX, tarSize - 1);
	size_t preHash = RabinKarpHash(str.substr(0, tarSize));

	if (preHash == tarHash && str.substr(0, tarSize) == pattern) res.emplace_back(0);

	for (size_t startLoc = 1; startLoc <= str.size() - tarSize; ++startLoc)
	{
		preHash -= str[startLoc - 1];
		assert((preHash % RabinKarpHashPOLX) == 0);
		preHash /= RabinKarpHashPOLX;
		preHash += lastPOLX * str[startLoc + tarSize - 1];
		if (preHash == tarHash && str.substr(0, tarSize) == pattern) res.emplace_back(startLoc);
	}
	return res;
}

void RabinKarpInterface()
{
	vector<size_t> res = RabinKarp("abaabaabab", "ab");
	for (auto& iterres : res) cout << iterres << " ";
}
