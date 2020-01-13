#pragma once

#include "../public/constants.hpp"
#include "../public/exception.hpp"

namespace bla {
	template<typename _GeneraicType>
	class _defaloc {
	private:
		typedef _GeneraicType* _pointerGeneraicType;
	public:
		static _pointerGeneraicType _allocate(_allocatorSizeType len) {
			_pointerGeneraicType _pGT = (_pointerGeneraicType)malloc(sizeof(_GeneraicType)*len);
			if (_pGT == nullptr) {
				throw baseException("class:_defaloc func:_allocate error");
			}
			else {
				return _pGT;
			}
		}

		static void _deallocate(_pointerGeneraicType ptr) {
			if (ptr == nullptr) throw baseException("class:_defaloc func:_deallocate error");
			else free(ptr);
		}

		static _pointerGeneraicType _construct(_pointerGeneraicType ptr)
		{
			try {
				_pointerGeneraicType _pGT = new(ptr) _GeneraicType();
				return _pGT;
			}
			catch (std::bad_alloc) {
				throw baseException("class:_defaloc func:_construct error");
			}
		}

		static _pointerGeneraicType _construct(_pointerGeneraicType ptr, _GeneraicType g)
		{
			try {
				_pointerGeneraicType _pGT = new(ptr) _GeneraicType(g);
				return _pGT;
			}
			catch (std::bad_alloc) {
				throw baseException("class:_defaloc func:_construct error");
			}
		}

		static void _destroy(_pointerGeneraicType ptr)
		{
			ptr->~_GeneraicType();
		}

	};

	void defaloc_unittest();
}
