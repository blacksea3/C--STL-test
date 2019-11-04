#pragma once
#include "../public/public.hpp"

namespace mLib
{
	/*
	 * 自定义单端链表
	 * 内部可能返回异常
	 */
	template<typename T>
	class mlist
	{
	private:
		/*
		 * 类内节点
		 */
		struct Node
		{
		public:
			T value;
			Node* next;
			Node(T t)
			{
				value = t;
				next = nullptr;
			}
		};
		Node* head;
	public:
		mlist();
		mlist(mLib::mlist<T> const& m);
		mLib::mlist<T>& operator=(mLib::mlist<T> const& m);

		void erase(T t);      //必须确保元素存在, 否则抛出异常
		void pushback(T t);
		~mlist();
		friend ostream& operator<<(ostream& os, mLib::mlist<T>& m)
		{
			Node* preListN = m.head->next;

			while (preListN)
			{
				os << "->";
				os << preListN->value;
				preListN = preListN->next;
			}
			return os;
		}
	private:
		void clear();
	};

	template<typename T>
	mlist<T>::mlist() : head(new Node(T()))
	{
		;
	}

	template<typename T>
	mlist<T>::mlist(mLib::mlist<T> const& m) : head(new Node(T()))
	{
		Node* preListN = this->head;
		Node* preOListN = m.head;
		while (preOListN->next)
		{
			preListN->next = new Node(preOListN->next->value);
			preListN = preListN->next;
			preOListN = preOListN->next;
		}
	}

	template<typename T>
	mLib::mlist<T> & mlist<T>::operator=(mLib::mlist<T> const& m)
	{
		this->clear();
		Node* preListN = this->head;
		Node* preOListN = m.head;
		while (preOListN->next)
		{
			preListN->next = new Node(preOListN->next->value);
			preListN = preListN->next;
			preOListN = preOListN->next;
		}
		return *this;
	}

	template<typename T>
	void mlist<T>::erase(T t)
	{
		Node* preListN = this->head->next;
		Node* lastListN = this->head;

		while (preListN)
		{
			if (preListN->value == t)
			{
				lastListN->next = preListN->next;
				delete preListN;
				return;
			}
			else
			{
				lastListN = preListN;
				preListN = preListN->next;
			}
		}
		throw "mLiblist:erase error, value you want to delete cannot be found";
	}

	template<typename T>
	void mlist<T>::pushback(T t)
	{
		Node* preListN = this->head;

		while (preListN->next) preListN = preListN->next;
		preListN->next = new Node(t);
	}

	template<typename T>
	mlist<T>::~mlist()
	{
		this->clear();
		delete this->head;
	}

	template<typename T>
	void mlist<T>::clear()
	{
		Node* preListN = this->head->next;

		while (preListN)
		{
			Node* nextListN = preListN->next;
			delete preListN;
			preListN = nextListN;
		}
	}

	void mlistClassTest();
}
