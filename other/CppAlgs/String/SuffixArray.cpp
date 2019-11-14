#include "SuffixArray.hpp"

/*
 * 排序单字符
 * 输入std::string raw
 * 输出对每个字符排序后的结果，放入数组，从前到后分别是源字符的下标位
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
 * 初始化字符类别
 * 输入std::string raw字符串，std::vector<size_t> 排序
 * 输出类别数组
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
 * 长度翻倍获得部分循环排序
 * 输入std::string raw字符串，size_t L排序对应长度，std::vector<size_t> order排序，std::vector<size_t> classes字符类别分组
 * 输出双倍长度2*L排序数组
 */
std::vector<size_t> SortDoubled(std::string const& raw, size_t L, std::vector<size_t> const& order, std::vector<size_t> const& classes)
{
	//需要使用稳定排序  
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
 * 更新字符类别数组
 * 输入size_t L排序对应长度，std::vector<size_t> order排序，std::vector<size_t> classes旧字符类别分组
 * 输出新字符类别分组
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
 * 生成后缀数组
 * 输入: std::string raw
 * 注意: 源字符串的字符应保证都大于$
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
 * 求相邻后缀字符串的LCP
 * 输入: std::vector<size_t> s 字符串, size_t i和j 位置， equal已知的LCP一定大于等于这个值
 * 输出int lcp
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
 * 反转后缀数组
 * 输入: std::vector<size_t> order 后缀数组
 * 输出反转后的后缀数组，后缀规则看代码
 */
std::vector<size_t> InvertSuffixArray(std::vector<size_t> order)
{
	std::vector<size_t> pos(order.size());
	for (size_t i = 0; i < order.size(); ++i) pos[order[i]] = i;
	return pos;
}

/*
 * 生成LCP数组
 * 输入: std::string s字符串，std::vector<size_t> order 后缀数组
 */
std::vector<int> ComputeLCPArray(std::string s, std::vector<size_t> order)
{
	size_t sSize = s.size();
	std::vector<int> lcpArray(sSize - 1); //每两个相邻的后缀数组的LCP，放入此数组
	int lcp = 0;
	std::vector<size_t> posInOrder = InvertSuffixArray(order);
	size_t suffix = order[0];
	for (int i = 0; i < sSize; ++i)
	{
		//先求相邻后缀字符串的首字符位置
		size_t orderIndex = posInOrder[suffix];
		if (orderIndex == sSize - 1)  //到末尾了，更新sufix，重置lcp
		{
			lcp = 0;
			suffix = (suffix + 1) % sSize;
			continue;
		}
		size_t nextSuffix = order[orderIndex + 1];
		//通过上一次lcp求这一次的
		lcp = LCPOfSuffixs(s, suffix, nextSuffix, lcp - 1);
		lcpArray[orderIndex] = lcp;
		//更新sufix
		suffix = (suffix + 1) % sSize;
	}
	return lcpArray;
}

/*
 * 后缀树节点
 */
struct SuffixTreeNode
{
	SuffixTreeNode* parent;
	std::map<char, SuffixTreeNode*> children;
	int stringDepth;  //根节点到此节点的字符串长度
	int edgeStart;    //父亲节点到此节点的边在总字符串中的起始下标
	int edgeEnd;      //父亲节点到此节点的边在总字符串中的结束下标
	SuffixTreeNode(SuffixTreeNode* p, 
		std::map<char, SuffixTreeNode*> chi,
		int sd, int es, int ee) : parent(p), children(chi),
		stringDepth(sd), edgeStart(es), edgeEnd(ee)
	{
		;
	}
};

/*
 * 在当前节点上创键新叶子节点
 * 输入 SuffixTreeNode* curNode当前节点，
 * std::string s 字符串，size_t suffix 将要创建的节点对应的后缀字符串的起始下标
 */
SuffixTreeNode* CreateNewLeaf(SuffixTreeNode* curNode, std::string s, size_t suffix)
{
	SuffixTreeNode* leaf = new SuffixTreeNode(curNode, {}, 
		s.size() - suffix, suffix + curNode->stringDepth, s.size() - 1);
	curNode->children[s[leaf->edgeStart]] = leaf;
	return leaf;
}

/*
 * 切边，
 * 输入 SuffixTreeNode* curNode 边的起始节点，std::string s 字符串
 * int edgeStart ？，int offset ？
 * std::string s 字符串，size_t suffix 将要创建的节点对应的后缀字符串的起始下标
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
 * 后缀数组转后缀树
 * 输入std::string s 字符串, std::vector<size_t> order后缀数组
 * std::vector<int> lcpArray lcp数组
 * 输出后缀树根节点
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
		if (curNode->stringDepth == lcpPrev) //直接新建节点
			curNode = CreateNewLeaf(curNode, s, suffix);
		else //需要切边
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
