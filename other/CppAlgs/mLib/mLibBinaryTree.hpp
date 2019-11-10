#pragma once

#include "mLibvector.hpp"
#include "../public/public.hpp"

namespace mLib
{
	template<typename T>
	struct nNode   //�����ڵ�
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

//�����Ƕ�����������AVL�����ڵ��������ڲ�

namespace mLib
{
	/*
	 * �Զ������������
	 * Ԫ�ز����ظ�
	 * �ڲ�������������ʱʹ��std::vector
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
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
		mbinary_searchtree<T>::Node* head;                    //���ڵ�
	private:
		mbinary_searchtree<T>::Node* findinsert(T t, mbinary_searchtree<T>::Node* n);   //�����ܲ���λ�õĽڵ�, Ҳ������С��ֵ>=n�Ľڵ�, ��������Ϊ��
		mbinary_searchtree<T>::Node* next(T t, mbinary_searchtree<T>::Node* n);         //������һ���ڵ�, �ҵõ��򷵻ش˽ڵ�, ����null
		void postorder_del(mbinary_searchtree<T>::Node* n);   //�������, ������������
		//�ڲ���������ֵ, pair:��һ����bool, �ڶ�������һ��pair��ʾ���ĸ���par, �ͱ�����ڵ�pre, ���Ѿ������򷵻�false, nul, nul, �������Ȼ�󷵻�true, ���ڵ�
		pair<bool, pair<mbinary_searchtree<T>::Node*, mbinary_searchtree<T>::Node*>> insertpri(T t, mbinary_searchtree<T>::Node* n);
		//�ڲ���������ֵ, pair:��һ����bool, �ڶ�����ɾ���ڵ�ĸ���par, ���Ѿ������򷵻�false, nul, �������Ȼ�󷵻�true, �ýڵ�
		pair<bool, mbinary_searchtree<T>::Node*> removepri(T t, mbinary_searchtree<T>::Node* n);
		void inorderpri(mbinary_searchtree<T>::Node* n, std::vector<T>& res);      //�ڲ������������, ������
		bool checkIfTreeValidpri(mbinary_searchtree<T>::Node* n);          //�ڲ����������������Ƿ�����
	public:
		mbinary_searchtree();                                 //�޲���
		~mbinary_searchtree();                                //�������ɾ��, ������

		bool find(T t);                                       //����ֵ, �ҵõ���true, ����false
		mLib::mvector<T> RangeSearch(T le, T ri);             //��Χ����, ����ֵ�Ĵ�С��[le, ri]��Χ�ڵ�ֵ����
		bool insert(T t);                                     //����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		std::vector<T> inorder();                             //�������, ������
		bool checkIfTreeValid();                              //�����������Ƿ�����
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
					if (!pre->left && !pre->right) //���Ҷ��Ӷ���, ֱ��ɾ
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delete del;
					}
					else if (!pre->left) //�����Ϊ��, ���Ҷ����ƹ���
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
					else if (!pre->right)  //�Ҷ���Ϊ��, ��������ƹ���
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
					else //�����Ӷ�����, Ѱ����һ���ڵ�next, �滻����, Ȼ��ɾ����һ���ڵ�, ע��:��һ���ڵ�һ��û�������!���������Ҷ���
					{
						//Ѱ����һ���ڵ�
						Node* next = pre->right;  //�˲���һ������, next������Ϊ��
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//�޸�next�ڵ���ع�ϵ
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
	 * �Զ���AVL��������Ӧ����������
	 * Ԫ�ز����ظ�
	 * �ڲ�������������ʱʹ��std::vector
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
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
		mAVLtree<T>::Node* head;                    //���ڵ�
		mAVLtree<T>::Node* findinsert(T t, mAVLtree<T>::Node* n);   //�����ܲ���λ�õĽڵ�, Ҳ������С��ֵ>=n�Ľڵ�, ��������Ϊ��
		mAVLtree<T>::Node* next(T t, mAVLtree<T>::Node* n);         //������һ���ڵ�, �ҵõ��򷵻ش˽ڵ�, ����null
		void postorder_del(mAVLtree<T>::Node* n);   //�������, ������������
		bool insertpri(T t, mAVLtree<T>::Node* n);  //�ڲ���������ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool removepri(T t, mAVLtree<T>::Node* n);  //�ڲ�����ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		void inorderpri(mAVLtree<T>::Node* n, std::vector<T>& res);      //�ڲ������������, ������

		void leftRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);        //����
		void rightRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);       //����
		void leftrightRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);   //������
		void rightleftRotate(mAVLtree<T>::Node* par, mAVLtree<T>::Node* son);   //������

		void updateHeight(mAVLtree<T>::Node* n);    //���¸߶�
		int getHeight(mAVLtree<T>::Node* n);       //��ȡ�߶ȣ�����ǿ�ָ����ô����0�������ǽڵ�ĸ߶�
		void makeAVLValidIterFunc(mAVLtree<T>::Node* par, mAVLtree<T>::Node* pre);   //�����ڲ������Ե������޸�AVL����

		mAVLtree<T>::Node* makeAVLValid(mAVLtree<T>::Node* par, mAVLtree<T>::Node* pre);   //ʹAVL��������, �������������ĸ��׽ڵ�
		bool checkIfAVLValidpri(mAVLtree<T>::Node* n);                //�ڲ���������AVL�����Ƿ�����

	public:
		mAVLtree();                                 //�޲���
		~mAVLtree();                                //�������ɾ��, ������

		bool find(T t);                                       //����ֵ, �ҵõ���true, ����false
		mLib::mvector<T> RangeSearch(T le, T ri);             //��Χ����, ����ֵ�Ĵ�С��[le, ri]��Χ�ڵ�ֵ����
		bool insert(T t);                                     //����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		std::vector<T> inorder();                             //�������, ������
		bool checkIfAVLValid();                                  //����AVL�����Ƿ�����
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
			while (pre && pre->right == old)   //���pre=nullptr�˳�˵��û��next��
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
			//�Ȱ�������������������, ͬʱ���½��Ľڵ�߶ȸ�ֵΪ1
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
			//Ȼ�����λ��, ����par�Ǹ��׽ڵ�, pre���²���Ľڵ�(�ӽڵ�)
			//�Ը��׽ڵ�Ϊ�ӽڵ㣬���׵ĸ��׽ڵ�Ϊ���׽ڵ㣬���¶��ϸ��¶�����������߶ȹ�ϵ
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
			//�Ȱ�������������ɾ������ɾ��һ���ڵ�
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
					if (!pre->left && !pre->right) //���Ҷ��Ӷ���, ֱ��ɾ
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delete del;
					}
					else if (!pre->left) //�����Ϊ��, ���Ҷ����ƹ���
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
					else if (!pre->right)  //�Ҷ���Ϊ��, ��������ƹ���
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
					else //�����Ӷ�����, Ѱ����һ���ڵ�next, �滻����, Ȼ��ɾ����һ���ڵ�, ע��:��һ���ڵ�һ��û�������!���������Ҷ���
					{
						//Ѱ����һ���ڵ�
						Node* next = pre->right;  //�˲���һ������, next������Ϊ��
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//�޸�next�ڵ���ع�ϵ
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
					//Ȼ�����λ��, ����par�Ǳ�ɾ���ڵ�ĸ��׽ڵ�
					//���parΪ��˵������ɾ��û��, ������
					if (!par);
					else if (par->left)  //�Ѹ��׽ڵ���Ϊpar, ���ӽڵ���Ϊ��һ��δɾ���Ķ���(����еĻ�), ���AVL����
						this->makeAVLValidIterFunc(par, par->left);
					else if (par->right)
						this->makeAVLValidIterFunc(par, par->right);
					else  //����, ���׽ڵ���Ϊpre, ���׵ĸ��׽ڵ���Ϊpar, ���AVL����
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
		//Ԥ����
		Node* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//�𿪸��׺��Ҷ���
		par->right = pre->left;
		if (pre->left) pre->left->parent = par;
		//��ת���׺��Ҷ��ӵĹ�ϵ
		pre->left = par;
		par->parent = pre;
		//����
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
		//Ԥ����
		Node* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//�𿪸��׺������
		par->left = pre->right;
		if (pre->right) pre->right->parent = par;
		//��ת���׺�����ӵĹ�ϵ
		pre->right = par;
		par->parent = pre;
		//����
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
		//������������
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
			//�˴���ҪУ׼pre, ������Ϊ����ݹ��޸ĸ߶�(����ɾ�������е�), ���ܵ��µ�ǰpre��par�İ���
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

//�����Ƕ���������/AVL��/Splay��/RedBlack�����ڵ��������ⲿ����ͬ�ṹ��

namespace mLib
{
	/*
	 * �Զ������������
	 * Ԫ�ز����ظ�
	 * �ڲ�������������ʱʹ��std::vector
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
	 */
	template<typename T>
	class nmbinary_searchtree
	{
	protected:
		mLib::nNode<T>* head;                    //���ڵ�
		mLib::nNode<T>* findinsert(T t, mLib::nNode<T>* n);   //�����ܲ���λ�õĽڵ�, Ҳ������С��ֵ>=n�Ľڵ�, ��������Ϊ��
		mLib::nNode<T>* next(T t, mLib::nNode<T>* n);         //������һ���ڵ�, �ҵõ��򷵻ش˽ڵ�, ����null
		void postorder_del(mLib::nNode<T>* n);   //�������, ������������
		//�ڲ���������ֵ, pair:��һ����bool, �ڶ�������һ��pair��ʾ���ĸ���par, �ͱ�����ڵ�pre, ���Ѿ������򷵻�false, nul, nul, �������Ȼ�󷵻�true, ���ڵ�
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> insertpri(T t, mLib::nNode<T>* n);
		//�ڲ�����ɾ��ֵ, pair:��һ����bool, ʵ�ʱ�ɾ���ڵ�ĸ���par
		pair<bool, mLib::nNode<T>*> removepri(T t, mLib::nNode<T>* n);
		void inorderpri(mLib::nNode<T>* n, std::vector<T>& res);      //�ڲ������������, ������
		bool checkIfTreeValidpri(mLib::nNode<T>* n);          //�ڲ����������������Ƿ�����
	public:
		nmbinary_searchtree();                                 //�޲���
		~nmbinary_searchtree();                                //�������ɾ��, ������

		bool find(T t);                                       //����ֵ, �ҵõ���true, ����false
		mLib::mvector<T> RangeSearch(T le, T ri);             //��Χ����, ����ֵ�Ĵ�С��[le, ri]��Χ�ڵ�ֵ����
		bool insert(T t);                                     //����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		std::vector<T> inorder();                             //�������, ������
		bool checkIfTreeValid();                              //�����������Ƿ�����
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
			while (pre && pre->right == old)   //���pre=nullptr�˳�˵��û��next��
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
					if (!pre->left && !pre->right) //���Ҷ��Ӷ���, ֱ��ɾ
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delheight = del->height;
						subPar = par;
						subBro = (par) ? ((par->left) ? par->left : par->right) : nullptr;
						delete del;
					}
					else if (!pre->left) //�����Ϊ��, ���Ҷ����ƹ���
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
					else if (!pre->right)  //�Ҷ���Ϊ��, ��������ƹ���
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
					else //�����Ӷ�����, Ѱ����һ���ڵ�next, �滻����, Ȼ��ɾ����һ���ڵ�, ע��:��һ���ڵ�һ��û�������!���������Ҷ���
					{
						//Ѱ����һ���ڵ�
						mLib::nNode<T>* next = pre->right;  //�˲���һ������, next������Ϊ��
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//�޸�next�ڵ���ع�ϵ
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
	 * �Զ���AVL��������Ӧ����������
	 * Ԫ�ز����ظ�
	 * �ڲ�������������ʱʹ��std::vector
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
	 */
	template<typename T>
	class nmAVLTree : public mLib::nmbinary_searchtree<T>
	{
	protected:
		void leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);        //����
		void rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);       //����
		void leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //������
		void rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //������
	private:
		void updateHeight(mLib::nNode<T>* n);    //���¸߶�
		int getHeight(mLib::nNode<T>* n);       //��ȡ�߶ȣ�����ǿ�ָ����ô����0�������ǽڵ�ĸ߶�
		void makeAVLValidIterFunc(mLib::nNode<T>* par, mLib::nNode<T>* pre);   //�����ڲ������Ե������޸�AVL����

		mLib::nNode<T>* makeAVLValid(mLib::nNode<T>* par, mLib::nNode<T>* pre);   //ʹAVL��������, �������������ĸ��׽ڵ�
		bool checkIfAVLValidpri(mLib::nNode<T>* n);   //�ڲ���������AVL�����Ƿ�����
	public:
		bool checkIfAVLValid();                               //����AVL�����Ƿ�����
		bool insert(T t);                                     //���ظ��෽��, ����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //���ظ��෽��, ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
	};

	template<typename T>
	void nmAVLTree<T>::leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* pre)
	{
		//Ԥ����
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//�𿪸��׺��Ҷ���
		par->right = pre->left;
		if (pre->left) pre->left->parent = par;
		//��ת���׺��Ҷ��ӵĹ�ϵ
		pre->left = par;
		par->parent = pre;
		//����
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
		//Ԥ����
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//�𿪸��׺������
		par->left = pre->right;
		if (pre->right) pre->right->parent = par;
		//��ת���׺�����ӵĹ�ϵ
		pre->right = par;
		par->parent = pre;
		//����
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
		//������������
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
			//�˴���ҪУ׼pre, ������Ϊ����ݹ��޸ĸ߶�(����ɾ�������е�), ���ܵ��µ�ǰpre��par�İ���
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
			//Ȼ�����λ��, ����par�Ǹ��׽ڵ�, pre���²���Ľڵ�(�ӽڵ�)
			//�Ը��׽ڵ�Ϊ�ӽڵ㣬���׵ĸ��׽ڵ�Ϊ���׽ڵ㣬���¶��ϸ��¶�����������߶ȹ�ϵ
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
			//Ȼ�����λ��, ����par�Ǳ�ɾ���ڵ�ĸ��׽ڵ�
			//���parΪ��˵������ɾ��û��, ������
			if (!par);
			else if (par->left)  //�Ѹ��׽ڵ���Ϊpar, ���ӽڵ���Ϊ��һ��δɾ���Ķ���(����еĻ�), ���AVL����
				this->makeAVLValidIterFunc(par, par->left);
			else if (par->right)
				this->makeAVLValidIterFunc(par, par->right);
			else  //����, ���׽ڵ���Ϊpre, ���׵ĸ��׽ڵ���Ϊpar, ���AVL����
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
	 * �Զ���splay��
	 * Ԫ�ز����ظ�
	 * �ڲ�������������ʱʹ��std::vector
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
	 */
	template<typename T>
	class nmSplayTree : public nmbinary_searchtree<T>
	{
	private:
		void moveNodeToTop(mLib::nNode<T>* pre);                 //��ָ���ڵ��ƶ�����
	public:
		bool find(T t);                                       //���ظ��෽��, ����ֵ, �ҵõ���true, ����false
		bool insert(T t);                                     //���ظ��෽��, ����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //���ظ��෽��, ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		//���Splay�����Ƿ�����, Ӧ�������ǿ�ʱ����, ֻ���find/insert���Ǹ��½ڵ��ǲ��Ǹ��ڵ��Լ�������������������
		bool checkIsSplayValid(T t);
	};

	template<typename T>
	void nmSplayTree<T>::moveNodeToTop(mLib::nNode<T> * pre)
	{
		while (this->head != pre)
		{
			mLib::nNode<T>* par = pre->parent;
			mLib::nNode<T>* gra = par->parent;
			//6��������忴����PPT: SplayTree.pptx
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
	 * �Զ���RedBlack��, �Ǽ̳а�
	 * Ԫ�ز����ظ�
	 * �ڲ�������������ʱʹ��std::vector
	 * Ĭ����<��<��, T������һ��֧�ֶ�Ԫ�Ƚ��жϵ�����
	 */
	template<typename T>
	class mRedBlackTree
	{
	private:
		//���������ɫ��Ϣ�ŵ������ڵ��height�ֶ�
		static const int BLACK = 0;
		static const int RED = 1;
		void recoverProperityInsert(mLib::nNode<T>* pre);
		void recoverProperityRemove(bool isColorBlack, mLib::nNode<T>* subPar, mLib::nNode<T>* subBro);
		bool checkIfRedBlackValidpri(mLib::nNode<T>* n, int& preBlackNodes, int& totalBlackNodes);      //�ڲ��������Ժ���������Ƿ�����
		void leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);        //����
		void rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);       //����
		void leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //������
		void rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //������

		mLib::nNode<T>* head;                    //���ڵ�
		mLib::nNode<T>* findinsert(T t, mLib::nNode<T>* n);   //�����ܲ���λ�õĽڵ�, Ҳ������С��ֵ>=n�Ľڵ�, ��������Ϊ��
		mLib::nNode<T>* next(T t, mLib::nNode<T>* n);         //������һ���ڵ�, �ҵõ��򷵻ش˽ڵ�, ����null
		void postorder_del(mLib::nNode<T>* n);   //�������, ������������
		//�ڲ���������ֵ, pair:��һ����bool, �ڶ�������һ��pair��ʾ���ĸ���par, �ͱ�����ڵ�pre, ���Ѿ������򷵻�false, nul, nul, �������Ȼ�󷵻�true, ���ڵ�
		pair<bool, pair<mLib::nNode<T>*, mLib::nNode<T>*>> insertpri(T t, mLib::nNode<T>* n);
		//�ڲ�����ɾ��ֵ, pair:��һ����bool, �ڶ�����һ��pair,
		//  ��һ���Ǳ�ɾ���ڵ�ĸ߶���Ϣ(Ҳ������ɫ), �ڶ�����һ������Ϊ3��vector�ֱ���:ʵ�ʱ�ɾ���ڵ�ĸ���par,
		//      subPar: ��ɾ�����1��4(��next�ƶ���)����ʵ�ʱ�ɾ���Ľڵ�ĸ���, �����2-3�������ɾ���ڵ�Ľڵ�ĸ���
		//      subBro: ��ɾ�����1��4(��next�ƶ���)����ʵ�ʱ�ɾ���Ľڵ�ĸ���, �����2-3�������ɾ���ڵ�Ľڵ���ֵ�
		//    ���Ѿ������򷵻�false, ȫ������nul, ����ɾ��Ȼ�󷵻�true, �ýڵ�
		pair<bool, pair<int, vector<mLib::nNode<T>*>>> removepri(T t, mLib::nNode<T>* n);
		void inorderpri(mLib::nNode<T>* n, std::vector<T>& res);      //�ڲ������������, ������

	public:
		mRedBlackTree();                                      //�޲���
		~mRedBlackTree();                                     //�������ɾ��, ������
		bool find(T t);                                       //����ֵ, �ҵõ���true, ����false
		bool insert(T t);                                     //����ֵ, ���Ѿ������򷵻�false, �������Ȼ�󷵻�true
		bool remove(T t);                                     //ɾ��ֵ, ���Ѿ�������ɾ��Ȼ�󷵻�true, ���򷵻�false
		std::vector<T> inorder();                             //�������, ������
		bool checkIsRedBlackValid();                          //������������Ƿ�����
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
			//���Ȼ��par��gra
			mLib::nNode<T>* par = pre->parent;
			mLib::nNode<T>* gra = par->parent;

			//Ȼ��������8�����: ����λ��ĸ��ʾ
			//��һλL��R��ʾ�������游���ĸ��������
			//�ڶ�λL��R��ʾ�����Ǹ��׵��ĸ��������
			//����λr��b��ʾ�游����һ�����ӵ���ɫ, �����Ӹ��׺��游������4���ڵ���ɫ��ʾ���������ڵ����ɫ, ���游��һ����������Կ���Ϊ��
			//pre: S, par:P, gra:G, ���б仯֮���ͼ��GΪ���ڵ��ͼ���ǿ�ɫ��ôӦ�ĳɺ�ɫ
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
			//	�����pre = gra, ����ѭ��
			pre = gra;
		}
	}

	template<typename T>
	void mRedBlackTree<T>::recoverProperityRemove(bool isColorBlack, mLib::nNode<T>* subPar, mLib::nNode<T>* subBro)
	{
		if (!isColorBlack || this->head == nullptr) return;
		//���Ȼ��par��bro
		mLib::nNode<T>* par = subPar;
		mLib::nNode<T>* bro = subBro;
		bool isDelRight = !par->right;
		while (true) {
			//���Ȼ��par��bro��isDelRight, ������ǵ�һ���������ѭ��, Ӧ������һ��ѭ��ĩβcontinue֮ǰ����, ����Ӧ���Ǻ����������
			//Ȼ��������16�����, ��Y��ʾɾ���Ľڵ�, B��ʾ�ֵ�, P��ʾ����, ��������ɫ��ʾ�½ڵ����ɫ
			if (isDelRight)
			{
				if (bro->color == BLACK) {
					bool bLr = (bro->left && bro->left->color == RED);
					bool bRr = (bro->right && bro->right->color == RED);
				//Rb0://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻڵ�, ��0�������
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
				//Rb1l://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻڵ�, ��1�������(��)
					else if (bLr && !bRr) {
						bro->color = par->color; bro->left->color = BLACK;
						par->color = BLACK; this->rightRotate(par, bro); break;
					}
				//Rb1r://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻڵ�, ��1�������(��)
				//Rb2://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻڵ�, ��2������� �������������һ����
					else {
						bro->right->color = par->color; par->color = BLACK;
						this->leftrightRotate(par, bro); break;
					}
				}
				else {
					mLib::nNode<T>* bR = bro->right;
					bool bRLr = (bR && bR->left && bR->left->color == RED);
					bool bRRr = (bR && bR->right && bR->right->color == RED);
				//RrR0://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻ��, �ֵܵ��Ҷ�����0�������
					if (!bRLr && !bRRr) {
						bro->color = BLACK; bR->color = RED; this->rightRotate(par, bro); break;
					}
				//RrR1l://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻ��,�ֵܵ��Ҷ�����1�������(��)
					else if (bRLr && !bRRr) {
						bR->left->color = BLACK; this->leftrightRotate(par, bro); break;
					}
				//RrR1r://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻ��,�ֵܵ��Ҷ�����1�������(��)
				//Rr2://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻ��, �ֵܵ��Ҷ�����2�������, �����һ����
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
				//Lb0://��ɾ���Ľڵ��������, �ֵ��Ǻڵ�, ��0�������
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
				//Lb1l://��ɾ���Ľڵ��������, �ֵ��Ǻڵ�, ��1�������(��)
					else if (!bLr && bRr) {
						bro->color = par->color; bro->right->color = BLACK;
						par->color = BLACK; this->leftRotate(par, bro); break;
					}
				//Lb1r://��ɾ���Ľڵ��������, �ֵ��Ǻڵ�, ��1�������(��)
				//Lb2://��ɾ���Ľڵ��������, �ֵ��Ǻڵ�, ��2������� �������������һ����
					else {
						bro->left->color = par->color; par->color = BLACK;
						this->rightleftRotate(par, bro); break;
					}
				}
				else {
					mLib::nNode<T>* bL = bro->left;
					bool bLLr = (bL && bL->left && bL->left->color == RED);
					bool bLRr = (bL && bL->right && bL->right->color == RED);
				//LrR0://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻ��, �ֵܵ��Ҷ�����0�������
					if (!bLLr && !bLRr) {
						bro->color = BLACK; bL->color = RED; this->leftRotate(par, bro); break;
					}
				//LrR1l://��ɾ���Ľڵ����Ҷ���, �ֵ��Ǻ��,�ֵܵ��Ҷ�����1�������(��)
					else if (!bLLr && bLRr) {
						bL->right->color = BLACK; this->rightleftRotate(par, bro); break;
					}
				//LrR1r://��ɾ���Ľڵ��������, �ֵ��Ǻ��,�ֵܵ��������1�������(��)
				//Lr2://��ɾ���Ľڵ��������, �ֵ��Ǻ��, �ֵܵ��������2�������, �����һ����
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
		//Ԥ����
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//�𿪸��׺��Ҷ���
		par->right = pre->left;
		if (pre->left) pre->left->parent = par;
		//��ת���׺��Ҷ��ӵĹ�ϵ
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
		//Ԥ����
		mLib::nNode<T>* gra = par->parent;
		bool GraOccur = (gra) ? true : false;
		bool GraLeft = (gra && gra->left == par) ? true : false;
		//�𿪸��׺������
		par->left = pre->right;
		if (pre->right) pre->right->parent = par;
		//��ת���׺�����ӵĹ�ϵ
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
		//������������
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
			while (pre && pre->right == old)   //���pre=nullptr�˳�˵��û��next��
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
					if (!pre->left && !pre->right) //���Ҷ��Ӷ���, ֱ��ɾ
					{
						if (!par) this->head = nullptr;
						else if (par->left == pre) par->left = nullptr;
						else par->right = nullptr;
						delcolor = del->color;
						subPar = par;
						subBro = (par) ? ((par->left) ? par->left : par->right) : nullptr;
						delete del;
					}
					else if (!pre->left) //�����Ϊ��, ���Ҷ����ƹ���
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
					else if (!pre->right)  //�Ҷ���Ϊ��, ��������ƹ���
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
					else //�����Ӷ�����, Ѱ����һ���ڵ�next, �滻����, Ȼ��ɾ����һ���ڵ�, ע��:��һ���ڵ�һ��û�������!���������Ҷ���
					{
						//Ѱ����һ���ڵ�
						mLib::nNode<T>* next = pre->right;  //�˲���һ������, next������Ϊ��
						par = pre;
						while (next->left)
						{
							par = next;
							next = next->left;
						}
						pre->val = next->val;
						//�޸�next�ڵ���ع�ϵ
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
			//Ȼ�����λ�ú���ɫ, ����par�Ǹ��׽ڵ�, pre���²���Ľڵ�(�ӽڵ�)
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
			//Ȼ�����λ�ú���ɫ, ����subPar�Ǳ�ɾ���ڵ���滻λ�õĸ��׽ڵ�
			//Ȼ�����λ�ú���ɫ, ����subBro�Ǳ�ɾ���ڵ���滻λ�õ��ֵܽڵ�
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






