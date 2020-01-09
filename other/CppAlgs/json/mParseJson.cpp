#include "mParseJson.hpp"

/*
 * ensure that only contain: '+' '-' '*' '/' '_', a-z, A-Z, 0-9, ' '
 */
bool isValidString(const string& s) {
	for (const auto& iters : s) {
		if (!(isdigit(iters) || isalpha(iters) || iters == '+' || iters == '-' || iters == '*' || iters == '/' || iters == ' ' || iters == '_'))
			return false;
	}
	return true;
}

vector<string> mJSONsplit(string& s) {
	vector<string> res;
	size_t index = 0;
	size_t sSize = s.size();
	string pre = "";
	while(index < sSize) {
		if (s[index] == '\n') {
			if (!pre.empty()) res.emplace_back(pre);
			pre = "";
		}else {
			pre.push_back(s[index]);
		}
		index++;
	}
	if (!pre.empty()) res.emplace_back(pre);
	return res;
}
