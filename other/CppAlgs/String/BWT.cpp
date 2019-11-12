#include "BWT.hpp"

/*
 * ���BWT�ַ���
 * ����std::string Դ�ַ���
 *   ������Դ�ַ�������Сд��ĸ, ���һ��ģ�Դ�ַ�����ASCII��С��$
 * ���std::string ת�����Ŀ���ַ���
 * ʱ��: O(n^2*logn), �ռ�O(n^2)
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
 * �ӻ��BWT�ַ������Դ�ַ���
 * ����std::string Ӧ����genBWTString�������ɵ�BWT�ַ���
 *   ������BWT�ַ�������Сд��ĸ, ���һ��ģ�BWT�ַ�����ASCII��С��$
 * ���std::string ת�����Դ�ַ���
 */
std::string getRawStringWithBWTString(std::string bwtStr)
{
	std::vector<std::pair<char, int>> lastChWithLocation;  //�ڲ�Ԫ��: first���ַ�, second��ǰ��������ĳ��ֵĴ���, ��0��ʼ
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

	std::vector<int> firstOccurLocation(256, 0);   //��¼ĳ���ַ��״γ��ֵ�location
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
 * ͨ��BWTת��, �ж�Դ�ַ�������pattern�ַ����ĸ���
 * ����std::string raw Դ�ַ���, std::string pattern�ַ���
 *   ������Դ�ַ�������Сд��ĸ, ���һ��ģ�BWT�ַ�����ASCII��С��$
 * ���ƥ��"����"
 */
int BWTmatching(std::string raw, std::string pattern)
{
	//Ԥ����: BWT�ַ��������������һ�����һ�еĹ�ϵ
	std::string BWTString = genBWTString(raw);

	std::vector<std::pair<char, int>> lastChWithLocation;  //�ڲ�Ԫ��: first���ַ�, second��ǰ��������ĳ��ֵĴ���, ��0��ʼ
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

	std::vector<int> firstOccurLocation(256, 0);   //��¼ĳ���ַ��״γ��ֵ�location
	char oldCh = '$' - 1;
	for (size_t index = 0; index < sortLastChWithLocation.size(); ++index)
	{
		if (sortLastChWithLocation[index].first != oldCh)
		{
			firstOccurLocation[sortLastChWithLocation[index].first] = index;
			oldCh = sortLastChWithLocation[index].first;
		}
	}

	//��ʼƥ��
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




