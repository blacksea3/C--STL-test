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

class mGenJson {
private:
	string errorString;
	bool dataInvalid;
	string mJSONString;

private:
	void genJSONWithJSONValue(const Json::Value& v) {
		Json::StreamWriterBuilder sw;
		sw.settings_["indentation"] = "";
		std::ostringstream osStream;
		string resStr;

		Json::StreamWriter* psw = sw.newStreamWriter();
		psw->write(v, &osStream);
		mJSONString = osStream.str();
	}

public:
	/********************************************base type*************************************/
	explicit mGenJson(const bool& data):
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v = data;
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const int& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v = data;
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const double& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v = data;
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const string& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v = data;
		genJSONWithJSONValue(v);
	}

	/**************************************vector<base> type*************************************/
	explicit mGenJson(const vector<bool>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) v.append(Json::Value(d));
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const vector<int>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) v.append(Json::Value(d));
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const vector<double>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) v.append(Json::Value(d));
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const vector<string>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) v.append(Json::Value(d));
		genJSONWithJSONValue(v);
	}

	/**********************************vector<vector<base>> type**********************************/
	explicit mGenJson(const vector<vector<bool>>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data){
			Json::Value innerv;
			innerv.resize(0);
			for (const auto& innerd : d) {
				innerv.append(Json::Value(innerd));
			}
			v.append(innerv);
		}
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const vector<vector<int>>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) {
			Json::Value innerv;
			innerv.resize(0);
			for (const auto& innerd : d) {
				innerv.append(Json::Value(innerd));
			}
			v.append(innerv);
		}
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const vector<vector<double>>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) {
			Json::Value innerv;
			innerv.resize(0);
			for (const auto& innerd : d) {
				innerv.append(Json::Value(innerd));
			}
			v.append(innerv);
		}
		genJSONWithJSONValue(v);
	}

	explicit mGenJson(const vector<vector<string>>& data) :
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v.resize(0);
		for (const auto& d : data) {
			Json::Value innerv;
			innerv.resize(0);
			for (const auto& innerd : d) {
				innerv.append(Json::Value(innerd));
			}
			v.append(innerv);
		}
		genJSONWithJSONValue(v);
	}

	string getJSONString() {
		return mJSONString;
	}

	inline bool isDataInvalid() { return dataInvalid; };
	inline string getErrorString() { return errorString; };
};

