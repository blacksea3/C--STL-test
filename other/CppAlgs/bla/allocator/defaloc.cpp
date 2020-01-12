#include "defaloc.hpp"
#include <iostream>

namespace bla {
	void defaloc_unittest() {
		{
			try {
				__defaloc<__defalocTestClass> __defAlocObject;
				__defalocTestClass* ptrChar = __defAlocObject._allocate(100);
				for (int i = 0; i < 100; ++i) {
					__defAlocObject._construct(ptrChar + i);
				}
				for (int i = 0; i < 100; ++i) {
					__defAlocObject._destroy(ptrChar + i);
				}
				//__defAlocObject._destroy(ptrChar + 10);

				__defAlocObject._deallocate(ptrChar);


				ptrChar = __defAlocObject._allocate(10000);
				__defAlocObject._deallocate(ptrChar);

				ptrChar = __defAlocObject._allocate(1000000);
				__defAlocObject._deallocate(ptrChar);

				ptrChar = __defAlocObject._allocate(100000000);
				__defAlocObject._deallocate(ptrChar);

				ptrChar = __defAlocObject._allocate(1000000000);
				__defAlocObject._deallocate(ptrChar);
			}
			catch(baseException& be){
				std::cout << be.what() << std::endl;
			}
		}
	}
}
