#pragma once
#include <exception>
#include <string>

namespace bla {
	class baseException :public std::exception {
	public:
		baseException(const char* c);
	};
}
