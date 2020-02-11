#pragma once

#include <iostream>

namespace mptr {
	/*
	 * ��ռʹ��, ��ӦC98����ָ��, C++11�ѷ���
	 * ���ܹ��캯�����Խ���nullptr, �ڲ�Ҳ������, Ҳû���ڴ�й©, ������ʹ�õĻ���
	 *		��Ӧ��ȷ���ⲿ����ָ�����ptrʱ�Ѿ���������ڴ��
	 *		�ڲ�û��new
	 *
	 *  ʹ��˵��: ͬһ��ָ��ֻ�ܱ�һ��mAutoPtr����, �����ÿ���������߸�ֵ�����ʱ����Ȩת��,
	 *		�������ʹ��ԭ��������ָ���� *�����ûᵼ�� *nullptr ��RE
	 *			�����㲻Ӧ����ͬһ��ָ����Ϊ���캯�������������mAutoPtr
	 * 
	 *   //��ʵ�ֽǶ�, Ҳ���Լ�һ��bool��������ָʾ�Ƿ��ǵ�ǰ�����ָ��, ���ⲻ����falseʱ��ָ��ֱ��ָ��nullptr����
	 */
	template<class T>
	class mAutoPtr
	{
	protected:
		T* _ptr;
	public:
		mAutoPtr(T* ptr) : _ptr(ptr) {};

		//��������, ע�����������Ҫconst, ��ΪҪ����
		mAutoPtr(mAutoPtr<T>& map) :_ptr(map._ptr) {
			map._ptr = nullptr;
		}

		//���ظ��Ʋ�����, ע�����������Ҫconst
		mAutoPtr<T>& operator=(mAutoPtr<T>& map) {
			if (this != &map) {
				delete this->_ptr;  //�Լ���ֱ��ɾ��
				this->_ptr = map._ptr;
				map._ptr = nullptr;
			}
			return *this;
		}

		~mAutoPtr() {
			if (this->_ptr != nullptr) {
				delete this->_ptr;
				this->_ptr = nullptr;
			}
		};

		//Ŀ��*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//Ŀ��obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };
	};
	

	/*
	 * ��ռʹ��, ��Ӧboost��scoped_ptr
	 * ���ܹ��캯�����Խ���nullptr, �ڲ�Ҳ������, Ҳû���ڴ�й©, ������ʹ�õĻ���
	 *		��Ӧ��ȷ���ⲿ����ָ�����ptrʱ�Ѿ���������ڴ��
	 *		�ڲ�û��new
	 *
	 *  ʹ��˵��: ͬһ��ָ��ֻ�ܱ�һ��mScopedPtr����, ���ÿ���������߸�ֵ�����
	 *			�����㲻Ӧ����ͬһ��ָ����Ϊ���캯�������������mScopedPtr
	 */
	template<class T>
	class mScopedPtr
	{
	protected:
		T* _ptr;
	public:
		mScopedPtr(T* ptr) : _ptr(ptr) {};

		~mScopedPtr() {
			if (this->_ptr != nullptr) {
				delete this->_ptr;
				this->_ptr = nullptr;
			}
		};

		//Ŀ��*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//Ŀ��obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };

	private:
		mScopedPtr(const mScopedPtr<T>& map) {};
		mScopedPtr<T>& operator=(const mScopedPtr<T>& map) {};
	};

	/*
	 * ��ռʹ��, mScopedArray������汾
	 * ���ܹ��캯�����Խ���nullptr, �ڲ�Ҳ������, Ҳû���ڴ�й©, ������ʹ�õĻ���
	 *		��Ӧ��ȷ���ⲿ����ָ�����ptrʱ�Ѿ���������ڴ��, ����������ָ��
	 *		�ڲ�û��new
	 *
	 *  ʹ��˵��: ͬһ��ָ��ֻ�ܱ�һ��mScopedArray����, ���ÿ���������߸�ֵ�����
	 *			�����㲻Ӧ����ͬһ��ָ����Ϊ���캯�������������mScopedArray
	 */
	template<class T>
	class mScopedArray
	{
	protected:
		T* _ptr;
	public:
		//RAII
		mScopedArray(T* ptr) :_ptr(ptr) { ; };

		~mScopedArray()
		{
			if (this->_ptr != nullptr)
			{
				delete[] _ptr;
				this->_ptr = nullptr;
			}
		}

		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}

	public:
		mScopedArray(const mScopedArray<T>& sp) {};
		mScopedArray<T> operator=(const mScopedArray<T>& sp) {};
	};


	/*
	 * mSharedPtr�ļ�������, ʵ�������Ӧ�������̰߳�ȫ��, �����ڲ���Ŷ
	 */
	class mSharedPtrCount {
	public:
		size_t _count;
	public:
		mSharedPtrCount(int c) : _count(c) {};
		~mSharedPtrCount() {};
	};
	/*
	 * ����ʹ��, ��ӦC++11��֮���shared_ptr
	 * ���ܹ��캯�����Խ���nullptr, �ڲ�Ҳ������, Ҳû���ڴ�й©, ������ʹ�õĻ���
	 *		��Ӧ��ȷ���ⲿ����ָ�����ptrʱ�Ѿ���������ڴ��
	 *		�ڲ�û��new
	 *
	 *  ʹ��˵��: �����ÿ���������߸�ֵ�����ʱ�������ӻ����
	 *			��Ӧ����ͬһ��ָ����Ϊ���캯�������������mAutoPtr
	 *
	 *  ʹ��ʱ�����ѭ������: ���粻Ҫ��ѭ�������Node*��mSharedPtr����
	 */
	template<class T>
	class mSharedPtr
	{
	protected:
		T* _ptr;
		mSharedPtrCount* _pcount;
	public:
		mSharedPtr(T* ptr) : _ptr(ptr), _pcount(new mSharedPtrCount(1)){};

		//��������
		mSharedPtr(const mSharedPtr<T>& map) :_ptr(map._ptr), _pcount(map._pcount) {
			this->_pcount->_count++;
		}

		//���ظ��Ʋ�����
		mSharedPtr<T>& operator=(const mSharedPtr<T>& map) {
			if (this != &map) {
				this->_pcount->_count--;
				if (this->_pcount->_count == 0) {
					if (this->_ptr != nullptr) {
						delete this->_ptr;
					}
					delete this->_pcount;
				}
				this->_ptr = map._ptr;
				this->_pcount = map._pcount;
			}
			return *this;
		}

		~mSharedPtr() {
			this->_pcount->_count--;
			if (this->_pcount->_count == 0) {
				if (this->_ptr != nullptr) {
					delete this->_ptr;
				}
				delete this->_pcount;
			}
		};

		//Ŀ��*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//Ŀ��obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };
	};

	void mAutoPtr_unittest();
	void mScopedPtr_unittest();

	void mSharedPtr_unittest();
}
