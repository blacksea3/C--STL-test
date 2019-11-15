#pragma once
#include "../public/public.hpp"

/*
 * ���Զ��������������ԭʼ��
 * Ԫ�ز����ظ�
 * �ڲ�������������ʱʹ��std::vector
 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
 * �ڲ��ڵ����һ������ֵ��conut��ʾ�Լ�+���������ܽڵ����
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
	mspNode* head;                         //���ڵ�
	void insertpri(int t, mspNode* n, int& tcount);     //�������(����<=��ֵ�ĸ���)
public:
	int insert(int t);                    //�������, ���벢����<=��ֵ�ĸ���, ��ֵ�Ѵ����������������ͬ�ڵ���ص�
};

void msp_searchtreeTest();
