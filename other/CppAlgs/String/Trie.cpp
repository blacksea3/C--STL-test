#include "Trie.hpp"

void Trie::postOrderDel(Trie::Node* n)
{
	if (!n) return;
	for (size_t i = 0; i < 26; ++i) this->postOrderDel(n->nexts[i]);
	delete n;
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
		if (!pre->nexts[iterstr - 'a'])
		{
			Trie::Node* ne = new Trie::Node(iterstr);
			pre->nexts[iterstr - 'a'] = ne;
		}
		pre = pre->nexts[iterstr - 'a'];
	}
	pre->isEnd = true;
}

void Trie::insert(std::string::iterator begin, std::string::iterator end)
{
	Trie::Node* pre = this->head;
	for (std::string::iterator spre = begin; spre != end; ++spre)
	{
		char c = *spre;
		if (!pre->nexts[c - 'a'])
		{
			Trie::Node* ne = new Trie::Node(c);
			pre->nexts[c - 'a'] = ne;
		}
		pre = pre->nexts[c - 'a'];
	}
	pre->isEnd = true;
}

bool Trie::isPrefix(std::string prefix)
{
	Trie::Node* pre = this->head;
	for (auto& iterstr : prefix)
	{
		if (!pre->nexts[iterstr - 'a']) return false;
		pre = pre->nexts[iterstr - 'a'];
	}
	return true;
}

bool Trie::isOccur(std::string str)
{
	Trie::Node* pre = this->head;
	for (auto& iterstr : str)
	{
		if (!pre->nexts[iterstr - 'a']) return false;
		pre = pre->nexts[iterstr - 'a'];
	}
	return pre->isEnd;
}

bool Trie::remove(std::string str)
{
	Trie::Node* pre = this->head;
	std::stack<pair<Trie::Node*, char>> st; //ջ, ��ŵ���ʽDFS���ҵ���pair<�ڵ�,�ַ�>��
	for (auto& iterstr : str)
	{
		if (!pre->nexts[iterstr - 'a']) return false;
		pre = pre->nexts[iterstr - 'a'];
		st.push(pair<Trie::Node*, char>{pre, iterstr});
	}

	if (!pre->isEnd) return false;
	else //��ʼɾ��
	{
		pre->isEnd = false;
		while (!st.empty())
		{
			pair<Trie::Node*, char> temp = st.top();
			Trie::Node* tempNode = temp.first;
			char tempChar = temp.second;
			st.pop();
			bool isThisNodeEmpty = true;
			for (size_t i = 0; i < 26; ++i)
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
				if (parNode) parNode->nexts[tempChar - 'a'] = nullptr;
				delete tempNode;
			}
		}
		return true;
	}
}


