#include "Trie.hpp"

void Trie::postOrderDel(Trie::Node* n)
{
	if (!n) return;
	for (size_t i = 0; i < 256; ++i) this->postOrderDel(n->nexts[i]);
	delete n;
}

void Trie::getSuffixArray_pri(Trie::Node* n, std::vector<size_t>& arr, size_t preIndexInRawStr)
{
	if (!n) return;
	if (n->isEnd) arr.emplace_back(preIndexInRawStr);
	for (size_t i = 0; i < 256; ++i) this->getSuffixArray_pri(n->nexts[i], arr, preIndexInRawStr - 1);
}

Trie::Trie()
{
	this->head = new Trie::Node('!');
}

Trie::~Trie()
{
	this->postOrderDel(this->head);
}

void Trie::insert(std::string str)
{
	Trie::Node* pre = this->head;
	for (auto& iterstr : str)
	{
		if (!pre->nexts[iterstr])
		{
			Trie::Node* ne = new Trie::Node(iterstr);
			pre->nexts[iterstr] = ne;
		}
		pre = pre->nexts[iterstr];
	}
	pre->isEnd = true;
}

void Trie::insert(std::string::iterator begin, std::string::iterator end)
{
	Trie::Node* pre = this->head;
	for (std::string::iterator spre = begin; spre != end; ++spre)
	{
		char c = *spre;
		if (!pre->nexts[c])
		{
			Trie::Node* ne = new Trie::Node(c);
			pre->nexts[c] = ne;
		}
		pre = pre->nexts[c];
	}
	pre->isEnd = true;
}

bool Trie::isPrefix(std::string prefix)
{
	Trie::Node* pre = this->head;
	for (auto& iterstr : prefix)
	{
		if (!pre->nexts[iterstr]) return false;
		pre = pre->nexts[iterstr];
	}
	return true;
}

bool Trie::isOccur(std::string str)
{
	Trie::Node* pre = this->head;
	for (auto& iterstr : str)
	{
		if (!pre->nexts[iterstr]) return false;
		pre = pre->nexts[iterstr];
	}
	return pre->isEnd;
}

bool Trie::remove(std::string str)
{
	Trie::Node* pre = this->head;
	std::stack<pair<Trie::Node*, char>> st; //栈, 存放迭代式DFS查找到的pair<节点,字符>对
	for (auto& iterstr : str)
	{
		if (!pre->nexts[iterstr]) return false;
		pre = pre->nexts[iterstr];
		st.push(pair<Trie::Node*, char>{pre, iterstr});
	}

	if (!pre->isEnd) return false;
	else //开始删除
	{
		pre->isEnd = false;
		while (!st.empty())
		{
			pair<Trie::Node*, char> temp = st.top();
			Trie::Node* tempNode = temp.first;
			char tempChar = temp.second;
			st.pop();
			bool isThisNodeEmpty = true;
			for (size_t i = 0; i < 256; ++i)
			{
				if (tempNode->nexts[i])
				{
					isThisNodeEmpty = false;
					break;
				}
			}

			if (!isThisNodeEmpty || tempNode->isEnd) break;
			else
			{
				Trie::Node* parNode = !st.empty() ? st.top().first : this->head;
				if (parNode) parNode->nexts[tempChar] = nullptr;
				delete tempNode;
			}
		}
		return true;
	}
}

std::vector<size_t> Trie::getSuffixArray(size_t totalLength)
{
	std::vector<size_t> res;
	this->getSuffixArray_pri(this->head, res, totalLength);
	return res;
}

/*
 * 使用后缀树获得匹配的字符串个数
 * 输入std::string raw源字符串, std::string pattern匹配字符串
 * 输出匹配的个数 int
 */
int SuffixTriePatternMatching(std::string raw, std::string pattern)
{
	//std::string raw = "banana";
	//std::string pattern = "ana";

	//生成前缀树
	Trie tri;
	for (std::string::iterator iter = raw.begin(); iter != raw.end(); ++iter) tri.insert(iter, raw.end());
	//前缀树->前缀数组
	std::vector<size_t> suffixArr = tri.getSuffixArray(raw.size());
	//DEBUG
	std::cout << "suffix arr of " << raw << " is:" << std::endl;
	for (auto& itersize_t : suffixArr) cout << itersize_t << " ";
	cout << endl;

	//二分找到前缀数组的起始与结束位置
	size_t minIndex = 0;
	size_t maxIndex = raw.size() - 1;
	while (minIndex < maxIndex)
	{
		size_t midIndex = (minIndex + maxIndex) / 2;
		if (pattern > raw.substr(suffixArr[midIndex])) minIndex = midIndex + 1;
		else maxIndex = midIndex;
	}
	size_t st = minIndex;
	
	maxIndex = raw.size() - 1;
	while (minIndex < maxIndex)
	{
		size_t midIndex = (minIndex + maxIndex) / 2;
		if (pattern < raw.substr(suffixArr[midIndex])) maxIndex = midIndex;
		else minIndex = midIndex + 1;
	}
	size_t en = maxIndex;
	return (st <= en) ? en - st + 1: 0;
}

void SuffixTriePatternMatchingTest()
{
	int res = SuffixTriePatternMatching("banana", "ana");
	std::cout << "the number of ana(pattern) in banana(rawstr) is: " << res << std::endl;
}
