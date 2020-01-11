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

public:
	/********************************************base type*************************************/
	explicit mGenJson(const bool& data):
		dataInvalid(false), errorString("")
	{
		Json::Value v;
		v = data;
		Json::StreamWriterBuilder sw;
		std::ostringstream osStream;
		string resStr;

		Json::StreamWriter* psw = sw.newStreamWriter();
		psw->write(v, &osStream);
		resStr = osStream.str();
		cout << "res:" << resStr << endl;
	}

	explicit mGenJson(const int& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const double& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const string& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	/**************************************vector<base> type*************************************/
	explicit mGenJson(const vector<bool>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const vector<int>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const vector<double>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const vector<string>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	/**********************************vector<vector<base>> type**********************************/
	explicit mGenJson(const vector<vector<bool>>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const vector<vector<int>>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const vector<vector<double>>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	explicit mGenJson(const vector<vector<string>>& data) :
		dataInvalid(false), errorString("")
	{
		;
	}

	string getJSONString() {
		return mJSONString;
	}

	inline bool isDataInvalid() { return dataInvalid; };
	inline string getErrorString() { return errorString; };
};

