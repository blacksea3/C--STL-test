#include "SuffixArray.hpp"

/*
 * �����ַ�
 * ����std::string raw
 * �����ÿ���ַ������Ľ�����������飬��ǰ����ֱ���Դ�ַ����±�λ
 */
std::vector<size_t> SortCharacters(std::string raw)
{
	size_t rSize = raw.size();
	std::vector<size_t> order(rSize, 0);
	std::vector<size_t> count(256, 0);
	for (auto& i : raw) count[i]++;
	for (size_t i = 1; i < 256; ++i) count[i] += count[i - 1];
	for (int i = rSize - 1; i >= 0; --i)
	{
		char ch = raw[i];
		count[ch]--; 
		order[count[ch]] = i;
	}
	return order;
}

/*
 * ��ʼ���ַ����
 * ����std::string raw�ַ�����std::vector<size_t> ����
 * ����������
 */
std::vector<size_t> ComputeCharClasses(std::string raw, std::vector<size_t> order)
{
	size_t rSize = raw.size();
	std::vector<size_t> classes(rSize, 0);
	for (size_t i = 1; i < rSize; ++i)
	{
		if (raw[order[i]] == raw[order[i - 1]]) classes[order[i]] = classes[order[i - 1]];
		else classes[order[i]] = classes[order[i - 1]] + 1;
	}
	return classes;
}

/*
 * ���ȷ�����ò���ѭ������
 * ����std::string raw�ַ�����size_t L�����Ӧ���ȣ�std::vector<size_t> order����std::vector<size_t> classes�ַ�������
 * ���˫������2*L��������
 */
std::vector<size_t> SortDoubled(std::string raw, size_t L, std::vector<size_t> order, std::vector<size_t> classes)
{
	//��Ҫʹ���ȶ�����  
	size_t rSize = raw.size();
	std::vector<size_t> newOrder(rSize, 0);
	std::vector<size_t> count(rSize, 0);
	for (size_t i = 0; i < rSize; ++i) count[classes[i]]++;
	for (size_t i = 1; i < rSize; ++i) count[i] += count[i - 1];
	for (int i = rSize - 1; i >= 0; --i)
	{
		size_t newStart = (order[i] - L + rSize) % rSize;
		size_t cl = classes[newStart];
		count[cl]--;
		newOrder[count[cl]] = newStart;
	}
	return newOrder;
}

/*
 * �����ַ��������
 * ����size_t L�����Ӧ���ȣ�std::vector<size_t> order����std::vector<size_t> classes���ַ�������
 * ������ַ�������
 */
std::vector<size_t> UpdateClasses(size_t L, std::vector<size_t> order, std::vector<size_t> classes)
{
	size_t rSize = order.size();
	std::vector<size_t> newClasses(rSize, 0);
	for (size_t i = 1; i < rSize; ++i)
	{
		size_t cur = order[i]; size_t prev = order[i - 1];
		size_t midcur = (cur + L) % rSize; size_t midprev = (prev + L) % rSize;
		if (classes[cur] != classes[prev] || classes[midcur] != classes[midprev]) newClasses[cur] = newClasses[prev] + 1;
		else newClasses[cur] = newClasses[prev];
	}
	return newClasses;
}

/*
 * ���ɺ�׺����
 * ����: std::string raw
 * ע��: Դ�ַ������ַ�Ӧ��֤������$
 */
std::vector<size_t> BuildSuffixArray(std::string raw)
{
	raw.push_back('$');
	std::vector<size_t> order = SortCharacters(raw);
	std::vector<size_t> classes = ComputeCharClasses(raw, order);
	size_t L = 1;
	while (L < raw.size())
	{
		order = SortDoubled(raw, L, order, classes);
		classes = UpdateClasses(L, order, classes);
		L *= 2;
	}
	order.erase(order.begin());
	return order;
}

void SuffixArrayTest()
{
	std::vector<size_t> res = BuildSuffixArray("ababaa");
	std::cout << "The suffix of ababaa is: ";
	for (auto& r : res) std::cout << r << " ";
	std::cout << std::endl;
}
