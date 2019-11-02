#pragma once
#include "../public/public.hpp"
#include "mLibvector.hpp"
#include "mLibalgorithm.hpp"

namespace mLib
{
	/*
	 * 自定义priorityqueue
	 * 内部使用mLib::mvector
	 * 只支持int 和 double
	 */
	template<typename T>
	class mpriorityqueue
	{
	private:
		mLib::mvector<T> memory;
		size_t size;
	public:
		mpriorityqueue();

		T getmax();                                  //获取最大值, 不删除它
		T extractmax();                              //获取最大值, 删除它
		//void change(size_t index, T newval);       //不建议实现
		//void remove(size_t index);                 //不建议实现
		void insert(T newval);                       //插入值
	private:
		inline size_t getparent(size_t i) { return i / 2; };
		inline size_t getlchild(size_t i) { return 2 * i; };
		inline size_t getrchild(size_t i) { return 2 * i + 1; };
		void siftup(size_t i);
		void siftdown(size_t i);
	};

	template<typename T>
	mpriorityqueue<T>::mpriorityqueue() : size(0), memory()
	{
	}

	template<typename T>
	T mpriorityqueue<T>::getmax()
	{
		return memory[0];
	}

	template<typename T>
	T mpriorityqueue<T>::extractmax()
	{
		if (this->size == 0) throw "mLib::priorityqueue: try to extractmax from empty priorityqueue";

		T res = memory[0];
		memory[0] = memory[this->size - 1];
		this->size--;
		siftdown(1);
		return res;
	}

	/*
	template<typename T>
	void mpriorityqueue<T>::change(size_t indexadd1, T newval)
	{
		T old = this->memory[indexadd1 - 1];
		this->memory[indexadd1 - 1] = newval;
		if (newval > old) this->siftup(indexadd1);
		else this->siftdown(indexadd1);
	}

	template<typename T>
	void mpriorityqueue<T>::remove(size_t indexadd1)
	{
		this->memory[indexadd1 - 1] = mLib::infinity<T>();
		this->siftup(indexadd1);
		this->extractmax();
	}
	*/

	template<typename T>
	void mpriorityqueue<T>::insert(T newval)
	{
		this->size++;
		this->memory.push_back(newval);
		this->siftup(this->size);
	}

	template<typename T>
	void mpriorityqueue<T>::siftup(size_t i)
	{
		while ((i > 1) && (this->memory[this->getparent(i) - 1] < this->memory[i - 1]))
		{
			mLib::swap<T>(this->memory[this->getparent(i) - 1], this->memory[i - 1]);
			i = this->getparent(i);
		}
	}

	template<typename T>
	void mpriorityqueue<T>::siftdown(size_t i)
	{
		size_t maxi = i;
		size_t lchild = this->getlchild(i);
		if ((lchild <= this->size) && (this->memory[lchild - 1] > this->memory[maxi - 1]))
		{
			maxi = lchild;
		}
		size_t rchild = this->getrchild(i);
		if ((rchild <= this->size) && (this->memory[rchild - 1] > this->memory[maxi - 1]))
		{
			maxi = rchild;
		}
		if (i != maxi)
		{
			mLib::swap<T>(this->memory[i - 1], this->memory[maxi - 1]);
			this->siftdown(maxi);
		}
	}

	void mLibpriorityQueueClassTest();
	void mLibpriorityQueueClassTimeTest();
}
