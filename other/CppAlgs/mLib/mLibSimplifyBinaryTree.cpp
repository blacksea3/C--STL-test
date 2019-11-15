#include "mLibSimplifyBinaryTree.hpp"

void msp_searchtree::insertpri(int t, mspNode * n, int& tcount)
{
	if (n->val < t)
	{
		tcount += n->count;
		if (!n->right)
		{
			n->right = new mspNode(t);
			return;
		}
		else insertpri(t, n->right, tcount);
	}
	else if (n->val > t)
	{
		n->count++;
		if (!n->left)
		{
			n->left = new mspNode(t);
			return;
		}
		else insertpri(t, n->left, tcount);
	}
	else
	{
		mspNode * pre = n->left;
		while(pre)
		{
			tcount += pre->count;
			pre = pre->right;
		}
		n->count++;
		return;
	}
}

int msp_searchtree::insert(int t)
{
	if (!this->head)
	{
		this->head = new mspNode(t);
		return 0;
	}
	else
	{
		int tcount = 0;
		this->insertpri(t, this->head, tcount);
		return tcount;
	}
}

void msp_searchtreeTest()
{
	vector<int> nums = { 26, 78, 27, 100, 33, 67, 90, 23, 66, 5, 38, 7, 35, 23, 52, 22, 83, 51, 
		98, 69, 81, 32, 78, 28, 94, 13, 2, 97, 3, 76, 99, 51, 9, 21, 84, 66, 65, 36, 100, 41 };
	vector<int> res;
	msp_searchtree* msp = new msp_searchtree();
	reverse(nums.begin(), nums.end());
	int c = 0;
	for (auto& n : nums)
	{
		c++;
		if (c == 35)
			int p = 1;
		res.emplace_back(msp->insert(n));
	}
		
	reverse(res.begin(), res.end());
	int i = 1;
}
