#include "KMP.hpp"

/*
 * ����ǰ׺=��׺����, KMP�㷨ʹ��
 * �����ַ���std::string raw
 *  ע���ⲿӦ��ȷ��raw�ǿ�, ���򽫻����𻬻��Ĵ��� :)
 * �����Ӧ���ȵ�std:vector<size_t> res
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
 * ��raw����pattern����ȫƥ��
 * ����: std::string rawԴ�ַ���, std::string patternģʽ�ַ���
 * ע��: �ַ������ܰ���$
 * ���λ������
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
