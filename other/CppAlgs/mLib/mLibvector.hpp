#pragma once

#include "mLibalgorithm.hpp"

namespace mLib
{
	const size_t vectorDefaultCapacity = 8;

	/*
	 * 自定义vector
	 * 警告: 内部使用动态分配内存
	 * 警告: 部分函数使用异常
	 */
	template<typename T>
	class mvector
	{
	private:
		T* first;
		size_t size;
		size_t capacity;
	public:
		mvector();
		mvector(const mLib::mvector<T>& v);
		mLib::mvector<T>& operator=(const mLib::mvector<T>& v);
		~mvector();

		T at(size_t index);
		inline const T& operator[](size_t index) const { return *(this->first + index); };
		inline T& operator[](size_t index) { return *(this->first + index); };
		void set(size_t index, T val);
		void pop_back();
		void push_back(T val);
		void resize(size_t size);
		void insert(size_t index, T val);
		inline size_t getSize(){ return this->size; }
		inline const size_t getSize() const { return this->size; }
		inline size_t getCapacity() { return this->capacity; };
		inline const size_t getCapacity() const { return this->capacity; };
	};

	template<typename T>
	mvector<T>::mvector() : size(0), capacity(mLib::vectorDefaultCapacity)
	{
		this->first = new T[this->capacity];
	}

	template<typename T>
	mvector<T>::mvector(const mLib::mvector<T>& v) : size(v.size), capacity(v.capacity)
	{
		this->first = new T[this->capacity];
		for (size_t i = 0; i < this->size; ++i) *(this->first + i) = *(v.first + i);
	}

	template<typename T>
	mLib::mvector<T>& mvector<T>::operator=(const mLib::mvector<T>& v)
	{
		delete[] this->first;
		this->size = v.size;
		this->capacity = v.capacity;
		this->first = new T[this->capacity];
		for (size_t i = 0; i < this->size; ++i) *(this->first + i) = *(v.first + i);
		return *this;
	}

	template<typename T>
	inline mvector<T>::~mvector()
	{
		delete[] this->first;
	}

	template<typename T>
	T mvector<T>::at(size_t index)
	{
		if (index >= this->size) throw "index out of range";
		else return *(this->first + index);
	}

	template<typename T>
	void mvector<T>::set(size_t index, T val)
	{
		if (index >= this->size) throw "index out of range";
		else *(this->first + index) = val;
	}

	template<typename T>
	void mvector<T>::pop_back()
	{
		if (this->size == 0) throw "already empty, cannot pop_back()";
		else
		{
			this->size--;
		}
	}

	template<typename T>
	void mvector<T>::push_back(T val)
	{
		if (this->size < this->capacity)
		{
			*(this->first + size) = val;
			this->size++;
		}
		else
		{
			this->capacity *= 2;
			T* temp = new T[this->capacity];
			for (size_t i = 0; i < size; ++i) *(temp + i) = *(this->first + i);
			delete[] this->first;
			this->first = temp;
			*(this->first + size) = val;
			this->size++;
		}
	}

	template<typename T>
	void mvector<T>::resize(size_t size)
	{
		if (size <= this->capacity) this->size = size;
		else
		{
			size_t newCap = mLib::max<size_t>(2 * size, vectorDefaultCapacity);
			T* temp = new T[newCap];
			if (this->size > 0)
			{
				for (size_t i = 0; i < this->size; ++i) *(temp + i) = *(this->first + i);
			}
			delete[] this->first;
			this->first = temp;
			this->capacity = newCap;
			this->size = size;
		}
	}

	template<typename T>
	void mvector<T>::insert(size_t index, T val)
	{
		if (this->size < this->capacity)
		{
			for (size_t i = this->size; i > index; --i)
			{
				*(this->first + i) = *(this->first + i - 1);
			}
			*(this->first + index) = val;
			this->size++;
		}
		else
		{
			this->capacity *= 2;
			T* temp = new T[this->capacity];
			for (size_t i = 0; i < index; ++i) *(temp + i) = *(this->first + i);
			for (size_t i = index + 1; i < this->size; ++i) *(temp + i) = *(this->first + i);
			*(temp + index) = val;
			delete[] this->first;
			this->first = temp;
			this->size++;
		}
	}

	void mvectorClassTest();
	void mvectorClassTimeTest();
}
