#include "judgeFrame.hpp"

void judgeFrame_unittest() {
	judgeFrame<bool, bool> fu1("fuckyou");
	judgeFrame<int, bool> fu2("fuckyou");
	judgeFrame<double, bool> fu3("fuckyou");
	judgeFrame<string, bool> fu4("fuckyou");
	
	judgeFrame<vector<bool>, bool> fu11("fuckyou");
	judgeFrame<vector<int>, bool> fu12("fuckyou");
	judgeFrame<vector<double>, bool> fu13("fuckyou");
	judgeFrame<vector<string>, bool> fu14("fuckyou");
	
	/*
	judgeFrame<vector<vector<bool>>, bool> fu21("fuckyou");
	judgeFrame<vector<vector<int>>, bool> fu22("fuckyou");
	judgeFrame<vector<vector<double>>, bool> fu23("fuckyou");
	judgeFrame<vector<vector<string>>, bool> fu24("fuckyou");
	*/
}
