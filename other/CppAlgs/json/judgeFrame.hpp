#pragma once
#include "mParseJson.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

/*
 * specified input type and output type when compiling
 *
 */
template<typename _Input, typename _Output>
class judgeFrame{
private:
	_Input inputdata;
	_Output outputdata;
	
public:
	judgeFrame(string s){
		mParseJson<_Input> mpj = mParseJson<_Input>(s);
		if (mpj.unknownType){
			cout << "input type is not implemented yet" << endl;
		}else{
			mpj.debugPrint();
		}
	}
};

void judgeFrame_unittest();
