#include "BWT.hpp"

/*
 * 获得BWT字符串
 * 输入std::string 源字符串
 *   理想下源字符串都是小写字母, 或更一般的，源字符串的ASCII都小于$
 * 输出std::string 转换后的目标字符串
 * 时间: O(n^2*logn), 空间O(n^2)
 */

std::string genBWTString(std::string raw)
{
	raw.push_back('$');
	size_t rawSize = raw.size();
	std::vector<std::string> allStr(rawSize);
	for (size_t index = 0; index < rawSize; ++index) allStr[index] = raw.substr(index) + raw.substr(0, index);
	std::sort(allStr.begin(), allStr.end());
	std::string res;
	for (size_t index = 0; index < rawSize; ++index) res.push_back(allStr[index].back());
	return res;
}

/*
 * 从获得BWT字符串获得源字符串
 * 输入std::string 应当是genBWTString函数生成的BWT字符串
 *   理想下BWT字符串都是小写字母, 或更一般的，BWT字符串的ASCII都小于$
 * 输出std::string 转换后的源字符串
 */
std::string getRawStringWithBWTString(std::string bwtStr)
{
	std::vector<std::pair<char, int>> lastChWithLocation;  //内部元素: first是字符, second是前面等于它的出现的次数, 从0开始
	std::vector<int> preOccurTimes(256, 0);
	for (auto& iters : bwtStr)
	{
		lastChWithLocation.emplace_back(std::pair<char, int>{iters, preOccurTimes[iters]});
		preOccurTimes[iters]++;
	}

	std::vector<std::pair<char, int>> sortLastChWithLocation(lastChWithLocation);
	std::sort(sortLastChWithLocation.begin(), sortLastChWithLocation.end(), 
		[](const std::pair<char, int>& p1, const std::pair<char, int>& p2) -> bool
	{
		if (p1.first < p2.first) return true;
		else if (p1.first > p2.first) return false;
		else return p1.second < p2.second;
	});

	std::vector<int> firstOccurLocation(256, 0);   //记录某个字符首次出现的location
	char oldCh = '$' - 1;
	for (size_t index = 0; index < sortLastChWithLocation.size(); ++index)
	{
		if (sortLastChWithLocation[index].first != oldCh)
		{
			firstOccurLocation[sortLastChWithLocation[index].first] = index;
			oldCh = sortLastChWithLocation[index].first;
		}
	}

	std::string reverseStr;
	size_t preIndex = 0;

	for (size_t tim = 0; tim < sortLastChWithLocation.size(); ++tim)
	{
		reverseStr.push_back(sortLastChWithLocation[preIndex].first);
		preIndex = firstOccurLocation[lastChWithLocation[preIndex].first] + lastChWithLocation[preIndex].second;
	}

	std::reverse(reverseStr.begin(), reverseStr.end());
	reverseStr.pop_back();
	return reverseStr;
}

/*
 * 通过BWT转换, 判断源字符串包含pattern字符串的个数
 * 输入std::string raw 源字符串, std::string pattern字符串
 *   理想下源字符串都是小写字母, 或更一般的，BWT字符串的ASCII都小于$
 * 输出匹配"个数"
 */
int BWTmatching(std::string raw, std::string pattern)
{
	//预处理: BWT字符串和其代表的最后一列与第一列的关系
	std::string BWTString = genBWTString(raw);

	std::vector<std::pair<char, int>> lastChWithLocation;  //内部元素: first是字符, second是前面等于它的出现的次数, 从0开始
	std::vector<int> preOccurTimes(256, 0);
	for (auto& iters : BWTString)
	{
		lastChWithLocation.emplace_back(std::pair<char, int>{iters, preOccurTimes[iters]});
		preOccurTimes[iters]++;
	}

	std::vector<std::pair<char, int>> sortLastChWithLocation(lastChWithLocation);
	std::sort(sortLastChWithLocation.begin(), sortLastChWithLocation.end(),
		[](const std::pair<char, int>& p1, const std::pair<char, int>& p2) -> bool
	{
		if (p1.first < p2.first) return true;
		else if (p1.first > p2.first) return false;
		else return p1.second < p2.second;
	});

	std::vector<int> firstOccurLocation(256, 0);   //记录某个字符首次出现的location
	char oldCh = '$' - 1;
	for (size_t index = 0; index < sortLastChWithLocation.size(); ++index)
	{
		if (sortLastChWithLocation[index].first != oldCh)
		{
			firstOccurLocation[sortLastChWithLocation[index].first] = index;
			oldCh = sortLastChWithLocation[index].first;
		}
	}

	//开始匹配
	size_t le = 0;
	size_t ri = sortLastChWithLocation.size() - 1;

	while (!pattern.empty())
	{
		char tarCh = pattern.back();
		pattern.pop_back();
		size_t nextLe = -1;
		size_t nextRi = -1;
		for (size_t index = le; index <= ri; ++index)
		{
			if (lastChWithLocation[index].first == tarCh)
			{
				if (nextLe == -1)
				{
					nextLe = index;
					nextRi = index;
				}
				else nextRi = index;
			}
		}
		if (nextLe == -1) return 0;
		else
		{
			le = firstOccurLocation[lastChWithLocation[nextLe].first] + lastChWithLocation[nextLe].second;
			ri = firstOccurLocation[lastChWithLocation[nextRi].first] + lastChWithLocation[nextRi].second;
		}
	}
	return ri - le + 1;
}

void BWTconversionTest()
{
	std::string s = "banana";
	std::string sBWT = genBWTString(s);
	std::cout << "banana's BWT: " << sBWT << std::endl;
	std::cout << "raw string: " << getRawStringWithBWTString(sBWT) << std::endl;
	std::cout << "the number of ana(pattern) in banana(rawstr) is: " << BWTmatching("banana", "ana") << std::endl;
}




