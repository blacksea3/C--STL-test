#pragma once
#include "../public/public.hpp"

/*
 * 字典树
 * 内部使用std::vector
 */
class Trie
{
private:
	struct Node
	{
		char ch;
		std::array<Trie::Node*, 26> nexts;
		bool isEnd;
		explicit Node(char c)
		{
			ch = c;
			for (size_t i = 0; i < 26; ++i) nexts[i] = nullptr;
			isEnd = false;
		}
	};

	Trie::Node* head;
	void postOrderDel(Trie::Node* n);

public:
	Trie();
	~Trie();

	void insert(std::string str);        //插入字符串str, 迭代式插入
	void insert(std::string::iterator begin, std::string::iterator end); //插入字符串迭代器[begin, end)之间的字符串, 迭代式插入
	bool isPrefix(std::string prefix);   //判断prefix是否是前缀, 迭代式判断, 返回是否是前缀
	bool isOccur(std::string str);       //判断str是否存在, 迭代式判断, 返回是否存在
	bool remove(std::string str);        //删除字符串str, 迭代式删除, 返回是否删除成功(即存在然后删除的意思)
};


