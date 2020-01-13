#pragma once
#include <type_traits>

#include "../public/constants.hpp"
#include "../public/exception.hpp"
#include "../allocator/defaloc.hpp"
#include "../iterator/iterator_traits.hpp"

namespace bla {
	/*
	 * template para:
	 * _type : all container have, can be any type
	 * _inpsize: the capacity of array
	 * _allocator: suggest using the default value: the default is _defaloc class
	 */
	template<typename _type, _containerSizeType _inpsize, typename _allocator = _defaloc<_type>>
	class array {
	private:
		//predefined type/value
		typedef _type* _pointerType;
		const _containerSizeType _typeSize = sizeof(_type);

	private:
		//size of array<> class: 12
		_containerSizeType _capacity;
		_containerSizeType _size;
		_pointerType _begin;
		_allocator _allocatorObject;

	public:
		//inline _containerSizeType capacity() { return this->_capacity; };
		//inline _containerSizeType size() { return this->_size; };
		//inline _pointerType begin() { return this->_begin; };

		inline const _containerSizeType capacity() const { return this->_capacity; };
		inline const _containerSizeType size() const { return this->_size; };
		inline const _pointerType begin() const { return this->_begin; };

		/*
		 * push_back:
		 *     if not full, add a value/object in the end, return true
		 *     else return false
		 */
		bool push_back(const _type v) {
			if (this->_size == this->_capacity) return false;
			else {
				if (!std::is_trivially_copy_constructible<_type>::value) {
					_allocatorObject._construct(_begin + this->_size++, v);
				}
				else {
					*(_begin + this->_size++) = v;
				}
				return true;
			}
		}

		/*
		explicit bool push_back(const _type& v) {
			if (this->_size == this->_capacity) return false;
			else {
				*(_begin + this->_size++) = v;
			}
		}
		*/

		/*
	   bool push_back(_pointerType ptrv) {
		   if (this->_size == this->_capacity) return false;
		   else {
			   *(_begin + this->_size++) = *ptrv;
		   }
	   }
	   */

	   /*
		* default construction function:
		*     init private values, call function of _allocatorObject to allocate memory,
		*         if _type is not trivially_constructible, should call _construct of _allocatorObject
		*/
		array() :
			_capacity(_inpsize), _size(0), _begin(nullptr), _allocatorObject(_allocator())
		{
			_pointerType _ptr = _allocatorObject._allocate(this->_typeSize*this->_capacity);
			this->_begin = _ptr;
		}

		/*
		 * copy construction function:
		 *  same as default construction function
		 */
		array(const array<_type, _inpsize, _allocator>& _cpa) :
			_capacity(_inpsize), _size(0), _begin(nullptr), _allocatorObject(_allocator())
		{
			_pointerType _ptr = _allocatorObject._allocate(this->_typeSize*this->_capacity);
			this->_begin = _ptr;

			_pointerType _cptr = _cpa.begin();
			for (_containerSizeType _index = this->_size; _index < _cpa.size(); ++_index) {
				_allocatorObject._construct(_ptr, *_cptr);
				_ptr++;
			}
			this->_size = _cpa.size();
		}

		/*
		 * = assign function
		 *  compare &_cpa and this first, if address of these two pointers are same, do nothing
		 *                                if not, campare this->_size and _cpa.size(), then decide to:
		 *                                    use = of _type and allocate/deallocate of _allocatorObject
		 */
		array<_type, _inpsize, _allocator>& operator= (const array<_type, _inpsize, _allocator>& _cpa) {
			if (&_cpa == this)
				return *this;
			else {
				if (this->_size < _cpa.size()) {
					_pointerType _ptr = this->_begin;
					_pointerType _cptr = _cpa.begin();
					for (_containerSizeType _index = 0; _index < this->_size; ++_index) {
						*(_ptr++) = *(_cptr++);
					}
					if (!std::is_trivially_copy_constructible<_type>::value) {
						for (_containerSizeType _index = this->_size; _index < _cpa.size(); ++_index) {
							_allocatorObject._construct(_ptr++, *(_cptr++));
						}
					}
					else {
						for (_containerSizeType _index = this->_size; _index < _cpa.size(); ++_index) {
							*(_ptr++) = *(_cptr++);
						}
					}
					this->_size = _cpa.size();
				}
				else {
					_pointerType _ptr = this->_begin;
					_pointerType _cptr = _cpa.begin();
					for (_containerSizeType _index = 0; _index < _cpa.size(); ++_index) {
						*(_ptr++) = *(_cptr++);
					}
					if (!std::is_trivially_copy_constructible<_type>::value) {
						for (_containerSizeType _index = _cpa.size(); _index < this->_size; ++_index) {
							_allocatorObject._destroy(_ptr++);
						}
					}
					this->_size = _cpa.size();
				}
				return *this;
			}
		}

		/*
		 * deconstruction function:
		 *  call function of _allocatorObject to deallocate memory,
		 *    if _type is not trivially_destructible, should call _destroy of _allocatorObject
		 */
		~array() {
			if (!std::is_trivially_destructible<_type>::value) {
				_pointerType _ptr = this->_begin;
				for (_containerSizeType _index = 0; _index < this->_size; ++_index) {
					_allocatorObject._destroy(_ptr++);
				}
			}
			_allocatorObject._deallocate(this->_begin);
			this->_begin = nullptr;
		}
	};

	void array_unittest();
}
