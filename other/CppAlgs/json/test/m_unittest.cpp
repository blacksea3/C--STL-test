#include "m_unittest.hpp"

void m_json_unittest_interface() {
	unordered_map<string, string> testTable;
	testTable.insert({ "array", "[1,2,3]" });
	testTable.insert({ "bool", "true" });
	testTable.insert({ "double", "1.1" });
	testTable.insert({ "int", "44444" });
	testTable.insert({ "string", "\"ddd\"" });
	testTable.insert({ "object", "{\"key\":\"val\"}" });
	testTable.insert({ "empty", "" });

	for (auto& itertest : testTable) {
		std::string info = itertest.second;
		cout << "Now run test:" << itertest.first << endl;

		//iterater: parse root
		JSONCPP_STRING errs;
		Json::CharReaderBuilder readerBuilder;
		Json::Value root;

		std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
		bool res;
		res = jsonReader->parse(info.c_str(), info.c_str() + info.length(), &root, &errs);
		if (!res || !errs.empty()) {
			cout << "parseJson err. " << errs << endl;
		}

		if (root.isArray())  cout << "root is array" << endl;
		if (root.isBool())  cout << "root is bool" << endl;
		if (root.isDouble())  cout << "root is double" << endl;
		if (root.isInt())  cout << "root is int" << endl;
		if (root.isString())  cout << "root is string" << endl;
		if (root.isObject())  cout << "root is object" << endl;
		if (root.empty())  cout << "root is empty" << endl;
	}
}
