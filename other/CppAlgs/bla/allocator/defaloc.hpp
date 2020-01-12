#pragma once

#include "../public/constants.hpp"
#include "../public/exception.hpp"

namespace bla {
	class __defalocTestClass {
	private:
		char* c;
	public:
		__defalocTestClass() {
			c = (char*)malloc(sizeof(char));
		}
		~__defalocTestClass() {
			free(c);
		}
	};


	template<typename __GeneraicType>
	class __defaloc {
	private:
		typedef __GeneraicType* __pointerGeneraicType;
	public:
		static __pointerGeneraicType _allocate(__allocatorSizeType len) {
			__pointerGeneraicType _pGT = (__pointerGeneraicType)malloc(sizeof(__GeneraicType)*len);
			if (_pGT == nullptr) {
				throw baseException("class:__defaloc func:_allocate error");
			}
			else {
				return _pGT;
			}
		}

		static void _deallocate(__pointerGeneraicType ptr) {
			if (ptr == nullptr) throw baseException("class:__defaloc func:_deallocate error");
			else free(ptr);
		}

		static __pointerGeneraicType _construct(__pointerGeneraicType ptr)
		{
			try {
				__pointerGeneraicType _pGT = new(ptr) __GeneraicType();
				return _pGT;
			}
			catch (std::bad_alloc) {
				throw baseException("class:__defaloc func:_construct error");
			}
		}

		static void _destroy(__pointerGeneraicType ptr)
		{
			ptr->~__GeneraicType();
		}

	};

	void defaloc_unittest();
}
