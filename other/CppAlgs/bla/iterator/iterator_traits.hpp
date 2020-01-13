#pragma once
#include "../public/constants.hpp"

namespace bla {
	/*
	 * the following five class is the valid choice of _category of iterator or pointer
	 */
	struct _iterator_flag {};
	struct _input_iterator_flag : public _iterator_flag {};
	struct _si_direction_iterator_flag : public _input_iterator_flag {};
	struct _bi_direction_iterator_flag : public _si_direction_iterator_flag {};
	struct _random_iterator_flag : public _bi_direction_iterator_flag {};

	/*
	 * the following template struct _iteratorTraits is used for middleware of get common iterator traits
	 * common iterator can be one iterator class with three fields: _valueType/_difType/_category
	 *                     or one pointer
	 */
	template<typename _IteratorType>
	struct _iteratorTraits {
		typedef typename _IteratorType::_valueType _valueType;
		typedef typename _IteratorType::_difType _difType;
		typedef typename _IteratorType::_category _category;
	};

	template <class _Value>
	struct _iteratorTraits<_Value*> {
		typedef _Value _valueType;
		typedef _pointerDifType _difType;
		typedef _random_iterator_flag _category;
	};
}
