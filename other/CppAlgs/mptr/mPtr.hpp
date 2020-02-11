#pragma once

#include <iostream>

namespace mptr {
	/*
	 * 独占使用, 对应C98智能指针, C++11已废弃
	 * 尽管构造函数可以接受nullptr, 内部也不出错, 也没有内存泄漏, 但正常使用的话：
	 *		你应当确保外部传入指针参数ptr时已经是申请过内存的
	 *		内部没有new
	 *
	 *  使用说明: 同一个指针只能被一个mAutoPtr管理, 当调用拷贝构造或者赋值运算符时控制权转移,
	 *		如果还是使用原来的智能指针类 *解引用会导致 *nullptr 会RE
	 *			此外你不应当把同一个指针作为构造函数参数传给多个mAutoPtr
	 * 
	 *   //从实现角度, 也可以加一个bool变量用于指示是否是当前类管理指针, 但这不如在false时内指针直接指向nullptr清晰
	 */
	template<class T>
	class mAutoPtr
	{
	protected:
		T* _ptr;
	public:
		mAutoPtr(T* ptr) : _ptr(ptr) {};

		//拷贝构造, 注意输入参数不要const, 因为要改他
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
				this->_ptr = nullptr;
			}
		};

		//目的*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//目的obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };
	};
	

	/*
	 * 独占使用, 对应boost的scoped_ptr
	 * 尽管构造函数可以接受nullptr, 内部也不出错, 也没有内存泄漏, 但正常使用的话：
	 *		你应当确保外部传入指针参数ptr时已经是申请过内存的
	 *		内部没有new
	 *
	 *  使用说明: 同一个指针只能被一个mScopedPtr管理, 禁用拷贝构造或者赋值运算符
	 *			此外你不应当把同一个指针作为构造函数参数传给多个mScopedPtr
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

		//目的*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//目的obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };

	private:
		mScopedPtr(const mScopedPtr<T>& map) {};
		mScopedPtr<T>& operator=(const mScopedPtr<T>& map) {};
	};

	/*
	 * 独占使用, mScopedArray的数组版本
	 * 尽管构造函数可以接受nullptr, 内部也不出错, 也没有内存泄漏, 但正常使用的话：
	 *		你应当确保外部传入指针参数ptr时已经是申请过内存的, 而且是数组指针
	 *		内部没有new
	 *
	 *  使用说明: 同一个指针只能被一个mScopedArray管理, 禁用拷贝构造或者赋值运算符
	 *			此外你不应当把同一个指针作为构造函数参数传给多个mScopedArray
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
	 * mSharedPtr的计数器类, 实际上这个应该做成线程安全的, 但现在不是哦
	 */
	class mSharedPtrCount {
	public:
		size_t _count;
	public:
		mSharedPtrCount(int c) : _count(c) {};
		~mSharedPtrCount() {};
	};
	/*
	 * 共享使用, 对应C++11及之后的shared_ptr
	 * 尽管构造函数可以接受nullptr, 内部也不出错, 也没有内存泄漏, 但正常使用的话：
	 *		你应当确保外部传入指针参数ptr时已经是申请过内存的
	 *		内部没有new
	 *
	 *  使用说明: 当调用拷贝构造或者赋值运算符时计数增加或减少
	 *			不应当把同一个指针作为构造函数参数传给多个mAutoPtr
	 *
	 *  使用时请避免循环引用: 例如不要把循环链表的Node*用mSharedPtr处理
	 */
	template<class T>
	class mSharedPtr
	{
	protected:
		T* _ptr;
		mSharedPtrCount* _pcount;
	public:
		mSharedPtr(T* ptr) : _ptr(ptr), _pcount(new mSharedPtrCount(1)){};

		//拷贝构造
		mSharedPtr(const mSharedPtr<T>& map) :_ptr(map._ptr), _pcount(map._pcount) {
			this->_pcount->_count++;
		}

		//重载复制操作符
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

		//目的*obj -> obj.operator*()
		T& operator*() { return *this->_ptr; };

		//目的obj->member -> obj.operator->()->member
		T* operator->() { return _ptr; };
	};

	void mAutoPtr_unittest();
	void mScopedPtr_unittest();

	void mSharedPtr_unittest();
}
