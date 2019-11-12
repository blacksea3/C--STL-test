#include "KMP.hpp"

/*
 * 计算前缀=后缀函数, KMP算法使用
 * 输入字符串std::string raw
 *  注意外部应当确保raw非空, 否则将会引起滑稽的错误 :)
 * 输出对应长度的std:vector<size_t> res
 */
std::vector<size_t> computePrefixFunction(std::string raw)
{
	size_t rSize = raw.size();
	std::vector<size_t> res(rSize);
	res[0] = 0;
	size_t border = 0;
	for (size_t index = 1; index < rSize; ++index)
	{
		while (border > 0 && raw[index] != raw[border])
			border = res[border - 1];
		if (raw[border] == raw[index])
			border = border + 1;
		else
			border = 0;
		res[index] = border;
	}
	return res;
}

/*
 * 对raw进行pattern的完全匹配
 * 输入: std::string raw源字符串, std::string pattern模式字符串
 * 注意: 字符串不能包含$
 * 输出位置数组
 */
std::vector<size_t> fullyLocationMatch(std::string raw, std::string pattern)
{
	std::vector<size_t> pf = computePrefixFunction(pattern + "$" + raw);
	std::vector<size_t> res;
	size_t pSize = pattern.size();
	for (size_t index = pSize + 1; index < pf.size(); ++index)
	{
		if (pf[index] == pSize) res.emplace_back(index - 2 * pSize);
	}
	return res;
}

void KMPtest()
{
	std::cout << "fully match location of (ana)pattern and (banana)rawstr is: ";
	std::vector<size_t> res = fullyLocationMatch("banana", "ana");
	for (auto& iterres : res) std::cout << iterres << " ";
	std::cout << std::endl;
}
