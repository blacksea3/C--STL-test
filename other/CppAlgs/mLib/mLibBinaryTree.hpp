#pragma once

#include "mLibvector.hpp"
#include "../public/public.hpp"

namespace mLib
{
	/*
	 * �Զ������������
	 * �ڲ�ʹ��STD::pair
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
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
		mbinary_searchtree<T>::Node* head;                    //���ڵ�
		mbinary_searchtree<T>::Node* findinsert(T t, mbinary_searchtree<T>::Node* n);   //�����ܲ���λ�õĽڵ�, Ҳ������С��ֵ>=n�Ľڵ�, ��������Ϊ��
		mbinary_searchtree<T>::Node* next(T t, mbinary_searchtree<T>::Node* n);         //������һ���ڵ�, �ҵõ��򷵻ش˽ڵ�, ����null
		void postorder_del(mbinary_searchtree<T>::Node* n);   //�������, ������������
		bool insertpri(T t, mbinary_searchtree<T>::Node* n);  //�ڲ���������ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool removepri(T t, mbinary_searchtree<T>::Node* n);  //�ڲ�����ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		void inorderpri(mbinary_searchtree<T>::Node* n);      //�ڲ������������, ������
	public:
		mbinary_searchtree();                                 //�޲���
		~mbinary_searchtree();                                //�������ɾ��, ������

		bool find(T t);                                       //����ֵ, �ҵõ���true, ����false
		mLib::mvector<T> RangeSearch(T le, T ri);             //��Χ����, ����ֵ�Ĵ�С��[le, ri]��Χ�ڵ�ֵ����
		bool insert(T t);                                     //����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		void inorder();                                       //�������, ������
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
			while (pre && pre->right == old)   //���pre=nullptr�˳�˵��û��next��
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
					if (!pre->left) //�����Ϊ��
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
					else if (!pre->right)  //�Ҷ���Ϊ��
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
					else //�����Ӷ�����, Ѱ����һ���ڵ�next, �滻����, Ȼ��ɾ����һ���ڵ�, ע��:��һ���ڵ�һ��û�������!
					{
						Node* next = pre->right;  //�˲���һ������, next������Ϊ��
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


