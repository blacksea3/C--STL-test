#pragma once
#include "../public/public.hpp"

/*
 * �ֵ���
 * �ڲ�ʹ��std::vector
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

	void insert(std::string str);        //�����ַ���str, ����ʽ����
	void insert(std::string::iterator begin, std::string::iterator end); //�����ַ���������[begin, end)֮����ַ���, ����ʽ����
	bool isPrefix(std::string prefix);   //�ж�prefix�Ƿ���ǰ׺, ����ʽ�ж�, �����Ƿ���ǰ׺
	bool isOccur(std::string str);       //�ж�str�Ƿ����, ����ʽ�ж�, �����Ƿ����
	bool remove(std::string str);        //ɾ���ַ���str, ����ʽɾ��, �����Ƿ�ɾ���ɹ�(������Ȼ��ɾ������˼)
};


