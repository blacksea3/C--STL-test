#pragma once
#include "include/json.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;

#include <vector>
using std::vector;

using std::type_info;

namespace m_JSONFrame {

	bool isValidString(const string& s);

	/*************************************generic template class mParseJson definition *************************************/
	/*
	 * specified data type when compiling
	 * if type unknown, bool unknownType is true, else is false
	 * if type known
	 *     if data invalid, bool dataInvalid is true, and data is meaningless
	 *     else  bool dataInvalid is false, use getData to get the prased data(inputString -> typename _DataType data)
	 */
	template<typename _DataType>
	class mParseJson {
	private:
		typedef _DataType __Type;

		string errorString;
		__Type data;
		bool unknownType;
		bool dataInvalid;  //dump now

	public:
		mParseJson(string s) :
			unknownType(true), dataInvalid(true), errorString((string)"unknown type")
		{
			;
		}

		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			cout << "YOU SHOULD NOT SEE THIS PRINT, IF SEE, THE PROBLEM IS IN A FUCK MESS!" << endl;
		}
	};

	/************************************* base type *************************************/
	/*
	 * _DataType = bool
	 */
	template<>
	class mParseJson<bool> {
	private:
		typedef bool __Type;

		string errorString;
		__Type data;
		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<bool>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isBool()) {
					data = root.asBool();
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<bool>: parseError, input is:" + s;
					dataInvalid = true;
				}
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				if (data) cout << "true" << endl;
				else cout << data << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = int
	 */
	template<>
	class mParseJson<int> {
	private:
		typedef int __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<int>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isInt()) {
					data = root.asInt();
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<int>: parseError, input is:" + s;
					dataInvalid = true;
				}
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				cout << data << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = double
	 */
	template<>
	class mParseJson<double> {
	private:
		typedef double __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<double>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isDouble()) {
					data = root.asDouble();
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<double>: parseError, input is:" + s;
					dataInvalid = true;
				}
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				cout << data << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = string
	 */
	template<>
	class mParseJson<string> {
	private:
		typedef string __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<string>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isString()) {
					string temp = root.asString();
					if (!isValidString(temp)) {
						errorString = "isValidString of mParseJson<string>: parseError, input is:" + s;
						dataInvalid = true;
					}
					else {
						data = temp;
						dataInvalid = false;
					}

				}
				else {
					errorString = "mParseJson<string>: parseError, input is:" + s;
					dataInvalid = true;
				}
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				cout << data << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/************************************* vector<base> type *************************************/
	/*
	 * _DataType = vector<bool>
	 */
	template<>
	class mParseJson<vector<bool>> {
	private:
		typedef vector<bool> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<bool>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex tempLen = root.size();
					vector<bool> v;
					for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
						if (root[i].isBool()) {
							v.emplace_back(root[i].asBool());
						}
						else {
							errorString = "mParseJson<vector<bool>>: parseError, is vector, sth not bool, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<bool>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					if (d) cout << "true ";
					else cout << "false ";
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = vector<int>
	 */
	template<>
	class mParseJson<vector<int>> {
	private:
		typedef vector<int> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<int>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex tempLen = root.size();
					vector<int> v;
					for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
						if (root[i].isInt()) {
							v.emplace_back(root[i].asInt());
						}
						else {
							dataInvalid = true;
							goto __initEnd;
							errorString = "mParseJson<vector<int>>: parseError, is vector, sth not int, input is:" + s;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<int>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					cout << d << " ";
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = vector<double>
	 */
	template<>
	class mParseJson<vector<double>> {
	private:
		typedef vector<double> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<double>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex tempLen = root.size();
					vector<double> v;
					for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
						if (root[i].isDouble()) {
							v.emplace_back(root[i].asDouble());
						}
						else {
							errorString = "mParseJson<vector<double>>: parseError, is vector, sth not double, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<double>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					cout << d << " ";
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = vector<string>
	 */
	template<>
	class mParseJson<vector<string>> {
	private:
		typedef vector<string> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<string>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex tempLen = root.size();
					vector<string> v;
					for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
						if (root[i].isString()) {
							string temp = root[i].asString();
							if (isValidString(temp)) v.emplace_back(temp);
							else {
								errorString = "isValidString of mParseJson<vector<string>>: parseError, input is:" + s;
								dataInvalid = true;
								goto __initEnd;
							}
						}
						else {
							errorString = "mParseJson<vector<string>>: parseError, is vector, sth not string, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<string>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}


		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					cout << d << " ";
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/************************************* vector<vector<base>> type *************************************/
	/*
	 * _DataType = vector<vector<bool>>
	 */
	template<>
	class mParseJson<vector<vector<bool>>> {
	private:
		typedef vector<vector<bool>> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<vector<bool>>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex totLen = root.size();
					vector<vector<bool>> v;
					for (Json::ArrayIndex i = 0; i < totLen; ++i) {
						if (root[i].isArray()) {
							Json::Value innerRoot = root[i];
							Json::ArrayIndex tempLen = innerRoot.size();
							vector<bool> innerv;
							for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
								if (innerRoot[i].isBool()) {
									innerv.emplace_back(innerRoot[i].asBool());
								}
								else {
									errorString = "mParseJson<vector<vector<bool>>>: parseError, is vector<vector>, sth not bool, input is:" + s;
									dataInvalid = true;
									goto __initEnd;
								}
							}
							v.emplace_back(innerv);
						}
						else {
							errorString = "mParseJson<vector<vector<bool>>>: parseError, outer vector, inner not vector, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<bool>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}

		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					for (const auto& ind : d) {
						if (ind) cout << "true ";
						else cout << "false ";
					}
					cout << endl;
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = vector<vector<int>>
	 */
	template<>
	class mParseJson<vector<vector<int>>> {
	private:
		typedef vector<vector<int>> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<vector<int>>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex totLen = root.size();
					vector<vector<int>> v;
					for (Json::ArrayIndex i = 0; i < totLen; ++i) {
						if (root[i].isArray()) {
							Json::Value innerRoot = root[i];
							Json::ArrayIndex tempLen = innerRoot.size();
							vector<int> innerv;
							for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
								if (innerRoot[i].isInt()) {
									innerv.emplace_back(innerRoot[i].asInt());
								}
								else {
									errorString = "mParseJson<vector<vector<int>>>: parseError, is vector<vector>, sth not int, input is:" + s;
									dataInvalid = true;
									goto __initEnd;
								}
							}
							v.emplace_back(innerv);
						}
						else {
							errorString = "mParseJson<vector<vector<int>>>: parseError, outer vector, inner not vector, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<int>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}

		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					for (const auto& ind : d) {
						cout << ind << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = vector<vector<double>>
	 */
	template<>
	class mParseJson<vector<vector<double>>> {
	private:
		typedef vector<vector<double>> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<vector<double>>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex totLen = root.size();
					vector<vector<double>> v;
					for (Json::ArrayIndex i = 0; i < totLen; ++i) {
						if (root[i].isArray()) {
							Json::Value innerRoot = root[i];
							Json::ArrayIndex tempLen = innerRoot.size();
							vector<double> innerv;
							for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
								if (innerRoot[i].isDouble()) {
									innerv.emplace_back(innerRoot[i].asDouble());
								}
								else {
									errorString = "mParseJson<vector<vector<double>>>: parseError, is vector<vector>, sth not double, input is:" + s;
									dataInvalid = true;
									goto __initEnd;
								}
							}
							v.emplace_back(innerv);
						}
						else {
							errorString = "mParseJson<vector<vector<double>>>: parseError, outer vector, inner not vector, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<double>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}

		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					for (const auto& ind : d) {
						cout << ind << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	/*
	 * _DataType = vector<vector<string>>
	 */
	template<>
	class mParseJson<vector<vector<string>>> {
	private:
		typedef vector<vector<string>> __Type;

		string errorString;
		__Type data;

		bool unknownType;
		bool dataInvalid;

	public:
		mParseJson(string s) :
			unknownType(false)
		{
			//use jsoncpp to parse the data
			//iterater: parse root
			JSONCPP_STRING errs;
			Json::CharReaderBuilder readerBuilder;
			Json::Value root;

			std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
			bool res;
			res = jsonReader->parse(s.c_str(), s.c_str() + s.size(), &root, &errs);
			if (!res || !errs.empty()) {
				errorString = "jsonReader->parse of mParseJson<vector<vector<string>>>: parseError, input is:" + s + "errs is" + errs;
				dataInvalid = true;
			}
			else {
				if (root.isArray()) {
					Json::ArrayIndex totLen = root.size();
					vector<vector<string>> v;
					for (Json::ArrayIndex i = 0; i < totLen; ++i) {
						if (root[i].isArray()) {
							Json::Value innerRoot = root[i];
							Json::ArrayIndex tempLen = innerRoot.size();
							vector<string> innerv;
							for (Json::ArrayIndex i = 0; i < tempLen; ++i) {
								if (innerRoot[i].isString()) {
									string temp = innerRoot[i].asString();
									if (isValidString(temp)) innerv.emplace_back(temp);
									else {
										errorString = "isValidString of mParseJson<vector<vector<string>>>: parseError, is vector<vector>, sth not string, input is:" + s;
										dataInvalid = true;
										goto __initEnd;
									}
								}
								else {
									errorString = "mParseJson<vector<vector<string>>>: parseError, is vector<vector>, sth not string, input is:" + s;
									dataInvalid = true;
									goto __initEnd;
								}
							}
							v.emplace_back(innerv);
						}
						else {
							errorString = "mParseJson<vector<vector<string>>>: parseError, input is:" + s;
							dataInvalid = true;
							goto __initEnd;
						}
					}
					data = v;
					dataInvalid = false;
				}
				else {
					errorString = "mParseJson<vector<string>>: parseError, not vector<>, input is:" + s;
					dataInvalid = true;
				}
			__initEnd:
				;
			}
		}

		__Type getData() {
			return data;
		}

		inline bool isUnknownType() { return unknownType; };
		inline bool isDataInvalid() { return dataInvalid; };
		inline string getErrorString() { return errorString; };

		void debugPrint() {
			const std::type_info& st = typeid(__Type);
			cout << st.name() << endl;
			if (!dataInvalid) {
				for (const auto& d : data) {
					for (const auto& ind : d) {
						cout << ind << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
			else cout << "dataInvalid" << endl;
		}
	};

	vector<string> mJSONsplit(string& s);

}
