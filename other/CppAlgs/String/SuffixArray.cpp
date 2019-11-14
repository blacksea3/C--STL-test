#include "SuffixArray.hpp"

/*
 * �����ַ�
 * ����std::string raw
 * �����ÿ���ַ������Ľ�����������飬��ǰ����ֱ���Դ�ַ����±�λ
 */
std::vector<size_t> SortCharacters(std::string const& raw)
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
std::vector<size_t> ComputeCharClasses(std::string const& raw, std::vector<size_t> const& order)
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
std::vector<size_t> SortDoubled(std::string const& raw, size_t L, std::vector<size_t> const& order, std::vector<size_t> const& classes)
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
std::vector<size_t> UpdateClasses(size_t L, std::vector<size_t> const& order, std::vector<size_t> const& classes)
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
	//order.erase(order.begin());
	return order;
}

/*
 * �����ں�׺�ַ�����LCP
 * ����: std::vector<size_t> s �ַ���, size_t i��j λ�ã� equal��֪��LCPһ�����ڵ������ֵ
 * ���int lcp
 */
int LCPOfSuffixs(std::string s, size_t i, size_t j, int equal)
{
	int lcp = max(0, equal);
	while ((i + lcp) < s.size() && (j + lcp) < s.size())
	{
		if (s[i + lcp] == s[j + lcp]) lcp++;
		else break;
	}
	return lcp;
}

/*
 * ��ת��׺����
 * ����: std::vector<size_t> order ��׺����
 * �����ת��ĺ�׺���飬��׺���򿴴���
 */
std::vector<size_t> InvertSuffixArray(std::vector<size_t> order)
{
	std::vector<size_t> pos(order.size());
	for (size_t i = 0; i < order.size(); ++i) pos[order[i]] = i;
	return pos;
}

/*
 * ����LCP����
 * ����: std::string s�ַ�����std::vector<size_t> order ��׺����
 */
std::vector<int> ComputeLCPArray(std::string s, std::vector<size_t> order)
{
	size_t sSize = s.size();
	std::vector<int> lcpArray(sSize - 1); //ÿ�������ڵĺ�׺�����LCP�����������
	int lcp = 0;
	std::vector<size_t> posInOrder = InvertSuffixArray(order);
	size_t suffix = order[0];
	for (int i = 0; i < sSize; ++i)
	{
		//�������ں�׺�ַ��������ַ�λ��
		size_t orderIndex = posInOrder[suffix];
		if (orderIndex == sSize - 1)  //��ĩβ�ˣ�����sufix������lcp
		{
			lcp = 0;
			suffix = (suffix + 1) % sSize;
			continue;
		}
		size_t nextSuffix = order[orderIndex + 1];
		//ͨ����һ��lcp����һ�ε�
		lcp = LCPOfSuffixs(s, suffix, nextSuffix, lcp - 1);
		lcpArray[orderIndex] = lcp;
		//����sufix
		suffix = (suffix + 1) % sSize;
	}
	return lcpArray;
}

/*
 * ��׺���ڵ�
 */
struct SuffixTreeNode
{
	SuffixTreeNode* parent;
	std::map<char, SuffixTreeNode*> children;
	int stringDepth;  //���ڵ㵽�˽ڵ���ַ�������
	int edgeStart;    //���׽ڵ㵽�˽ڵ�ı������ַ����е���ʼ�±�
	int edgeEnd;      //���׽ڵ㵽�˽ڵ�ı������ַ����еĽ����±�
	SuffixTreeNode(SuffixTreeNode* p, 
		std::map<char, SuffixTreeNode*> chi,
		int sd, int es, int ee) : parent(p), children(chi),
		stringDepth(sd), edgeStart(es), edgeEnd(ee)
	{
		;
	}
};

/*
 * �ڵ�ǰ�ڵ��ϴ�����Ҷ�ӽڵ�
 * ���� SuffixTreeNode* curNode��ǰ�ڵ㣬
 * std::string s �ַ�����size_t suffix ��Ҫ�����Ľڵ��Ӧ�ĺ�׺�ַ�������ʼ�±�
 */
SuffixTreeNode* CreateNewLeaf(SuffixTreeNode* curNode, std::string s, size_t suffix)
{
	SuffixTreeNode* leaf = new SuffixTreeNode(curNode, {}, 
		s.size() - suffix, suffix + curNode->stringDepth, s.size() - 1);
	curNode->children[s[leaf->edgeStart]] = leaf;
	return leaf;
}

/*
 * �бߣ�
 * ���� SuffixTreeNode* curNode �ߵ���ʼ�ڵ㣬std::string s �ַ���
 * int edgeStart ����int offset ��
 * std::string s �ַ�����size_t suffix ��Ҫ�����Ľڵ��Ӧ�ĺ�׺�ַ�������ʼ�±�
 */
SuffixTreeNode* BreakEdge(SuffixTreeNode* curNode, std::string s,
	int edgeStart, int offset)
{
	char startChar = s[edgeStart];
	char midChar = s[edgeStart + offset];
	SuffixTreeNode* midNode = new SuffixTreeNode(curNode, {},
		curNode->stringDepth + offset, edgeStart, edgeStart + offset - 1);
	midNode->children[midChar] = curNode->children[startChar];
	curNode->children[startChar]->parent = midNode;
	curNode->children[startChar]->edgeStart += offset;
	curNode->children[startChar] = midNode;
	return midNode;
}

/*
 * ��׺����ת��׺��
 * ����std::string s �ַ���, std::vector<size_t> order��׺����
 * std::vector<int> lcpArray lcp����
 * �����׺�����ڵ�
 */
SuffixTreeNode* STFromSA(std::string s, std::vector<size_t> order,
	std::vector<int> lcpArray)
{
	SuffixTreeNode* root = new SuffixTreeNode(nullptr, {}, 0, -1, -1);
	int lcpPrev = 0;
	SuffixTreeNode* curNode = root;
	for (int i = 0; i < s.size(); ++i)
	{
		size_t suffix = order[i];
		while (curNode->stringDepth > lcpPrev)
			curNode = curNode->parent;
		if (curNode->stringDepth == lcpPrev) //ֱ���½��ڵ�
			curNode = CreateNewLeaf(curNode, s, suffix);
		else //��Ҫ�б�
		{
			int edgeStart = order[i - 1] + curNode->stringDepth;
			int offset = lcpPrev - curNode->stringDepth;
			SuffixTreeNode* midNode = BreakEdge(curNode, s, edgeStart, offset);
			curNode = CreateNewLeaf(midNode, s, suffix);
		}
		if (i < (s.size() - 1))
			lcpPrev = lcpArray[i];
	}
	return root;
}

void dfsSuffixTree(std::string& raw, 
	std::vector<std::string>& total, SuffixTreeNode* pren,
	std::string pres)
{
	pres += raw.substr(pren->edgeStart, pren->edgeEnd - pren->edgeStart + 1);
	if (pren->children.empty()) total.emplace_back(pres);
	else
	{
		for (auto& c : pren->children)
			dfsSuffixTree(raw, total, c.second, pres);
	}
}

void SuffixArrayTest()
{
	std::string raw = "ababaa";

	std::vector<size_t> order = BuildSuffixArray(raw);
	std::cout << "The suffix of ababaa is: ";
	for (auto& r : order) std::cout << r << " ";
	std::cout << std::endl;

	std::cout << "The LCPArray of ababaa is: ";
	std::vector<int> lcpa = ComputeLCPArray(raw + "$", order);
	for (auto& r : lcpa) std::cout << r << " ";
	std::cout << std::endl;

	SuffixTreeNode* root = STFromSA(raw + "$", order, lcpa);
	std::vector<std::string> total;
	for (auto& c:root->children) dfsSuffixTree(raw, total, c.second, "");
	std::cout << "The suffix strings of ababaa is:\n";
	for (auto& t : total) std::cout << t << std::endl;
}
