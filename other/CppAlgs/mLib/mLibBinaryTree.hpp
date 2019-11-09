#pragma once

#include "mLibvector.hpp"
#include "../public/public.hpp"

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
					
					return true;
				}
			}
		}
		return false;
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
		return this->insertpri(t, this->head);
	}

	template<typename T>
	bool mbinary_searchtree<T>::remove(T t)
	{
		return this->removepri(t, this->head);
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

