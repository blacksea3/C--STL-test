#pragma once
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class _noTrivalClass {
public:
	char* ptr;
public:
	_noTrivalClass() {
		this->ptr = (char*)malloc(sizeof(char));
	}
	
	_noTrivalClass(char inc) {
		this->ptr = (char*)malloc(sizeof(char));
		*this->ptr = inc;
	}

	_noTrivalClass(const _noTrivalClass& _inn) {
		this->ptr = (char*)malloc(sizeof(char));
		*this->ptr = *(_inn.ptr);
	}

	_noTrivalClass& operator=(const _noTrivalClass& _inn) {
		if (this == &_inn) return *this;
		else {
			*this->ptr = *(_inn.ptr);
			return *this;
		}
	}

	~_noTrivalClass() {
		if (this->ptr == nullptr) cout << "fatal error of ~_noTrivalClass()" << endl;
		else free(this->ptr);
	}
};
