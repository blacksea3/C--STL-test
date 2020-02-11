#include "mAutoPtr.hpp"

namespace mptr {
	//ÄÚÖÃclassÓÃÓÚtest
	class mptrTestClass {
	private:
		int data;
	public:
		mptrTestClass(int d = 0) : data(d) { ; };
		void setData(int d) {
			this->data = d;
		}
		int getData() {
			return this->data;
		}
	};


	void mAutoPtr_unittest() {
		mAutoPtr<int> map1(new int(10));
		mAutoPtr<double> mapd(new double(20.0));

		int* pint3 = new int(3);
		mAutoPtr<int> map2(pint3);
		map2 = map1;

		mAutoPtr<int> map3(map2);

		mAutoPtr<int> map4(new int(4));

		mAutoPtr<int> map5(nullptr);
		map5 = map4;

		std::cout << *map5 << std::endl;

		mAutoPtr<mptrTestClass> mtc1(new mptrTestClass);
		std::cout << mtc1->getData() << std::endl;

		mtc1->setData(5);
		std::cout << mtc1->getData() << std::endl;

		mAutoPtr<mptrTestClass> mtc2(mtc1);
		mAutoPtr<mptrTestClass> mtc3(nullptr);
		mtc3 = mtc2;
	}
}
