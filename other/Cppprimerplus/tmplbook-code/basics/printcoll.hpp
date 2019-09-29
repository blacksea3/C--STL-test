#include <iostream>
#include "../../global.h"

// print elements of an STL container
template<typename T>
void printcoll (T const& coll)
{
    typename T::const_iterator pos;  // iterator to iterate over coll
    typename T::const_iterator end(coll.end());  // end position
    for (pos=coll.begin(); pos!=end; ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << '\n';
}

void printcollFuncTest();

void printcollFuncTest()
{
	vector<int> v(1, 2);
	printcoll<vector<int>>(v);
}
