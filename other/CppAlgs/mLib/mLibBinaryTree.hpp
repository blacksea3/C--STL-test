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
					else //两儿子都不空, 寻找下一个节点next, 替换过来, 然后删除下一个节点, 注意:下一个节点一定没有左儿子!但可能有右儿子
					{
						//寻找下一个节点
						Node* next = pre->right;  //此步骤一定存在, next不可能为空
						par = pre;
						while (next->left)
						{
							next = next->left;
							par = next;
						}
						pre->val = next->val;
						//更新待删除的节点
						if (next->right)
						{
							next->val = next->right->val;
							del = next->right;
						}
						else del = next;
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

namespace mLib 
{
	/*
	 * 自定义AVL树，自适应二叉搜索树
	 * 内部使用STD::pair
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class mAVLtree
	{
	private:
		struct Node
		{
			T val;
			Node* left;
			Node* right;
			Node* parent;
			Node* height;
			Node(T v)
			{
				val = v;
				left = nullptr;
				right = nullptr;
				parent = nullptr;
			}
		};
		mAVLtree<T>::Node* head;                    //根节点
		mAVLtree<T>::Node* findinsert(T t, mAVLtree<T>::Node* n);   //查找能插入位置的节点, 也就是最小的值>=n的节点, 不存在则为空
		mAVLtree<T>::Node* next(T t, mAVLtree<T>::Node* n);         //查找下一个节点, 找得到则返回此节点, 否则null
		void postorder_del(mAVLtree<T>::Node* n);   //后序遍历, 用于析构函数
		bool insertpri(T t, mAVLtree<T>::Node* n);  //内部函数插入值, 若已经存在则返回false, 否则插入然后返回true
		bool removepri(T t, mAVLtree<T>::Node* n);  //内部函数删除值, 若已经存在则删除然后返回true, 否则返回false
		void inorderpri(mAVLtree<T>::Node* n);      //内部函数中序遍历, 中左右

		void leftRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);        //左旋
		void rightRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);       //右旋
		void leftrightRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);   //左右旋
		void rightleftRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);   //右左旋

		void updateHeight(mAVLtree<T>::Node* n);    //更新高度
		void getHeight(mAVLtree<T>::Node* n);       //获取高度，如果是空指针那么就是0，否则是节点的高度
		void makeAVLValid(mAVLtree<T>::Node* par, mAVLtree<T>::Node* pre);   //使AVL性质满足

	public:
		mAVLtree();                                 //无操作
		~mAVLtree();                                //后序遍历删除, 左右中

		bool find(T t);                                       //查找值, 找得到则true, 否则false
		mLib::mvector<T> RangeSearch(T le, T ri);             //范围查找, 返回值的大小在[le, ri]范围内的值数组
		bool insert(T t);                                     //插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //删除值, 若已经存在则删除然后返回true, 否则返回false
		void inorder();                                       //中序遍历, 中左右
	};

	template<typename T>
	typename mAVLtree<T>::Node * mAVLtree<T>::findinsert(T t, mAVLtree<T>::Node * n)
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
	typename mAVLtree<T>::Node * mAVLtree<T>::next(T t, mAVLtree<T>::Node * n)
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
	void mAVLtree<T>::postorder_del(mAVLtree<T>::Node * n)
	{
		if (!n) return;
		if (n->left) postorder_del(n->left);
		if (n->right) postorder_del(n->right);
		delete n;
	}

	template<typename T>
	bool mAVLtree<T>::insertpri(T t, mAVLtree<T>::Node * n)
	{
		if (!n)
		{
			this->head = new mAVLtree<T>::Node(t);
			return true;
		}
		else
		{
			//先按二叉搜索树方法插入, 同时对新建的节点高度赋值为1
			mAVLtree<T>::Node* par = nullptr;
			mAVLtree<T>::Node* pre = this->head;
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
				par->left = new mAVLtree<T>::Node(t);
				par->left->parent = par;
				pre = par->left;
			}
			else
			{
				par->right = new mAVLtree<T>::Node(t);
				par->right->parent = par;
				pre = par->right;
			}
			//然后调整位置, 现在par是父亲节点, pre是新插入的节点(子节点)
			//以父亲节点为子节点，父亲的父亲节点为父亲节点，自下而上更新二叉树以满足高度关系
			while (par)
			{
				this->updateHeight(pre);
				this->updateHeight(par);
				this->makeAVLValid(par, pre);
				pre = par;
				par = par->parent;
			}
			this->updateHeight(pre);
			return true;
		}
	}

	template<typename T>
	bool mAVLtree<T>::removepri(T t, mAVLtree<T>::Node * n)
	{
		if (!n) return false;
		else
		{
			//先按二叉搜索树的删除方法删除一个节点
			mAVLtree<T>::Node* par = nullptr;
			mAVLtree<T>::Node* pre = this->head;
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
					else //两儿子都不空, 寻找下一个节点next, 替换过来, 然后删除下一个节点, 注意:下一个节点一定没有左儿子!但可能有右儿子
					{
						//寻找下一个节点
						Node* next = pre->right;  //此步骤一定存在, next不可能为空
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//更新待删除的节点
						if (next->right)
						{
							next->val = next->right->val;
							del = next->right;
							par = next;
						}
						else del = next;
					}
					delete del;
					del = nullptr;

					//然后调整位置, 现在par是被删除节点的父亲节点
					pre = par;
					par = par->parent;

					while (par)
					{
						this->updateHeight(pre);
						this->updateHeight(par);
						this->makeAVLValid(par, pre);
						pre = par;
						par = par->parent;
					}
					this->updateHeight(pre);
					return true;
				}
			}
		}
		return false;
	}

	template<typename T>
	void mAVLtree<T>::inorderpri(mAVLtree<T>::Node * n)
	{
		if (!n) return;
		if (n->left) this->inorderpri(n->left);
		std::cout << n->val << " ";
		if (n->right) this->inorderpri(n->right);
	}

	template<typename T>
	void mAVLtree<T>::leftRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * son)
	{
		//预处理
		Node* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gre->left == par) ? true : false;
		//拆开父亲和右儿子
		par->right = pre->left;
		pre->left->parent = par;
		//反转父亲和右儿子的关系
		pre->left = par;
		par->parent = pre->left;
		//后处理
		this->updateHeight(par);
		this->updateHeight(pre);
		if (!GraOccur)
		{
			pre->parent = nullptr;
			this->head = pre;
		}
		else if (GraLeft)
		{
			pre->parent = gra;
			gra->left = pre;
		}
		else
		{
			pre->parent = gra;
			gra->right = pre;
		}

	}

	template<typename T>
	void mAVLtree<T>::rightRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * son)
	{
		//预处理
		Node* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gre->left == par) ? true : false;
		//拆开父亲和左儿子
		par->left = pre->right;
		pre->right->parent = par;
		//反转父亲和左儿子的关系
		pre->right = par;
		par->parent = pre->right;
		//后处理
		this->updateHeight(par);
		this->updateHeight(pre);
		if (!GraOccur)
		{
			pre->parent = nullptr;
			this->head = pre;
		}
		else if (GraLeft)
		{
			pre->parent = gra;
			gra->left = pre;
		}
		else
		{
			pre->parent = gra;
			gra->right = pre;
		}
	}

	template<typename T>
	void mAVLtree<T>::leftrightRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * son)
	{
		//先左旋后右旋
		this->leftRotate(pre->right, pre);
		this->rightRotate(pre->parent, par);
	}

	template<typename T>
	void mAVLtree<T>::rightleftRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * son)
	{
		this->rightRotate(pre->left, pre);
		this->leftRotate(pre->parent, par);
	}

	template<typename T>
	void mAVLtree<T>::updateHeight(mAVLtree<T>::Node * n)
	{
		n->height = max(this->getHeight(n->left), this->getHeight(n->right));
	}

	template<typename T>
	void mAVLtree<T>::getHeight(mAVLtree<T>::Node * n)
	{
		return (n) ? n->height : 0;
	}

	template<typename T>
	void mAVLtree<T>::makeAVLValid(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		if (par->right->height > (par->left->height + 1))
		{
			if (pre->right->height > pre->left->height) this->leftRotate(par, pre);
			else if (pre->right->height < pre->left->height) this->rightleftRotate(par, pre);
			else throw "alg bug happened in mAVLtree::makeAVLValid(when called func:insertpri)";
		}
		else if (par->left->height > (par->right->height + 1))
		{
			if (pre->left->height > pre->right->height) this->rightRotate(par, pre);
			else if (pre->left->height < pre->right->height) this->leftrightRotate(par, pre);
			else throw "alg bug happened in mAVLtree::makeAVLValid(when called func:insertpri)";
		}
	}

	template<typename T>
	mAVLtree<T>::mAVLtree()
	{
		;
	}

	template<typename T>
	mAVLtree<T>::~mAVLtree()
	{
		this->postorder_del(this->head);
	}

	template<typename T>
	bool mAVLtree<T>::find(T t)
	{
		Node* re = this->findinsert(t, this->head);
		return (re == nullptr || re->val != t) ? false : true;
	}

	template<typename T>
	inline mLib::mvector<T> mAVLtree<T>::RangeSearch(T le, T ri)
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
	bool mAVLtree<T>::insert(T t)
	{
		return this->insertpri(t, this->head);
	}

	template<typename T>
	bool mAVLtree<T>::remove(T t)
	{
		return this->removepri(t, this->head);
	}

	template<typename T>
	void mAVLtree<T>::inorder()
	{
		this->inorderpri(this->head);
	}

}

