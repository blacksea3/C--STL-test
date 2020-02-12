#include "mPtr.hpp"

namespace mptr {
	//����class����test
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


	//����class����test, ����ѭ������, ���ڲ�ʹ��mWeakPtr
	class mptrTestClassLoop
	{
	private:
		int _data;
	public:// Ϊ��ʡȥһЩ�������� ���ݳ�ԱҲ����Ϊpublic
		mptrTestClassLoop(): _next() {};
		mWeakPtr<mptrTestClassLoop> _next;

		~mptrTestClassLoop()
		{
			std::cout << "kill mptrTestClassLoop\n";
		}

		void setData(int d) {
			this->_data = d;
		}
		int getData() {
			return this->_data;
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
		//std::cout << *map4 << std::endl;    //��ͼ��һ��*nullptr, RE

		mAutoPtr<mptrTestClass> mtc1(new mptrTestClass);
		std::cout << mtc1->getData() << std::endl;

		mtc1->setData(5);
		std::cout << mtc1->getData() << std::endl;

		mAutoPtr<mptrTestClass> mtc2(mtc1);
		mAutoPtr<mptrTestClass> mtc3(nullptr);
		mtc3 = mtc2;

		//std::cout << mtc2->getData() << std::endl;   //��ͼ��һ��nullptr->?, RE

		//int* pint10 = new int(10);
		//mAutoPtr<int> map10(pint10);
		//mAutoPtr<int> map11(pint10);   //��ͼdeleteһ����delete����ָ��(����������nullptr), RE
	}

	void mScopedPtr_unittest() {
		mScopedPtr<int> map1(new int(10));
		mScopedPtr<double> mapd(new double(20.0));

		int* pint3 = new int(3);
		mScopedPtr<int> map2(pint3);   
		std::cout << *map2 << std::endl;
		//map2 = map1;   //�������

		//mScopedPtr<int> map3(map2);  //�������

		mScopedPtr<mptrTestClass> mtc1(new mptrTestClass);
		std::cout << mtc1->getData() << std::endl;
		
		mtc1->setData(5);
		std::cout << mtc1->getData() << std::endl;
		
		mScopedPtr<mptrTestClass> mtc3(nullptr);

		//int* pint10 = new int(10);
		//mScopedPtr<int> map10(pint10);
		//mScopedPtr<int> map11(pint10);   //��ͼdeleteһ����delete����ָ��(����������nullptr), RE

		int* pintArr5 = new int[5];
		mScopedArray<int> msa5(pintArr5);
		for (int i = 0; i < 5; ++i) msa5[i] = 10 + i;
		std::cout << msa5[2] << std::endl;
	}

	void mSharedPtr_unittest() {
		//mSharedPtr<int> msp1(new int(1));
		//mSharedPtr<int> msp2(new int(2));
		//mSharedPtr<int> msp3(new int(3));
		//mSharedPtr<int> msp4(new int(4));
		//mSharedPtr<int> msp5(new int(5));
		//
		//std::cout << *msp1 << std::endl;
		//std::cout << *msp2 << std::endl;
		//std::cout << *msp3 << std::endl;
		//std::cout << *msp4 << std::endl;
		//std::cout << *msp5 << std::endl;
		//
		//msp2 = msp1;
		//msp4 = msp1;
		//std::cout << *msp2 << std::endl;
		//std::cout << *msp4 << std::endl;
		//
		//mSharedPtr<int> msp6(msp5);
		//mSharedPtr<int> msp7(msp2);
		//std::cout << *msp6 << std::endl;
		//std::cout << *msp7 << std::endl;
	}


	/*
	 * ����mWeakPtr, ��Ҫ����������: ��ĳ���������涨�����״����ṹ, Ȼ���ĳһ������,
	 * �����ᵼ����һ�����ͷ�, �ں��������޷�ȡ��ֵ
	 *
	 * �����Ҫʹ�û�״�ṹ:ȷ������λ�����������ʹ��λ��
	 */
	mSharedPtr<mptrTestClassLoop> mWeakPtrTestFunc() {
		//��ͼ����ѭ�����õ��ǲ��ɹ�, ?Ϊʲô�����ĸ����ִ�н���֮������sharedPtr�����ö���1������2 ?
		mSharedPtr<mptrTestClassLoop> msptc1(new mptrTestClassLoop());
		mSharedPtr<mptrTestClassLoop> msptc2(new mptrTestClassLoop());
		msptc1->setData(2);
		msptc2->setData(5);
		msptc1->_next = msptc2;
		msptc2->_next = msptc1;
		return msptc1;
	}

	void mWeakPtr_unittest() {
		mSharedPtr<mptrTestClassLoop> msp = mWeakPtrTestFunc();
		std::cout << msp->_next->getData() << std::endl;
	}

}
