#include "mLibTest.hpp"

namespace mLib {

	//
	//NOTE: consider now is c++14
	//
	template<typename T>
	void mTypeTraitsPrint(const T x) {
		cout << "type name                   \t" << typeid(T).name() << endl;
		cout << "is_void                     \t" << is_void<T>::value << endl;
		cout << "is_integral				 \t" << is_integral<T>::value << endl;
		cout << "is_floating_point			 \t" << is_floating_point<T>::value << endl;
		cout << "is_array					 \t" << is_array<T>::value << endl;
		cout << "is_enum					 \t" << is_enum<T>::value << endl;
		cout << "is_union					 \t" << is_union<T>::value << endl;
		cout << "is_class					 \t" << is_class<T>::value << endl;
		cout << "is_function				 \t" << is_function<T>::value << endl;
		cout << "is_pointer					 \t" << is_pointer<T>::value << endl;
		cout << "is_lvalue_reference		 \t" << is_lvalue_reference<T>::value << endl;
		cout << "is_rvalue_reference		 \t" << is_rvalue_reference<T>::value << endl;
		cout << "is_member_object_pointer	 \t" << is_member_object_pointer<T>::value << endl;
		cout << "is_member_function_pointer	 \t" << is_member_function_pointer<T>::value << endl;

		cout << "is_fundamental				 \t" << is_fundamental<T>::value << endl;
		cout << "is_scalar					 \t" << is_scalar<T>::value << endl;
		cout << "is_object					 \t" << is_object<T>::value << endl;
		cout << "is_compound				 \t" << is_compound<T>::value << endl;
		cout << "is_reference				 \t" << is_reference<T>::value << endl;
		cout << "is_member_pointer			 \t" << is_member_pointer<T>::value << endl;

		cout << "is_const					 \t" << is_const<T>::value << endl;
		cout << "is_volatile				 \t" << is_volatile<T>::value << endl;
		cout << "is_trivial					 \t" << is_trivial<T>::value << endl;
		cout << "is_trivially_copyable		 \t" << is_trivially_copyable<T>::value << endl;
		cout << "is_standard_layout			 \t" << is_standard_layout<T>::value << endl;

		cout << "is_empty					 \t" << is_empty<T>::value << endl;
		cout << "is_polymorphic				 \t" << is_polymorphic<T>::value << endl;
		cout << "is_abstract				 \t" << is_abstract<T>::value << endl;
		cout << "is_final					 \t" << is_final<T>::value << endl;
		cout << "is_signed					 \t" << is_signed<T>::value << endl;
		cout << "is_unsigned				 \t" << is_unsigned<T>::value << endl;

		cout << "is_constructible					 \t" << is_constructible<T>::value << endl;
		cout << "is_trivially_constructible			 \t" << is_trivially_constructible<T>::value << endl;
		cout << "is_nothrow_constructible			 \t" << is_nothrow_constructible<T>::value << endl;
		cout << "is_default_constructible			 \t" << is_default_constructible<T>::value << endl;
		cout << "is_trivially_default_constructible	 \t" << is_trivially_default_constructible<T>::value << endl;
		cout << "is_nothrow_default_constructible	 \t" << is_nothrow_default_constructible<T>::value << endl;
		cout << "is_copy_constructible				 \t" << is_copy_constructible<T>::value << endl;
		cout << "is_trivially_copy_constructible	 \t" << is_trivially_copy_constructible<T>::value << endl;
		cout << "is_nothrow_copy_constructible		 \t" << is_nothrow_copy_constructible<T>::value << endl;
		cout << "is_move_constructible				 \t" << is_move_constructible<T>::value << endl;
		cout << "is_trivially_move_constructible	 \t" << is_trivially_move_constructible<T>::value << endl;
		cout << "is_nothrow_move_constructible		 \t" << is_nothrow_move_constructible<T>::value << endl;
		cout << "is_copy_assignable					 \t" << is_copy_assignable<T>::value << endl;
		cout << "is_trivially_copy_assignable		 \t" << is_trivially_copy_assignable<T>::value << endl;
		cout << "is_nothrow_copy_assignable			 \t" << is_nothrow_copy_assignable<T>::value << endl;
		cout << "is_move_assignable					 \t" << is_move_assignable<T>::value << endl;
		cout << "is_trivially_move_assignable		 \t" << is_trivially_move_assignable<T>::value << endl;
		cout << "is_nothrow_move_assignable			 \t" << is_nothrow_move_assignable<T>::value << endl;
		cout << "is_destructible					 \t" << is_destructible<T>::value << endl;
		cout << "is_trivially_destructible			 \t" << is_trivially_destructible<T>::value << endl;
		cout << "is_nothrow_destructible			 \t" << is_nothrow_destructible<T>::value << endl;
		cout << "has_virtual_destructor				 \t" << has_virtual_destructor<T>::value << endl;
	}

	void mLibTest_unittest() {
		mTypeTraitsPrint(std::string());
	}
}

