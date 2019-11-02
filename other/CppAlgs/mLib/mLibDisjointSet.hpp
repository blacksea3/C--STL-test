#pragma once
#include "../public/public.hpp"
#include "mLibvector.hpp"

namespace mLib
{
	/*
	 * 自定义并查集
	 * 内部使用std::vector和std::unordered_map
	 */
	template<typename T>
	class mDisjoint
	{
	private:
		std::unordered_map<T, size_t> um;
		mLib::mvector<size_t> memory;
		size_t recuFind(size_t i);
	public:
		mDisjoint(mLib::mvector<T>& v);
		void Union(T t1, T t2);
		size_t Find(T t);
	};

	template<typename T>
	size_t mDisjoint<T>::recuFind(size_t i)
	{
		if (i != this->memory[i])
			this->memory[i] = this->recuFind(this->memory[i]);
		return this->memory[i];
	}

	template<typename T>
	mDisjoint<T>::mDisjoint(mLib::mvector<T> & v)
	{
		const size_t vSize = v.getSize();
		this->memory.resize(vSize);
		for (size_t i = 0; i < vSize; ++i)
		{
			T temp = v[i];
			this->um[temp] = i;
			this->memory[i] = i;
		}
	}

	template<typename T>
	void mDisjoint<T>::Union(T t1, T t2)
	{
		size_t r1 = this->Find(t1);
		size_t r2 = this->Find(t2);
		if (r1 != r2) this->memory[r1] = r2;
	}

	template<typename T>
	size_t mDisjoint<T>::Find(T t)
	{
		return this->recuFind(this->um[t]);
	}

	void mLibDisjointSetClassTest();
}
