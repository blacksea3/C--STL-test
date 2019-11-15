#pragma once
#include "../public/public.hpp"

/*
 * 简化自定义二叉搜索树，原始版
 * 元素不可重复
 * 内部在中序遍历输出时使用std::vector
 * 默认左<中<右, T必须是一个支持二元比较判断的类型
 * 内部节点包含一个额外值：conut表示自己+左子树的总节点个数
 */

struct mspNode
{
	int val;
	mspNode* left;
	mspNode* right;
	int count;
	mspNode(int v)
	{
		val = v;
		left = nullptr;
		right = nullptr;
		count = 1;
	}
};

class msp_searchtree
{
private:
	mspNode* head;                         //根节点
	void insertpri(int t, mspNode* n, int& tcount);     //插入查找(返回<=此值的个数)
public:
	int insert(int t);                    //插入查找, 插入并返回<=此值的个数, 若值已存在则虚拟成两个相同节点的重叠
};

void msp_searchtreeTest();
