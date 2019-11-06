#pragma once

#include "mLibvector.hpp"
#include "../public/public.hpp"

namespace mLib
{
	/*
	 * 自定义二叉搜索树
	 * 内部使用STD::pair
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class mbinary_searchtree
	{
	private:
		struct Node
		{
			T val;
			Node* left;
			Node* right;
			Node* parent;
			Node(T v)
			{
				val = v;
				left = nullptr;
				right = nullptr;
				parent = nullptr;
			}
		};
		mbinary_searchtree<T>::Node* head;                    //根节点
		mbinary_searchtree<T>::Node* findinsert(T t, mbinary_searchtree<T>::Node* n);   //查找能插入位置的节点, 也就是最小的值>=n的节点, 不存在则为空
		mbinary_searchtree<T>::Node* next(T t, mbinary_searchtree<T>::Node* n);         //查找下一个节点, 找得到则返回此节点, 否则null
		void postorder_del(mbinary_searchtree<T>::Node* n);   //后序遍历, 用于析构函数
		bool insertpri(T t, mbinary_searchtree<T>::Node* n);  //内部函数插入值, 若已经存在则返回false, 否则插入然后返回true
		bool removepri(T t, mbinary_searchtree<T>::Node* n);  //内部函数删除值, 若已经存在则删除然后返回true, 否则返回false
		void inorderpri(mbinary_searchtree<T>::Node* n);      //内部函数中序遍历, 中左右
	public:
		mbinary_searchtree();                                 //无操作
		~mbinary_searchtree();                                //后序遍历删除, 左右中

		bool find(T t);                                       //查找值, 找得到则true, 否则false
		mLib::mvector<T> RangeSearch(T le, T ri);             //范围查找, 返回值的大小在[le, ri]范围内的值数组
		bool insert(T t);                                     //插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //删除值, 若已经存在则删除然后返回true, 否则返回false
		void inorder();                                       //中序遍历, 中左右
	};

	template<typename T>
	typename mbinary_searchtree<T>::Node * mbinary_searchtree<T>::findinsert(T t, typename mbinary_searchtree::Node * n)
	{
		if (!n || n->val == t) return n;
		else if (n->val > t)
		{
			if (n->left) return this->findinsert(t, n->left);
			return n;
		}
		else
		{
			if (n->right) return this->findinsert(t, n->right);
			else return nullptr;
		}
	}

	template<typename T>
	typename mbinary_searchtree<T>::Node* mbinary_searchtree<T>::next(T t, typename mbinary_searchtree::Node * n)
	{
		if (!n) return nullptr;
		else if (n->right)
		{
			n = n->right;
			while (n->left) n = n->left;
			return n;
		}
		else
		{
			Node* old = n;
			Node* pre = n->parent;
			while (pre && pre->right == old)   //如果pre=nullptr退出说明没有next了
			{
				old = pre;
				pre = pre->parent;
			}
			return pre;
		}
	}

	template<typename T>
	void mbinary_searchtree<T>::postorder_del(typename mbinary_searchtree<T>::Node * n)
	{
		if (!n) return;
		if (n->left) postorder_del(n->left);
		if (n->right) postorder_del(n->right);
		delete n;
	}

	template<typename T>
	bool mbinary_searchtree<T>::insertpri(T t, mbinary_searchtree<T>::Node * n)
	{
		if (!n)
		{
			this->head = new mbinary_searchtree<T>::Node(t);
			return true;
		}
		else
		{
			mbinary_searchtree<T>::Node* par = nullptr;
			mbinary_searchtree<T>::Node* pre = this->head;
			while (pre)
			{
				if (pre->val > t)
				{
					par = pre;
					pre = pre->left;
				}
				else if (pre->val < t)
				{
					par = pre;
					pre = pre->right;
				}
				else return false;
			}
			if (par->val > t)
			{
				par->left = new mbinary_searchtree<T>::Node(t);
				par->left->parent = par;
			}
			else
			{
				par->right = new mbinary_searchtree<T>::Node(t);
				par->right->parent = par;
			}
			return true;
		}
	}

	template<typename T>
	bool mbinary_searchtree<T>::removepri(T t, mbinary_searchtree<T>::Node * n)
	{
		if (!n) return false;
		else
		{
			mbinary_searchtree<T>::Node* par = nullptr;
			mbinary_searchtree<T>::Node* pre = this->head;
			while (pre)
			{
				if (pre->val > t)
				{
					par = pre;
					pre = pre->left;
				}
				else if (pre->val < t)
				{
					par = pre;
					pre = pre->right;
				}
				else
				{
					Node* del = pre;
					if (!pre->left) //左儿子为空
					{
						if (par)
						{
							if (par->left == pre)
							{
								par->left = pre->right;
								pre->right->parent = par;
							}
							else
							{
								par->right = pre->right;
								pre->right->parent = par;
							}
						}
						else this->head = pre->right;
					}
					else if (!pre->right)  //右儿子为空
					{
						if (par)
						{
							if (par->left == pre)
							{
								par->left = pre->left;
								pre->left->parent = par;
							}
							else
							{
								par->right = pre->left;
								pre->left->parent = par;
							}
						}
						else this->head = pre->left;
					}
					else //两儿子都不空, 寻找下一个节点next, 替换过来, 然后删除下一个节点, 注意:下一个节点一定没有左儿子!
					{
						Node* next = pre->right;  //此步骤一定存在, next不可能为空
						par = pre;
						while (next->left)
						{
							next = next->left;
							par = next;
						}
						pre->val = next->val;
						del = next;
						if (par->left == next)
						{
							par->left = next->right;
							if (next->right) next->right->parent = par->left;
						}
						else
						{
							par->right = next->right;
							if (next->right) next->right->parent = par->right;
						}
					}
					delete del;
					del = nullptr;
					return true;
				}
			}
		}
		return false;
	}

	template<typename T>
	void mbinary_searchtree<T>::inorderpri(mbinary_searchtree<T>::Node * n)
	{
		if (!n) return;
		if (n->left) this->inorderpri(n->left);
		std::cout << n->val << " ";
		if (n->right) this->inorderpri(n->right);
	}

	template<typename T>
	mbinary_searchtree<T>::mbinary_searchtree()
	{
		;
	}

	template<typename T>
	mbinary_searchtree<T>::~mbinary_searchtree()
	{
		this->postorder_del(this->head);
	}

	template<typename T>
	bool mbinary_searchtree<T>::find(T t)
	{
		Node* re = this->findinsert(t, this->head);
		return (re == nullptr || re->val != t) ? false : true;
	}

	template<typename T>
	mLib::mvector<T> mbinary_searchtree<T>::RangeSearch(T le, T ri)
	{
		Node* begin = this->findinsert(le, this->head);
		mLib::mvector<T> res;
		while (begin && begin->val <= ri)
		{
			res.push_back(begin->val);
			begin = this->next(begin->val, begin);
		}
		return res;
	}

	template<typename T>
	bool mbinary_searchtree<T>::insert(T t)
	{
		return this->insertpri(t, this->head);
	}

	template<typename T>
	bool mbinary_searchtree<T>::remove(T t)
	{
		return this->removepri(t, this->head);
	}

	template<typename T>
	void mbinary_searchtree<T>::inorder()
	{
		this->inorderpri(this->head);
	}

	void mLibBinaryTreeClassTest();
}


