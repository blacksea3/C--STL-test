#include "defaloc.hpp"
#include <iostream>
#include "../test/noTrivalClass.hpp"

namespace bla {
	void defaloc_unittest() {
		{
			try {
				_defaloc<_noTrivalClass> _defAlocObject;
				_noTrivalClass* ptrChar = _defAlocObject._allocate(100);
				for (int i = 0; i < 100; ++i) {
					_defAlocObject._construct(ptrChar + i);
				}
				for (int i = 0; i < 100; ++i) {
					_defAlocObject._destroy(ptrChar + i);
				}
				//_defAlocObject._destroy(ptrChar + 10);

				_defAlocObject._deallocate(ptrChar);


				ptrChar = _defAlocObject._allocate(10000);
				_defAlocObject._deallocate(ptrChar);

				ptrChar = _defAlocObject._allocate(1000000);
				_defAlocObject._deallocate(ptrChar);

				ptrChar = _defAlocObject._allocate(100000000);
				_defAlocObject._deallocate(ptrChar);

				ptrChar = _defAlocObject._allocate(1000000000);
				_defAlocObject._deallocate(ptrChar);
			}
			catch(baseException& be){
				std::cout << be.what() << std::endl;
			}
		}
	}
}
