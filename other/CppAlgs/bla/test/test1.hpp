#pragma once
#include "../public/constants.hpp"
#include "../iterator/iterator_traits.hpp"

namespace bla {
	class testIntIterator1 {
	public:
		typedef int _valueType;
		typedef _baseSizeType _difType;
		typedef _random_iterator_flag _category;
	};

	class testI1 {
	public:
		typedef _iteratorTraits<testIntIterator1>::_valueType __newValueType;
	};

	void test1();
}
