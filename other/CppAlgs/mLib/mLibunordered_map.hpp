#pragma once

#include "../public/public.hpp"
#include "mLibvector.hpp"
#include "mLiblist.hpp"

namespace mLib
{
	const unsigned long long HASHMOD = 1000000007;
	const size_t HASHPOLX = 7;

	/*
	 * mhash函数模板
	 */
	template<typename T>
	size_t mhash(T t, size_t m)
	{
		std::cout << "not implemented" << endl;
		return 0;
	}

	/*
	 * 以下mhash均为全特化函数模板
	 * 必须使用inline/extern/static中的一个来特化
	 */
	template<>
	inline size_t mhash<unsigned long long>(unsigned long long t, size_t m)
	{
		return (t % HASHMOD) % m;
	}

	template<>
	inline size_t mhash<unsigned int>(unsigned int t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<int>(int t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<long>(long t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<unsigned long>(unsigned long t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<long long>(long long t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<short>(short t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<unsigned short>(unsigned short t, size_t m)
	{
		return mhash<unsigned long long>(t, m);
	}

	template<>
	inline size_t mhash<std::string>(std::string t, size_t m)
	{
		size_t res = 0;
		size_t prex = HASHPOLX;
		for (auto& itert : t)
		{
			res += (size_t)itert * prex;
			prex *= HASHPOLX;
		}
		return res;
	}

	template<>
	inline size_t mhash<const std::string>(const std::string t, size_t m)
	{
		size_t res = 0;
		size_t prex = HASHPOLX;
		for (auto& itert : t)
		{
			res += (size_t)itert * prex;
			prex *= HASHPOLX;
		}
		return res;
	}

	/*
	 * 无序map
	 * 警告:内部使用STL::pair
	 */
	template<typename Tk, typename Tv>
	class munordered_map
	{
	private:
		mLib::mvector<mLib::mlist<pair<Tk, Tv>>*> mem;
		size_t memSize;
		static const size_t DEFAULT_SIZE_M = 10;
	public:
		munordered_map(size_t m = DEFAULT_SIZE_M);
		void set(Tk key, Tv value);     //设置key:value
		bool erase(Tk key);             //擦除成功则返回true, 失败则返回false
		pair<bool, Tv> get(Tk key);     //获取key:value, 键存在则返回true, value; 不存在则返回false, Tv()
		~munordered_map();
	};

	template<typename Tk, typename Tv>
	munordered_map<Tk, Tv>::munordered_map(size_t m) : memSize(m)
	{
		this->mem.resize(m);
		for (size_t i = 0; i < this->mem.getSize(); ++i)
			this->mem[i] = new mLib::mlist<pair<Tk, Tv>>();

		//for (size_t i = 0; i < this->mem.getSize(); ++i)
		//	this->mem[i] = 2;
	}

	template<typename Tk, typename Tv>
	void munordered_map<Tk, Tv>::set(Tk key, Tv value)
	{
		this->mem[mLib::mhash(key, this->memSize)]->pushback(std::pair<Tk, Tv>(key, value));
	}

	template<typename Tk, typename Tv>
	bool munordered_map<Tk, Tv>::erase(Tk key)
	{
		size_t tar = mLib::mhash(key, this->memSize);
		auto preListN = this->mem[tar]->head->next;
		auto lastListN = this->mem[tar]->head;

		while (preListN)
		{
			if (preListN->value.first == key)
			{
				lastListN->next = preListN->next;
				delete preListN;
				return true;
			}
			else
			{
				lastListN = preListN;
				preListN = preListN->next;
			}
		}
		return false;
	}

	template<typename Tk, typename Tv>
	pair<bool, Tv> munordered_map<Tk, Tv>::get(Tk key)
	{
		size_t tar = mLib::mhash(key, this->memSize);
		auto preListN = this->mem[tar]->head->next;

		while (preListN)
		{
			if (preListN->value.first == key)
			{
				return pair<bool, Tv>(true, preListN->value.second);
			}
			else
			{
				preListN = preListN->next;
			}
		}
		return pair<bool, Tv>(false, Tv());
	}

	template<typename Tk, typename Tv>
	munordered_map<Tk, Tv>::~munordered_map()
	{
		;
	}

	void mLibunordered_mapClassTest();
}
