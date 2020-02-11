#pragma once

#include <iostream>

namespace mptr {
	/*
	 * 独占使用, 智能指针, C++11已废弃
	 * 尽管构造函数可以接受nullptr, 内部也不出错, 也没有内存泄漏, 但正常使用
	 *		你应当确保外部传入指针参数ptr时已经是申请过内存的
	 *		内部没有new
	 */
	template<class T>
	class mAutoPtr
	{
	protected:
		T* _ptr;
	public:
		mAutoPtr(T* ptr) : _ptr(ptr) {};

		//拷贝构造, 注意输入参数不要const
		mAutoPtr(mAutoPtr<T>& map) :_ptr(map._ptr) {
			map._ptr = nullptr;
		}

		//重载复制操作符, 注意输入参数不要const
		mAutoPtr<T>& operator=(mAutoPtr<T>& map) {
			if (this != &map) {
				delete this->_ptr;  //自己的直接删了
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

		//目的*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//目的obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };
	};

	void mAutoPtr_unittest();
}


