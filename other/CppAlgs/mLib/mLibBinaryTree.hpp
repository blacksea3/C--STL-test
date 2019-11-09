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
		explicit nNode(T v)
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

//�����Ƕ�����������AVL�����ڵ��������ⲿ����ͬ�ṹ��

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
		//�ڲ���������ֵ, pair:��һ����bool, �ڶ�����ɾ���ڵ�ĸ���par, ���Ѿ������򷵻�false, nul, �������Ȼ�󷵻�true, �ýڵ�
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
			if (n->right && n != n->right->parent && n->val >= n->left->val) return false;
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
	private:
		void leftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);        //����
		void rightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);       //����
		void leftrightRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //������
		void rightleftRotate(mLib::nNode<T>* par, mLib::nNode<T>* son);   //������

		void updateHeight(mLib::nNode<T>* n);    //���¸߶�
		int getHeight(mLib::nNode<T>* n);       //��ȡ�߶ȣ�����ǿ�ָ����ô����0�������ǽڵ�ĸ߶�
		void makeAVLValidIterFunc(mLib::nNode<T>* par, mLib::nNode<T>* pre);   //�����ڲ������Ե������޸�AVL����

		mLib::nNode<T>* makeAVLValid(mLib::nNode<T>* par, mLib::nNode<T>* pre);   //ʹAVL��������, �������������ĸ��׽ڵ�
		bool checkIfAVLValidpri(mLib::nNode<T>* n);   //�ڲ���������AVL�����Ƿ�����
	public:
		bool checkIfAVLValid();                                  //����AVL�����Ƿ�����

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










