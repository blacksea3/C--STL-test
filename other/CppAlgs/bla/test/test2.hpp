#pragma once
#include "../iterator/iterator_traits.hpp"

namespace bla {
	class testIntIterator2 {
	public:
		typedef long _valueType;
		typedef _baseSizeType _difType;
		typedef _random_iterator_flag _category;
	};

	class testI2 {
	public:
		typedef _iteratorTraits<testIntIterator2>::_valueType _newValueType;
	};

	void test2();
}
