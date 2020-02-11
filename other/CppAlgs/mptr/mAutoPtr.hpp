#pragma once

#include <iostream>

namespace mptr {
	/*
	 * ��ռʹ��, ����ָ��, C++11�ѷ���
	 * ���ܹ��캯�����Խ���nullptr, �ڲ�Ҳ������, Ҳû���ڴ�й©, ������ʹ��
	 *		��Ӧ��ȷ���ⲿ����ָ�����ptrʱ�Ѿ���������ڴ��
	 *		�ڲ�û��new
	 */
	template<class T>
	class mAutoPtr
	{
	protected:
		T* _ptr;
	public:
		mAutoPtr(T* ptr) : _ptr(ptr) {};

		//��������, ע�����������Ҫconst
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
			}
		};

		//Ŀ��*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//Ŀ��obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };
	};

	void mAutoPtr_unittest();
}


