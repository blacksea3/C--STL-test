#pragma once

#include "mLibvector.hpp"
#include "../public/public.hpp"

namespace mLib
{
	template<typename T>
	struct nNode   //公共节点
	{
		T val;
		nNode* left;
		nNode* right;
		nNode* parent;
		int height;
		int& color = height;
		nNode(T v = 0)
		{
			val = v;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			height = 0;
		}
	};
}

//以下是二叉搜索树和AVL树，节点在树的内部

namespace mLib
{
	/*
	 * 自定义二叉搜索树
	 * 元素不可重复
	 * 内部在中序遍历输出时使用std::vector
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class mbinary_searchtree
	{
	protected:
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
	private:
		mbinary_searchtree<T>::Node* findinsert(T t, mbinary_searchtree<T>::Node* n);   //查找能插入位置的节点, 也就是最小的值>=n的节点, 不存在则为空
		mbinary_searchtree<T>::Node* next(T t, mbinary_searchtree<T>::Node* n);         //查找下一个节点, 找得到则返回此节点, 否则null
		void postorder_del(mbinary_searchtree<T>::Node* n);   //后序遍历, 用于析构函数
		//内部函数插入值, pair:第一个是bool, 第二个是另一个pair表示它的父亲par, 和被插入节点pre, 若已经存在则返回false, nul, nul, 否则插入然后返回true, 俩节点
		pair<bool, pair<mbinary_searchtree<T>::Node*, mbinary_searchtree<T>::Node*>> insertpri(T t, mbinary_searchtree<T>::Node* n);
		//内部函数插入值, pair:第一个是bool, 第二个被删除节点的父亲par, 若已经存在则返回false, nul, 否则插入然后返回true, 该节点
		pair<bool, mbinary_searchtree<T>::Node*> removepri(T t, mbinary_searchtree<T>::Node* n);
		void inorderpri(mbinary_searchtree<T>::Node* n, std::vector<T>& res);      //内部函数中序遍历, 中左右
		bool checkIfTreeValidpri(mbinary_searchtree<T>::Node* n);          //内部函数测试树性质是否满足
	public:
		mbinary_searchtree();                                 //无操作
		~mbinary_searchtree();                                //后序遍历删除, 左右中

		bool find(T t);                                       //查找值, 找得到则true, 否则false
		mLib::mvector<T> RangeSearch(T le, T ri);             //范围查找, 返回值的大小在[le, ri]范围内的值数组
		bool insert(T t);                                     //插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //删除值, 若已经存在则删除然后返回true, 否则返回false
		std::vector<T> inorder();                             //中序遍历, 中左右
		bool checkIfTreeValid();                              //测试树性质是否满足
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
	pair<bool, pair<typename mbinary_searchtree<T>::Node*, typename mbinary_searchtree<T>::Node*>>
		mbinary_searchtree<T>::insertpri(T t, mbinary_searchtree<T>::Node * n)
	{
		if (!n)
		{
			this->head = new mbinary_searchtree<T>::Node(t);
			return pair<bool, pair<mbinary_searchtree<T>::Node*, mbinary_searchtree<T>::Node*>>
			{true, { nullptr, this->head }};
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
				else return pair<bool, pair<mbinary_searchtree<T>::Node*, mbinary_searchtree<T>::Node*>>
				{false, {nullptr, nullptr}};
			}
			if (par->val > t)
			{
				par->left = new mbinary_searchtree<T>::Node(t);
				par->left->parent = par;
				pre = par->left;
			}
			else
			{
				par->right = new mbinary_searchtree<T>::Node(t);
				par->right->parent = par;
				pre = par->right;
			}
			return pair<bool, pair<mbinary_searchtree<T>::Node*, mbinary_searchtree<T>::Node*>>
			{true, { par, pre }};
		}
	}

	template<typename T>
	pair<bool, typename mbinary_searchtree<T>::Node*> mbinary_searchtree<T>::removepri(T t, mbinary_searchtree<T>::Node * n)
	{
		if (!n) return pair<bool, mbinary_searchtree<T>::Node*>{false, nullptr};
		else
		{
			mbinary_searchtree<T>::Node* par = n->parent;
			mbinary_searchtree<T>::Node* pre = n;
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
					bool DirectDelNode = false;
					if (!pre->left && !pre->right) //左右儿子都空, 直接删
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delete del;
					}
					else if (!pre->left) //左儿子为空, 把右儿子移过来
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
						else
						{
							this->head = pre->right;
							this->head->parent = nullptr;
						}
						delete del;
					}
					else if (!pre->right)  //右儿子为空, 把左儿子移过来
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
						else
						{
							this->head = pre->left;
							this->head->parent = nullptr;
						}
						delete del;
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
						//修改next节点相关关系
						if (next == par->left)
						{
							par->left = next->right;
							if (next->right) next->right->parent = par;
						}
						else
						{
							par->right = next->right;
							if (next->right) next->right->parent = par;
						}
						del = next;
						delete del;
					}
					return pair<bool, mbinary_searchtree<T>::Node*>{true, par};
				}
			}
		}
		return pair<bool, mbinary_searchtree<T>::Node*>{false, nullptr};
	}

	template<typename T>
	void mbinary_searchtree<T>::inorderpri(mbinary_searchtree<T>::Node * n, std::vector<T>& res)
	{
		if (!n) return;
		if (n->left) this->inorderpri(n->left, res);
		res.emplace_back(n->val);
		if (n->right) this->inorderpri(n->right, res);
	}

	template<typename T>
	bool mbinary_searchtree<T>::checkIfTreeValidpri(mbinary_searchtree<T>::Node * n)
	{
		if (!n) return true;
		else
		{
			if (n->left && n != n->left->parent && n->val <= n->left->val) return false;
			if (n->right && n != n->right->parent && n->val >= n->left->val) return false;
			return this->checkIfTreeValidpri(n->left) && this->checkIfTreeValidpri(n->right);
		}
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
		return this->insertpri(t, this->head).first;
	}

	template<typename T>
	bool mbinary_searchtree<T>::remove(T t)
	{
		return this->removepri(t, this->head).first;
	}

	template<typename T>
	std::vector<T> mbinary_searchtree<T>::inorder()
	{
		std::vector<T> res;
		this->inorderpri(this->head, res);
		return res;
	}

	template<typename T>
	bool mbinary_searchtree<T>::checkIfTreeValid()
	{
		return this->checkIfTreeValidpri(this->head);
	}

	void mLibBinaryTreeClassTest();
}

namespace mLib 
{
	/*
	 * 自定义AVL树，自适应二叉搜索树
	 * 元素不可重复
	 * 内部在中序遍历输出时使用std::vector
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
			int height;
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
		void inorderpri(mAVLtree<T>::Node* n, std::vector<T>& res);      //内部函数中序遍历, 中左右

		void leftRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);        //左旋
		void rightRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);       //右旋
		void leftrightRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);   //左右旋
		void rightleftRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);   //右左旋

		void updateHeight(mAVLtree<T>::Node* n);    //更新高度
		int getHeight(mAVLtree<T>::Node* n);       //获取高度，如果是空指针那么就是0，否则是节点的高度
		void makeAVLValidIterFunc(mAVLtree<T>::Node* par, mAVLtree<T>::Node* pre);   //函数内部迭代自底向上修复AVL性质

		mAVLtree<T>::Node* makeAVLValid(mAVLtree<T>::Node* par, mAVLtree<T>::Node* pre);   //使AVL性质满足, 返回性质满足后的父亲节点
		bool checkIfAVLValidpri(mAVLtree<T>::Node* n);                //内部函数测试AVL性质是否满足

	public:
		mAVLtree();                                 //无操作
		~mAVLtree();                                //后序遍历删除, 左右中

		bool find(T t);                                       //查找值, 找得到则true, 否则false
		mLib::mvector<T> RangeSearch(T le, T ri);             //范围查找, 返回值的大小在[le, ri]范围内的值数组
		bool insert(T t);                                     //插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //删除值, 若已经存在则删除然后返回true, 否则返回false
		std::vector<T> inorder();                             //中序遍历, 中左右
		bool checkIfAVLValid();                                  //测试AVL性质是否满足
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
			this->makeAVLValidIterFunc(par, pre);
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
			mAVLtree<T>::Node* par = n->parent;
			mAVLtree<T>::Node* pre = n;
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
					bool DirectDelNode = false;
					if (!pre->left && !pre->right) //左右儿子都空, 直接删
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delete del;
					}
					else if (!pre->left) //左儿子为空, 把右儿子移过来
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
						else
						{
							this->head = pre->right;
							this->head->parent = nullptr;
						}
						delete del;
					}
					else if (!pre->right)  //右儿子为空, 把左儿子移过来
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
						else
						{
							this->head = pre->left;
							this->head->parent = nullptr;
						}
						delete del;
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
						//修改next节点相关关系
						if (next == par->left)
						{
							par->left = next->right;
							if (next->right) next->right->parent = par;
						}
						else
						{
							par->right = next->right;
							if (next->right) next->right->parent = par;
						}
						del = next;
						delete del;
					}
					//然后调整位置, 现在par是被删除节点的父亲节点
					//如果par为空说明树被删除没了, 不操作
					if (!par);
					else if (par->left)  //把父亲节点作为par, 儿子节点作为另一个未删除的儿子(如果有的话), 检查AVL性质
						this->makeAVLValidIterFunc(par, par->left);
					else if (par->right)
						this->makeAVLValidIterFunc(par, par->right);
					else  //否则, 父亲节点作为pre, 父亲的父亲节点作为par, 检查AVL性质
					{
						pre = par;
						par = par->parent;
						this->makeAVLValidIterFunc(par, pre);
					}
					return true;
				}
			}
		}
		return false;
	}

	template<typename T>
	void mAVLtree<T>::inorderpri(mAVLtree<T>::Node * n, std::vector<T>& res)
	{
		if (!n) return;
		if (n->left) this->inorderpri(n->left, res);
		res.emplace_back(n->val);
		if (n->right) this->inorderpri(n->right, res);
	}

	template<typename T>
	void mAVLtree<T>::leftRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		//预处理
		Node* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//拆开父亲和右儿子
		par->right = pre->left;
		if (pre->left) pre->left->parent = par;
		//反转父亲和右儿子的关系
		pre->left = par;
		par->parent = pre;
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
	void mAVLtree<T>::rightRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		//预处理
		Node* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//拆开父亲和左儿子
		par->left = pre->right;
		if (pre->right) pre->right->parent = par;
		//反转父亲和左儿子的关系
		pre->right = par;
		par->parent = pre;
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
	void mAVLtree<T>::leftrightRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		//先左旋后右旋
		this->leftRotate(pre, pre->right);
		this->rightRotate(par, pre->parent);
	}

	template<typename T>
	void mAVLtree<T>::rightleftRotate(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		this->rightRotate(pre, pre->left);
		this->leftRotate(par, pre->parent);
	}

	template<typename T>
	void mAVLtree<T>::updateHeight(mAVLtree<T>::Node * n)
	{
		if (n) n->height = std::max(this->getHeight(n->left), this->getHeight(n->right)) + 1;
	}

	template<typename T>
	int mAVLtree<T>::getHeight(mAVLtree<T>::Node * n)
	{
		return (n) ? n->height : 0;
	}

	template<typename T>
	void mAVLtree<T>::makeAVLValidIterFunc(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		while (par)
		{
			this->updateHeight(pre);
			this->updateHeight(par);
		    pre = this->makeAVLValid(par, pre);
			par = pre->parent;
		}
		this->updateHeight(pre);
	}

	template<typename T>
	typename mAVLtree<T>::Node* mAVLtree<T>::makeAVLValid(mAVLtree<T>::Node * par, mAVLtree<T>::Node * pre)
	{
		int parrRight = this->getHeight(par->right);
		int parlRight = this->getHeight(par->left);

		if (parrRight > (parlRight + 1))
		{
			//此处需要校准pre, 这是因为如果递归修改高度(例如删除操作中的), 可能导致当前pre是par的矮树
			pre = par->right;
			int prerRight = this->getHeight(pre->right);
			int prelRight = this->getHeight(pre->left);
			if (prerRight >= prelRight) this->leftRotate(par, pre);
			else if (prerRight < prelRight) this->rightleftRotate(par, pre);
			else throw "alg bug happened in mAVLtree::makeAVLValid(when called func:insertpri)";
			return par->parent;
		}
		else if (parlRight > (parrRight + 1))
		{
			pre = par->left;
			int prerRight = this->getHeight(pre->right);
			int prelRight = this->getHeight(pre->left);
			if (prelRight >= prerRight) this->rightRotate(par, pre);
			else if (prelRight < prerRight) this->leftrightRotate(par, pre);
			else throw "alg bug happened in mAVLtree::makeAVLValid(when called func:insertpri)";
			return par->parent;
		}
		return par;
	}

	template<typename T>
	bool mAVLtree<T>::checkIfAVLValidpri(mAVLtree<T>::Node * n)
	{
		if (!n) return true;
		else
		{
			if (n->left && n != n->left->parent && n->val <= n->left->val) return false;
			if (n->right && n != n->right->parent && n->val >= n->left->val) return false;
			if (abs(this->getHeight(n->left) - this->getHeight(n->right)) > 1) return false;
			else return this->checkIfAVLValidpri(n->left) && this->checkIfAVLValidpri(n->right);
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
	std::vector<T> mAVLtree<T>::inorder()
	{
		std::vector<T> res;
		this->inorderpri(this->head, res);
		return res;
	}

	template<typename T>
	bool mAVLtree<T>::checkIfAVLValid()
	{
		return this->checkIfAVLValidpri(this->head);
	}
}

/*
 *
 *******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
*******************************************************
 */

//以下是二叉搜索树/AVL树/Splay树/RedBlack树，节点在树的外部，相同结构体

namespace mLib
{
	/*
	 * 自定义二叉搜索树
	 * 元素不可重复
	 * 内部在中序遍历输出时使用std::vector
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class nmbinary_searchtree
	{
	protected:
		mLib::nNode<T>* head;                    //根节点
		mLib::nNode<T>* findinsert(T t, mLib::nNode<T>* n);   //查找能插入位置的节点, 也就是最小的值>=n的节点, 不存在则为空
		mLib::nNode<T>* next(T t, mLib::nNode<T>* n);         //查找下一个节点, 找得到则返回此节点, 否则null
		void postorder_del(mLib::nNode<T>* n);   //后序遍历, 用于析构函数
		//内部函数插入值, pair:第一个是bool, 第二个是另一个pair表示它的父亲par, 和被插入节点pre, 若已经存在则返回false, nul, nul, 否则插入然后返回true, 俩节点
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> insertpri(T t, mLib::nNode<T>* n);
		//内部函数删除值, pair:第一个是bool, 实际被删除节点的父亲par
		pair<bool, mLib::nNode<T>*> removepri(T t, mLib::nNode<T>* n);
		void inorderpri(mLib::nNode<T>* n, std::vector<T>& res);      //内部函数中序遍历, 中左右
		bool checkIfTreeValidpri(mLib::nNode<T>* n);          //内部函数测试树性质是否满足
	public:
		nmbinary_searchtree();                                 //无操作
		~nmbinary_searchtree();                                //后序遍历删除, 左右中

		bool find(T t);                                       //查找值, 找得到则true, 否则false
		mLib::mvector<T> RangeSearch(T le, T ri);             //范围查找, 返回值的大小在[le, ri]范围内的值数组
		bool insert(T t);                                     //插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //删除值, 若已经存在则删除然后返回true, 否则返回false
		std::vector<T> inorder();                             //中序遍历, 中左右
		bool checkIfTreeValid();                              //测试树性质是否满足
	};

	template<typename T>
	mLib::nNode<T>* nmbinary_searchtree<T>::findinsert(T t, mLib::nNode<T>* n)
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
	mLib::nNode<T>* nmbinary_searchtree<T>::next(T t, mLib::nNode<T>* n)
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
			mLib::nNode<T>* old = n;
			mLib::nNode<T>* pre = n->parent;
			while (pre && pre->right == old)   //如果pre=nullptr退出说明没有next了
			{
				old = pre;
				pre = pre->parent;
			}
			return pre;
		}
	}

	template<typename T>
	void nmbinary_searchtree<T>::postorder_del(mLib::nNode<T>* n)
	{
		if (!n) return;
		if (n->left) postorder_del(n->left);
		if (n->right) postorder_del(n->right);
		delete n;
	}

	template<typename T>
	pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
		nmbinary_searchtree<T>::insertpri(T t, mLib::nNode<T>* n)
	{
		if (!n)
		{
			this->head = new mLib::nNode<T>(t);
			return pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
			{true, { nullptr, this->head }};
		}
		else
		{
			mLib::nNode<T>* par = nullptr;
			mLib::nNode<T>* pre = this->head;
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
				else return pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
				{false, { nullptr, nullptr }};
			}
			if (par->val > t)
			{
				par->left = new mLib::nNode<T>(t);
				par->left->parent = par;
				pre = par->left;
			}
			else
			{
				par->right = new mLib::nNode<T>(t);
				par->right->parent = par;
				pre = par->right;
			}
			return pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
			{true, { par, pre }};
		}
	}

	template<typename T>
	pair<bool, mLib::nNode<T>*> nmbinary_searchtree<T>::removepri(T t, mLib::nNode<T>* n)
	{
		if (!n) return pair<bool, mLib::nNode<T>*>{false, nullptr};
		else
		{
			mLib::nNode<T>* par = n->parent;
			mLib::nNode<T>* pre = n;
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
					mLib::nNode<T>* del = pre;
					mLib::nNode<T>* subPar;
					mLib::nNode<T>* subBro;
					int delheight;
					bool DirectDelNode = false;
					if (!pre->left && !pre->right) //左右儿子都空, 直接删
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delheight = del->height;
						subPar = par;
						subBro = (par) ? ((par->left) ? par->left : par->right) : nullptr;
						delete del;
					}
					else if (!pre->left) //左儿子为空, 把右儿子移过来
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
						else
						{
							this->head = pre->right;
							this->head->parent = nullptr;
						}
						subPar = par;
						subBro = (par) ? ((par->left != pre->right) ? par->left : par->right) : nullptr;
						par = pre->right;
						delheight = del->height;
						delete del;
					}
					else if (!pre->right)  //右儿子为空, 把左儿子移过来
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
						else
						{
							this->head = pre->left;
							this->head->parent = nullptr;
						}
						subPar = par;
						subBro = (par) ? ((par->left != pre->left) ? par->left : par->right) : nullptr;
						par = pre->left;
						delheight = del->height;
						delete del;
					}
					else //两儿子都不空, 寻找下一个节点next, 替换过来, 然后删除下一个节点, 注意:下一个节点一定没有左儿子!但可能有右儿子
					{
						//寻找下一个节点
						mLib::nNode<T>* next = pre->right;  //此步骤一定存在, next不可能为空
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//修改next节点相关关系
						if (next == par->left)
						{
							subPar = par;
							subBro = par->right;
							par->left = next->right;
							if (next->right) next->right->parent = par;
						}
						else
						{
							subPar = par;
							subBro = par->left;
							par->right = next->right;
							if (next->right) next->right->parent = par;
						}
						del = next;
						delheight = del->height;
						delete del;
					}
					return pair<bool, mLib::nNode<T>*>{true, par};
				}
			}
		}
		return pair<bool, mLib::nNode<T>*>{false, nullptr};
	}

	template<typename T>
	void nmbinary_searchtree<T>::inorderpri(mLib::nNode<T>* n, std::vector<T>& res)
	{
		if (!n) return;
		if (n->left) this->inorderpri(n->left, res);
		res.emplace_back(n->val);
		if (n->right) this->inorderpri(n->right, res);
	}

	template<typename T>
	bool nmbinary_searchtree<T>::checkIfTreeValidpri(mLib::nNode<T>* n)
	{
		if (!n) return true;
		else
		{
			if (n->left && n != n->left->parent && n->val <= n->left->val) return false;
			if (n->right && n != n->right->parent && n->val >= n->right->val) return false;
			return this->checkIfTreeValidpri(n->left) && this->checkIfTreeValidpri(n->right);
		}
	}

	template<typename T>
	nmbinary_searchtree<T>::nmbinary_searchtree()
	{
		;
	}

	template<typename T>
	nmbinary_searchtree<T>::~nmbinary_searchtree()
	{
		this->postorder_del(this->head);
	}

	template<typename T>
	bool nmbinary_searchtree<T>::find(T t)
	{
		mLib::nNode<T>* re = this->findinsert(t, this->head);
		return (re == nullptr || re->val != t) ? false : true;
	}

	template<typename T>
	mLib::mvector<T> nmbinary_searchtree<T>::RangeSearch(T le, T ri)
	{
		mLib::nNode<T>* begin = this->findinsert(le, this->head);
		mLib::mvector<T> res;
		while (begin && begin->val <= ri)
		{
			res.push_back(begin->val);
			begin = this->next(begin->val, begin);
		}
		return res;
	}

	template<typename T>
	bool nmbinary_searchtree<T>::insert(T t)
	{
		return this->insertpri(t, this->head).first;
	}

	template<typename T>
	bool nmbinary_searchtree<T>::remove(T t)
	{
		return this->removepri(t, this->head).first;
	}

	template<typename T>
	std::vector<T> nmbinary_searchtree<T>::inorder()
	{
		std::vector<T> res;
		this->inorderpri(this->head, res);
		return res;
	}

	template<typename T>
	bool nmbinary_searchtree<T>::checkIfTreeValid()
	{
		return this->checkIfTreeValidpri(this->head);
	}
}

namespace mLib
{
	/*
	 * 自定义AVL树，自适应二叉搜索树
	 * 元素不可重复
	 * 内部在中序遍历输出时使用std::vector
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class nmAVLTree : public mLib::nmbinary_searchtree<T>
	{
	protected:
		void leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);        //左旋
		void rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);       //右旋
		void leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //左右旋
		void rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //右左旋
	private:
		void updateHeight(mLib::nNode<T>* n);    //更新高度
		int getHeight(mLib::nNode<T>* n);       //获取高度，如果是空指针那么就是0，否则是节点的高度
		void makeAVLValidIterFunc(mLib::nNode<T>* par, mLib::nNode<T>* pre);   //函数内部迭代自底向上修复AVL性质

		mLib::nNode<T>* makeAVLValid(mLib::nNode<T>* par, mLib::nNode<T>* pre);   //使AVL性质满足, 返回性质满足后的父亲节点
		bool checkIfAVLValidpri(mLib::nNode<T>* n);   //内部函数测试AVL性质是否满足
	public:
		bool checkIfAVLValid();                               //测试AVL性质是否满足
		bool insert(T t);                                     //重载父类方法, 插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //重载父类方法, 删除值, 若已经存在则删除然后返回true, 否则返回false
	};

	template<typename T>
	void nmAVLTree<T>::leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//预处理
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//拆开父亲和右儿子
		par->right = pre->left;
		if (pre->left) pre->left->parent = par;
		//反转父亲和右儿子的关系
		pre->left = par;
		par->parent = pre;
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
	void nmAVLTree<T>::rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//预处理
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//拆开父亲和左儿子
		par->left = pre->right;
		if (pre->right) pre->right->parent = par;
		//反转父亲和左儿子的关系
		pre->right = par;
		par->parent = pre;
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
	void nmAVLTree<T>::leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//先左旋后右旋
		this->leftRotate(pre, pre->right);
		this->rightRotate(par, pre->parent);
	}

	template<typename T>
	void nmAVLTree<T>::rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		this->rightRotate(pre, pre->left);
		this->leftRotate(par, pre->parent);
	}

	template<typename T>
	void nmAVLTree<T>::updateHeight(mLib::nNode<T>* n)
	{
		if (n) n->height = std::max(this->getHeight(n->left), this->getHeight(n->right)) + 1;
	}

	template<typename T>
	int nmAVLTree<T>::getHeight(mLib::nNode<T>* n)
	{
		return (n) ? n->height : 0;
	}

	template<typename T>
	void nmAVLTree<T>::makeAVLValidIterFunc(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		while (par)
		{
			this->updateHeight(pre);
			this->updateHeight(par);
			pre = this->makeAVLValid(par, pre);
			par = pre->parent;
		}
		this->updateHeight(pre);
	}

	template<typename T>
	typename mLib::nNode<T>* nmAVLTree<T>::makeAVLValid(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		int parrRight = this->getHeight(par->right);
		int parlRight = this->getHeight(par->left);

		if (parrRight > (parlRight + 1))
		{
			//此处需要校准pre, 这是因为如果递归修改高度(例如删除操作中的), 可能导致当前pre是par的矮树
			pre = par->right;
			int prerRight = this->getHeight(pre->right);
			int prelRight = this->getHeight(pre->left);
			if (prerRight >= prelRight) this->leftRotate(par, pre);
			else if (prerRight < prelRight) this->rightleftRotate(par, pre);
			else throw "alg bug happened in nmAVLTree::makeAVLValid(when called func:insertpri)";
			return par->parent;
		}
		else if (parlRight > (parrRight + 1))
		{
			pre = par->left;
			int prerRight = this->getHeight(pre->right);
			int prelRight = this->getHeight(pre->left);
			if (prelRight >= prerRight) this->rightRotate(par, pre);
			else if (prelRight < prerRight) this->leftrightRotate(par, pre);
			else throw "alg bug happened in nmAVLTree::makeAVLValid(when called func:insertpri)";
			return par->parent;
		}
		return par;
	}

	template<typename T>
	bool nmAVLTree<T>::checkIfAVLValidpri(mLib::nNode<T>* n)
	{
		if (!n) return true;
		else
		{
			if (n->left && n != n->left->parent && n->val <= n->left->val) return false;
			if (n->right && n != n->right->parent && n->val >= n->left->val) return false;
			if (abs(this->getHeight(n->left) - this->getHeight(n->right)) > 1) return false;
			else return this->checkIfAVLValidpri(n->left) && this->checkIfAVLValidpri(n->right);
		}
	}

	template<typename T>
	bool nmAVLTree<T>::insert(T t)
	{
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> res = this->insertpri(t, this->head);
		if (res.first)
		{
			mLib::nNode<T>* par = res.second.first;
			mLib::nNode<T>* pre = res.second.second;
			//然后调整位置, 现在par是父亲节点, pre是新插入的节点(子节点)
			//以父亲节点为子节点，父亲的父亲节点为父亲节点，自下而上更新二叉树以满足高度关系
			this->makeAVLValidIterFunc(par, pre);
			return true;
		}
		else return false;
	}

	template<typename T>
	bool nmAVLTree<T>::remove(T t)
	{
		pair<bool, mLib::nNode<T>*> res = this->removepri(t, this->head);
		if (res.first)
		{
			mLib::nNode<T>* par = res.second;
			//然后调整位置, 现在par是被删除节点的父亲节点
			//如果par为空说明树被删除没了, 不操作
			if (!par);
			else if (par->left)  //把父亲节点作为par, 儿子节点作为另一个未删除的儿子(如果有的话), 检查AVL性质
				this->makeAVLValidIterFunc(par, par->left);
			else if (par->right)
				this->makeAVLValidIterFunc(par, par->right);
			else  //否则, 父亲节点作为pre, 父亲的父亲节点作为par, 检查AVL性质
				this->makeAVLValidIterFunc(par->parent, par);
			return true;
		}
		else return false;
	}

	template<typename T>
	bool nmAVLTree<T>::checkIfAVLValid()
	{
		return this->checkIfAVLValidpri(this->head);
	}
}

namespace mLib
{
	/*
	 * 自定义splay树
	 * 元素不可重复
	 * 内部在中序遍历输出时使用std::vector
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class nmSplayTree : public nmbinary_searchtree<T>
	{
	private:
		void moveNodeToTop(mLib::nNode<T>* pre);                 //将指定节点移动到根
	public:
		bool find(T t);                                       //重载父类方法, 查找值, 找得到则true, 否则false
		bool insert(T t);                                     //重载父类方法, 插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //重载父类方法, 删除值, 若已经存在则删除然后返回true, 否则返回false
		//检查Splay性质是否满足, 应当在树非空时调用, 只检查find/insert后那个新节点是不是根节点以及基本二叉搜索树性质
		bool checkIsSplayValid(T t);
	};

	template<typename T>
	void nmSplayTree<T>::moveNodeToTop(mLib::nNode<T> * pre)
	{
		while (this->head != pre)
		{
			mLib::nNode<T>* par = pre->parent;
			mLib::nNode<T>* gra = par->parent;
			//6种情况具体看配套PPT: SplayTree.pptx
			if (gra && gra->right == par && par->right == pre)
			{
				if (gra->parent && gra->parent->left == gra){
					gra->parent->left = pre; pre->parent = gra->parent;
				}
				else if (gra->parent && gra->parent->right == gra) {
					gra->parent->right = pre; pre->parent = gra->parent;
				}
				else{
					this->head = pre; pre->parent = nullptr;
				}
				par->right = pre->left;  if (pre->left) pre->left->parent = par;
				gra->right = par->left;  if (par->left) par->left->parent = gra;
				pre->left = par;  par->parent = pre;
				par->left = gra;  gra->parent = par;
			}
			else if (gra && gra->left == par && par->left == pre) 
			{
				if (gra->parent && gra->parent->left == gra) {
					gra->parent->left = pre; pre->parent = gra->parent;
				}
				else if (gra->parent && gra->parent->right == gra) {
					gra->parent->right = pre; pre->parent = gra->parent;
				}
				else {
					this->head = pre; pre->parent = nullptr;
				}
				par->left = pre->right; if (pre->right) pre->right->parent = par;
				gra->left = par->right; if (par->right) par->right->parent = gra;
				pre->right = par;  par->parent = pre;
				par->right = gra;  gra->parent = par;
			}
			else if (gra && gra->right == par && par->left == pre)
			{
				if (gra->parent && gra->parent->left == gra) {
					gra->parent->left = pre; pre->parent = gra->parent;
				}
				else if (gra->parent && gra->parent->right == gra) {
					gra->parent->right = pre; pre->parent = gra->parent;
				}
				else {
					this->head = pre; pre->parent = nullptr;
				}
				gra->right = pre->left; if (pre->left) pre->left->parent = gra;
				par->left = pre->right; if (pre->right) pre->right->parent = par;
				pre->right = par;  par->parent = pre;
				pre->left = gra;  gra->parent = pre;
			}
			else if (gra && gra->left == par && par->right == pre)
			{
				if (gra->parent && gra->parent->left == gra) {
					gra->parent->left = pre; pre->parent = gra->parent;
				}
				else if (gra->parent && gra->parent->right == gra) {
					gra->parent->right = pre; pre->parent = gra->parent;
				}
				else {
					this->head = pre; pre->parent = nullptr;
				}
				gra->left = pre->right;  if (pre->right) pre->right->parent = gra;
				par->right = pre->left;  if (pre->left) pre->left->parent = par;
				pre->left = par;  par->parent = pre;
				pre->right = gra;  gra->parent = pre;
			}
			else if (par->right == pre)
			{
				this->head = pre; pre->parent = nullptr;
				par->right = pre->left;  if (pre->left) pre->left->parent = par;
				pre->left = par; par->parent = pre;
			}
			else
			{
				this->head = pre; pre->parent = nullptr;
				par->left = pre->right;  if (pre->right) pre->right->parent = par;
				pre->right = par; par->parent = pre;
			}
		}
	}

	template<typename T>
	bool nmSplayTree<T>::find(T t)
	{
		mLib::nNode<T>* re = this->findinsert(t, this->head);
		if (re == nullptr || re->val != t) return false;
		else
		{
			this->moveNodeToTop(re);
			return true;
		}
	}

	template<typename T>
	bool nmSplayTree<T>::insert(T t)
	{
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> res = this->insertpri(t, this->head);
		if (res.first)
		{
			this->moveNodeToTop(res.second.second);
			return true;
		}
		else return false;
	}

	template<typename T>
	bool nmSplayTree<T>::remove(T t)
	{
		pair<bool, mLib::nNode<T>*> res = this->removepri(t, this->head);
		if (res.first)
		{
			if(res.second) this->moveNodeToTop(res.second);
			return true;
		}
		else return false;
	}

	template<typename T>
	bool nmSplayTree<T>::checkIsSplayValid(T t)
	{
		return this->checkIfTreeValidpri(this->head) && this->head && this->head->val == t;
	}

}

namespace mLib
{
	/*
	 * 自定义RedBlack树, 非继承版
	 * 元素不可重复
	 * 内部在中序遍历输出时使用std::vector
	 * 默认左<中<右, T必须是一个支持二元比较判断的类型
	 */
	template<typename T>
	class mRedBlackTree
	{
	private:
		//红黑树的颜色信息放到公共节点的height字段
		static const int BLACK = 0;
		static const int RED = 1;
		void recoverProperityInsert(mLib::nNode<T>* pre);
		void recoverProperityRemove(bool isColorBlack, mLib::nNode<T>* subPar, mLib::nNode<T>* subBro);
		bool checkIfRedBlackValidpri(mLib::nNode<T>* n, int& preBlackNodes, int& totalBlackNodes);      //内部函数测试红黑树性质是否满足
		void leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);        //左旋
		void rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);       //右旋
		void leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //左右旋
		void rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //右左旋

		mLib::nNode<T>* head;                    //根节点
		mLib::nNode<T>* findinsert(T t, mLib::nNode<T>* n);   //查找能插入位置的节点, 也就是最小的值>=n的节点, 不存在则为空
		mLib::nNode<T>* next(T t, mLib::nNode<T>* n);         //查找下一个节点, 找得到则返回此节点, 否则null
		void postorder_del(mLib::nNode<T>* n);   //后序遍历, 用于析构函数
		//内部函数插入值, pair:第一个是bool, 第二个是另一个pair表示它的父亲par, 和被插入节点pre, 若已经存在则返回false, nul, nul, 否则插入然后返回true, 俩节点
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> insertpri(T t, mLib::nNode<T>* n);
		//内部函数删除值, pair:第一个是bool, 第二个是一个pair,
		//  第一个是被删除节点的高度信息(也就是颜色), 第二个是一个长度为3的vector分别是:实际被删除节点的父亲par,
		//      subPar: 在删除情况1和4(有next移动中)中是实际被删除的节点的父亲, 在情况2-3是替代被删除节点的节点的父亲
		//      subBro: 在删除情况1和4(有next移动中)中是实际被删除的节点的父亲, 在情况2-3是替代被删除节点的节点的兄弟
		//    若已经存在则返回false, 全部都是nul, 否则删除然后返回true, 该节点
		pair<bool, pair<int, vector<mLib::nNode<T>*>>> removepri(T t, mLib::nNode<T>* n);
		void inorderpri(mLib::nNode<T>* n, std::vector<T>& res);      //内部函数中序遍历, 中左右

	public:
		mRedBlackTree();                                      //无操作
		~mRedBlackTree();                                     //后序遍历删除, 左右中
		bool find(T t);                                       //查找值, 找得到则true, 否则false
		bool insert(T t);                                     //插入值, 若已经存在则返回false, 否则插入然后返回true
		bool remove(T t);                                     //删除值, 若已经存在则删除然后返回true, 否则返回false
		std::vector<T> inorder();                             //中序遍历, 中左右
		bool checkIsRedBlackValid();                          //检查红黑树性质是否满足
	};

	template<typename T>
	void mRedBlackTree<T>::recoverProperityInsert(mLib::nNode<T>* pre)
	{
		if (this->head == pre)
		{
			pre->color = BLACK;
			return;
		}
		while (pre->color == RED && pre->parent && pre->parent->color == RED) {
			//…先获得par和gra
			mLib::nNode<T>* par = pre->parent;
			mLib::nNode<T>* gra = par->parent;

			//然后以下有8种情况: 用三位字母表示
			//第一位L或R表示父亲是祖父的哪个方向儿子
			//第二位L或R表示孙子是父亲的哪个方向儿子
			//第三位r或b表示祖父的另一个儿子的颜色, 除孙子父亲和祖父，其他4个节点颜色表示此子树根节点的颜色, 除祖父另一个儿子以外皆可能为空
			//pre: S, par:P, gra:G, 所有变化之后的图若G为根节点而图上是空色那么应改成黑色
		//LLr:
			if (pre == par->left && par == gra->left) 
			{
				if (gra->right && gra->right->color == RED) {
					par->color = BLACK;
					if (this->head != gra) gra->color = RED;
					gra->right->color = BLACK;
				}
				else {
					this->rightRotate(gra, par);
					par->color = BLACK;
					gra->color = RED;
				}
			}
		//LRr:
			else if (pre == par->right && par == gra->left)
			{
				if (gra->right && gra->right->color == RED) {
					par->color = BLACK;
					if (this->head != gra) gra->color = RED;
					gra->right->color = BLACK;
				}
				else {
					this->leftrightRotate(gra, par);
					pre->color = BLACK;
					gra->color = RED;
				}
			}
		//RLr:
			else if (pre == par->left && par == gra->right)
			{
				if (gra->left && gra->left->color == RED) {
					par->color = BLACK;
					if (this->head != gra) gra->color = RED;
					gra->left->color = BLACK;
				}
				else {
					this->rightleftRotate(gra, par);
					pre->color = BLACK;
					gra->color = RED;
				}
			}
		//RRr:
			else
			{
				if (gra->left && gra->left->color == RED) {
					par->color = BLACK;
					if (this->head != gra) gra->color = RED;
					gra->left->color = BLACK;
				}
				else {
					this->leftRotate(gra, par);
					par->color = BLACK;
					gra->color = RED;
				}
			}
			//	…最后pre = gra, 继续循环
			pre = gra;
		}
	}

	template<typename T>
	void mRedBlackTree<T>::recoverProperityRemove(bool isColorBlack, mLib::nNode<T>* subPar, mLib::nNode<T>* subBro)
	{
		if (!isColorBlack || this->head == nullptr) return;
		//…先获得par和bro
		mLib::nNode<T>* par = subPar;
		mLib::nNode<T>* bro = subBro;
		bool isDelRight = !par->right;
		while (true) {
			//…先获得par和bro和isDelRight, 如果不是第一次来到这个循环, 应该在上一个循环末尾continue之前更新, 否则应该是函数输入参数
			//然后以下有16个情况, 以Y表示删除的节点, B表示兄弟, P表示父亲, 以连线颜色表示下节点的颜色
			if (isDelRight)
			{
				if (bro->color == BLACK) {
					bool bLr = (bro->left && bro->left->color == RED);
					bool bRr = (bro->right && bro->right->color == RED);
				//Rb0://被删除的节点是右儿子, 兄弟是黑的, 有0个红儿子
					if (!bLr && !bRr) {
						bro->color = RED;
						if (par->color == RED) { 
							par->color = BLACK; break; 
						}
						else if (this->head != par) { 
							if (par != par->parent->left)
							{
								bro = par->parent->left;
								isDelRight = true;
							}
							else
							{
								bro = par->parent->right;
								isDelRight = false;
							}
							par = par->parent; continue;
						}
						else break;
					}
				//Rb1l://被删除的节点是右儿子, 兄弟是黑的, 有1个红儿子(左)
					else if (bLr && !bRr) {
						bro->color = par->color; bro->left->color = BLACK;
						par->color = BLACK; this->rightRotate(par, bro); break;
					}
				//Rb1r://被删除的节点是右儿子, 兄弟是黑的, 有1个红儿子(右)
				//Rb2://被删除的节点是右儿子, 兄弟是黑的, 有2个红儿子 这两情况处理方法一样的
					else {
						bro->right->color = par->color; par->color = BLACK;
						this->leftrightRotate(par, bro); break;
					}
				}
				else {
					mLib::nNode<T>* bR = bro->right;
					bool bRLr = (bR && bR->left && bR->left->color == RED);
					bool bRRr = (bR && bR->right && bR->right->color == RED);
				//RrR0://被删除的节点是右儿子, 兄弟是红的, 兄弟的右儿子有0个红儿子
					if (!bRLr && !bRRr) {
						bro->color = BLACK; bR->color = RED; this->rightRotate(par, bro); break;
					}
				//RrR1l://被删除的节点是右儿子, 兄弟是红的,兄弟的右儿子有1个红儿子(左)
					else if (bRLr && !bRRr) {
						bR->left->color = BLACK; this->leftrightRotate(par, bro); break;
					}
				//RrR1r://被删除的节点是右儿子, 兄弟是红的,兄弟的右儿子有1个红儿子(右)
				//Rr2://被删除的节点是右儿子, 兄弟是红的, 兄弟的右儿子有2个红儿子, 俩情况一样的
					else {
						mLib::nNode<T>* bRR = bR->right; bRR->color = BLACK;
						if (par->parent && par->parent->left == par) {
							par->parent->left = bRR; bRR->parent = par->parent;
						}
						else if (par->parent && par->parent->right == par) {
							par->parent->right = bRR; bRR->parent = par->parent;
						}
						else { this->head = bRR; bRR->parent = nullptr; }
						par->left = bRR->right; if(bRR->right) bRR->right->parent = par;
						bRR->right = par; par->parent = bRR;
						bR->right = bRR->left; if (bRR->left) bRR->left->parent = bR;
						bRR->left = bro; bro->parent = bRR;
						break;
					}
				}
			}
			else
			{
				if (bro->color == BLACK) {
					bool bLr = (bro->left && bro->left->color == RED);
					bool bRr = (bro->right && bro->right->color == RED);
				//Lb0://被删除的节点是左儿子, 兄弟是黑的, 有0个红儿子
					if (!bLr && !bRr) {
						bro->color = RED;
						if (par->color == RED) { par->color = BLACK; break; }
						else if (this->head != par) { 
							if (par != par->parent->left)
							{
								bro = par->parent->left;
								isDelRight = true;
							}
							else
							{
								bro = par->parent->right;
								isDelRight = false;
							}
							par = par->parent; continue; 
						}
						else break;
					}
				//Lb1l://被删除的节点是左儿子, 兄弟是黑的, 有1个红儿子(右)
					else if (!bLr && bRr) {
						bro->color = par->color; bro->right->color = BLACK;
						par->color = BLACK; this->leftRotate(par, bro); break;
					}
				//Lb1r://被删除的节点是左儿子, 兄弟是黑的, 有1个红儿子(左)
				//Lb2://被删除的节点是左儿子, 兄弟是黑的, 有2个红儿子 这两情况处理方法一样的
					else {
						bro->left->color = par->color; par->color = BLACK;
						this->rightleftRotate(par, bro); break;
					}
				}
				else {
					mLib::nNode<T>* bL = bro->left;
					bool bLLr = (bL && bL->left && bL->left->color == RED);
					bool bLRr = (bL && bL->right && bL->right->color == RED);
				//LrR0://被删除的节点是右儿子, 兄弟是红的, 兄弟的右儿子有0个红儿子
					if (!bLLr && !bLRr) {
						bro->color = BLACK; bL->color = RED; this->leftRotate(par, bro); break;
					}
				//LrR1l://被删除的节点是右儿子, 兄弟是红的,兄弟的右儿子有1个红儿子(右)
					else if (!bLLr && bLRr) {
						bL->right->color = BLACK; this->rightleftRotate(par, bro); break;
					}
				//LrR1r://被删除的节点是左儿子, 兄弟是红的,兄弟的左儿子有1个红儿子(左)
				//Lr2://被删除的节点是左儿子, 兄弟是红的, 兄弟的左儿子有2个红儿子, 俩情况一样的
					else {
						mLib::nNode<T>* bLL = bL->left; bLL->color = BLACK;
						if (par->parent && par->parent->left == par) {
							par->parent->left = bLL; bLL->parent = par->parent;
						}
						else if (par->parent && par->parent->right == par) {
							par->parent->right = bLL; bLL->parent = par->parent;
						}
						else { this->head = bLL; bLL->parent = nullptr; }
						par->right = bLL->left; if (bLL->left) bLL->left->parent = par;
						bLL->left = par; par->parent = bLL;
						bL->left = bLL->right; if (bLL->right) bLL->right->parent = bL;
						bLL->right = bro; bro->parent = bLL;
						break;
					}
				}
			}
		}
	}

	template<typename T>
	bool mRedBlackTree<T>::checkIfRedBlackValidpri(mLib::nNode<T>* n, int& preBlackNodes, int& totalBlackNodes)
	{
		if (!n)
		{
			if (totalBlackNodes == 0) totalBlackNodes = preBlackNodes;
			assert(totalBlackNodes == preBlackNodes);
			return true;
		}
		else
		{
			if (n->left && n != n->left->parent && n->val <= n->left->val) return false;
			if (n->right && n != n->right->parent && n->val >= n->left->val) return false;
			if (n->color == BLACK)
			{
				preBlackNodes++;
				bool res = this->checkIfRedBlackValidpri(n->left, preBlackNodes, totalBlackNodes) &&
					this->checkIfRedBlackValidpri(n->right, preBlackNodes, totalBlackNodes);
				preBlackNodes--;
				return res;
			}
			else if (n->color == RED)
			{
				bool res = this->checkIfRedBlackValidpri(n->left, preBlackNodes, totalBlackNodes) &&
					this->checkIfRedBlackValidpri(n->right, preBlackNodes, totalBlackNodes);
				return res;
			}
			else
			{
				assert(-1);
				return false;
			}
		}
	}

	template<typename T>
	void mRedBlackTree<T>::leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//预处理
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//拆开父亲和右儿子
		par->right = pre->left;
		if (pre->left) pre->left->parent = par;
		//反转父亲和右儿子的关系
		pre->left = par;
		par->parent = pre;
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
	void mRedBlackTree<T>::rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//预处理
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//拆开父亲和左儿子
		par->left = pre->right;
		if (pre->right) pre->right->parent = par;
		//反转父亲和左儿子的关系
		pre->right = par;
		par->parent = pre;
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
	void mRedBlackTree<T>::leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//先左旋后右旋
		this->leftRotate(pre, pre->right);
		this->rightRotate(par, pre->parent);
	}

	template<typename T>
	void mRedBlackTree<T>::rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		this->rightRotate(pre, pre->left);
		this->leftRotate(par, pre->parent);
	}

	template<typename T>
	mLib::nNode<T>* mRedBlackTree<T>::findinsert(T t, mLib::nNode<T>* n)
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
	mLib::nNode<T>* mRedBlackTree<T>::next(T t, mLib::nNode<T>* n)
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
			mLib::nNode<T>* old = n;
			mLib::nNode<T>* pre = n->parent;
			while (pre && pre->right == old)   //如果pre=nullptr退出说明没有next了
			{
				old = pre;
				pre = pre->parent;
			}
			return pre;
		}
	}

	template<typename T>
	void mRedBlackTree<T>::postorder_del(mLib::nNode<T>* n)
	{
		if (!n) return;
		if (n->left) postorder_del(n->left);
		if (n->right) postorder_del(n->right);
		delete n;
	}

	template<typename T>
	pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
		mRedBlackTree<T>::insertpri(T t, mLib::nNode<T>* n)
	{
		if (!n)
		{
			this->head = new mLib::nNode<T>(t);
			return pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
			{true, { nullptr, this->head }};
		}
		else
		{
			mLib::nNode<T>* par = nullptr;
			mLib::nNode<T>* pre = this->head;
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
				else return pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
				{false, { nullptr, nullptr }};
			}
			if (par->val > t)
			{
				par->left = new mLib::nNode<T>(t);
				par->left->parent = par;
				pre = par->left;
			}
			else
			{
				par->right = new mLib::nNode<T>(t);
				par->right->parent = par;
				pre = par->right;
			}
			return pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>>
			{true, { par, pre }};
		}
	}

	template<typename T>
	pair<bool, pair<int, vector<mLib::nNode<T>*>>> mRedBlackTree<T>::removepri(T t, mLib::nNode<T>* n)
	{
		if (!n) return pair<bool, pair<int, vector<mLib::nNode<T>*>>>{false, { -1 , vector<mLib::nNode<T>*> {} }};
		else
		{
			mLib::nNode<T>* par = n->parent;
			mLib::nNode<T>* pre = n;
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
					mLib::nNode<T>* del = pre;
					mLib::nNode<T>* subPar;
					mLib::nNode<T>* subBro;
					int delcolor;
					bool DirectDelNode = false;
					if (!pre->left && !pre->right) //左右儿子都空, 直接删
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delcolor = del->color;
						subPar = par;
						subBro = (par) ? ((par->left) ? par->left : par->right) : nullptr;
						delete del;
					}
					else if (!pre->left) //左儿子为空, 把右儿子移过来
					{
						delcolor = pre->right->color;
						pre->right->color = pre->color;
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
						else
						{
							this->head = pre->right;
							this->head->parent = nullptr;
						}
						subPar = par;
						subBro = (par) ? ((par->left != pre->right) ? par->left : par->right) : nullptr;
						par = pre->right;
						delete del;
					}
					else if (!pre->right)  //右儿子为空, 把左儿子移过来
					{
						delcolor = pre->left->color;
						pre->left->color = pre->color;
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
						else
						{
							this->head = pre->left;
							this->head->parent = nullptr;
						}
						subPar = par;
						subBro = (par) ? ((par->left != pre->left) ? par->left : par->right) : nullptr;
						par = pre->left;
						delete del;
					}
					else //两儿子都不空, 寻找下一个节点next, 替换过来, 然后删除下一个节点, 注意:下一个节点一定没有左儿子!但可能有右儿子
					{
						//寻找下一个节点
						mLib::nNode<T>* next = pre->right;  //此步骤一定存在, next不可能为空
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//修改next节点相关关系
						if (next == par->left)
						{
							subPar = par;
							subBro = par->right;
							par->left = next->right;
							if (next->right)
							{
								delcolor = next->right->color;
								next->right->color = next->color;
								next->right->parent = par;
							}
							else delcolor = next->color;
						}
						else
						{
							subPar = par;
							subBro = par->left;
							par->right = next->right;
							if (next->right)
							{
								delcolor = next->right->color;
								next->right->color = next->color;
								next->right->parent = par;
							}
							else delcolor = next->color;
						}
						del = next;
						delete del;
					}
					return pair<bool, pair<int, vector<mLib::nNode<T>*>>>{true, { delcolor , vector<mLib::nNode<T>*> { par, subPar, subBro }}};
				}
			}
		}
		return pair<bool, pair<int, vector<mLib::nNode<T>*>>>{false, { -1 , vector<mLib::nNode<T>*> {} }};
	}

	template<typename T>
	void mRedBlackTree<T>::inorderpri(mLib::nNode<T>* n, std::vector<T>& res)
	{
		if (!n) return;
		if (n->left) this->inorderpri(n->left, res);
		res.emplace_back(n->val);
		if (n->right) this->inorderpri(n->right, res);
	}

	template<typename T>
	mRedBlackTree<T>::mRedBlackTree()
	{
		;
	}

	template<typename T>
	mRedBlackTree<T>::~mRedBlackTree()
	{
		this->postorder_del(this->head);
	}

	template<typename T>
	bool mRedBlackTree<T>::find(T t)
	{
		mLib::nNode<T>* re = this->findinsert(t, this->head);
		return (re == nullptr || re->val != t) ? false : true;
	}





	template<typename T>
	bool mRedBlackTree<T>::insert(T t)
	{
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> res = this->insertpri(t, this->head);
		if (res.first)
		{
			mLib::nNode<T>* par = res.second.first;
			mLib::nNode<T>* pre = res.second.second;
			//然后调整位置和颜色, 现在par是父亲节点, pre是新插入的节点(子节点)
			pre->color = RED;
			this->recoverProperityInsert(pre);
			return true;
		}
		else return false;
	}

	template<typename T>
	bool mRedBlackTree<T>::remove(T t)
	{
		pair<bool, pair<int, vector<mLib::nNode<T>*>>> res = this->removepri(t, this->head);
		if (res.first)
		{
			mLib::nNode<T>* subPar = res.second.second[1];
			mLib::nNode<T>* subBro = res.second.second[2];
			assert(!subBro || subBro->parent == subPar);
			//然后调整位置和颜色, 现在subPar是被删除节点的替换位置的父亲节点
			//然后调整位置和颜色, 现在subBro是被删除节点的替换位置的兄弟节点
			bool isColorBlack = (res.second.first == BLACK);
			this->recoverProperityRemove(isColorBlack, subPar, subBro);
			return true;
		}
		else return false;
	}

	template<typename T>
	std::vector<T> mRedBlackTree<T>::inorder()
	{
		std::vector<T> res;
		this->inorderpri(this->head, res);
		return res;
	}

	template<typename T>
	bool mRedBlackTree<T>::checkIsRedBlackValid()
	{
		if (this->head)
		{
			assert(this->head->height == BLACK);
			int preBlackNodes = 0;
			int totalBlackNodes = 0;
			return this->checkIfRedBlackValidpri(this->head, preBlackNodes, totalBlackNodes);
		}
		else return true;
	}

}






