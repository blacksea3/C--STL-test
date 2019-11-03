#pragma once

#include "../public/public.hpp"

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

	void mLibunorderedmapClassTest();
}
