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

/*************************************generic template mTypeString definition *************************************/
template<typename _DataType>
struct mTypeString{
	string _mTypeName = "unimplemented type";
};

/*************************************full specialization template mParseJson definition *************************************/
template<>
struct mTypeString<bool>{
	string _mTypeName = "bool";
};
template<>
struct mTypeString<int>{
	string _mTypeName = "int";
};
template<>
struct mTypeString<double>{
	string _mTypeName = "double";
};
template<>
struct mTypeString<string>{
	string _mTypeName = "std::string";
};

template<>
struct mTypeString<vector<bool>>{
	string _mTypeName = "std::vector<bool>";
};
template<>
struct mTypeString<vector<int>>{
	string _mTypeName = "std::vector<int>";
};
template<>
struct mTypeString<vector<double>>{
	string _mTypeName = "std::vector<double>";
};
template<>
struct mTypeString<vector<string>>{
	string _mTypeName = "std::vector<std::string>";
};

template<>
struct mTypeString<vector<vector<bool>>>{
	string _mTypeName = "std::vector<std::vector<bool>>";
};
template<>
struct mTypeString<vector<vector<int>>>{
	string _mTypeName = "std::vector<std::vector<int>>";
};
template<>
struct mTypeString<vector<vector<double>>>{
	string _mTypeName = "std::vector<std::vector<double>>";
};
template<>
struct mTypeString<vector<vector<string>>>{
	string _mTypeName = "std::vector<std::vector<std::string>>";
};

/*************************************generic template class mParseJson definition *************************************/
/*
 * specified data type when compiling
 * if type unknown, bool unknownType is true, else is false
 * if type known
 *     if data invalid, bool dataInvalid is true, and data is meaningless
 *     else  bool dataInvalid is false, use getData to get the prased data(inputString -> typename _DataType data)
 */
template<typename _DataType>
class mParseJson{
private:
	typedef _DataType __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;

public:  //should me modified in later version: change public to private, add new function to the class
	bool unknownType;
	bool dataInvalid;  //dump now
	
	mParseJson(string s){
		unknownType = true;
	}
	
	void debugPrint(){
		cout << "YOU SHOULD NOT SEE THIS PRINT, IF SEE, THE PROBLEM IS IN A FUCK MESS!" << endl;
	}
};

/************************************* base type *************************************/
/*
 * _DataType = bool
 */
template<>
class mParseJson<bool>{
private:
	typedef bool __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		data = true;
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		if (data) cout << "true" << endl;
		else cout << data << endl;
	}
};

/*
 * _DataType = int
 */
template<>
class mParseJson<int>{
private:
	typedef int __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		data = 100;
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		cout << data << endl;
	}
};

/*
 * _DataType = double
 */
template<>
class mParseJson<double>{
private:
	typedef double __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		data = 999.999;
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		if (data) cout << "true" << endl;
		else cout << data << endl;
	}
};

/*
 * _DataType = int
 */
template<>
class mParseJson<string>{
private:
	typedef string __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		data = "FUNNY STRING";
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		cout << data << endl;
	}
};

/************************************* vector<base> type *************************************/

/*
 * _DataType = vector<bool>
 */
template<>
class mParseJson<vector<bool>>{
private:
	typedef vector<bool> __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		for(int i = 0; i < 10; ++i) data.emplace_back((i%2) == 0);
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		for (auto iterdata:data)
			if (iterdata) cout << "true" << " ";
			else cout << "false" << " ";
		cout << endl;
	}
};

/*
 * _DataType = vector<int>
 */
template<>
class mParseJson<vector<int>>{
private:
	typedef vector<int> __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		for(int i = 0; i < 10; ++i) data.emplace_back(i);
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		for (auto& iterdata:data) cout << iterdata << " ";
		cout << endl;
	}
};

/*
 * _DataType = vector<double>
 */
template<>
class mParseJson<vector<double>>{
private:
	typedef vector<double> __Type;
	
	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		for(int i = 0; i < 10; ++i) data.emplace_back(i*11.11);
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		for (auto& iterdata:data) cout << iterdata << " ";
		cout << endl;
	}
};

/*
 * _DataType = vector<string>
 */
template<>
class mParseJson<vector<string>>{
private:
	typedef vector<string> __Type;

	string inputString;
	mTypeString<__Type> mTSSruct;
	__Type data;
	
public:
	bool unknownType;
	bool dataInvalid;
	
	mParseJson(string s){
		unknownType = false;
		//use jsoncpp to parse the data
		for(int i = 0; i < 10; ++i) data.emplace_back("str:" + to_string(i));
		//
		dataInvalid = true;
	}
	
	//template<>
	__Type getData(){
		return data;
	}
	
	void debugPrint(){
		cout << mTSSruct._mTypeName << endl;
		for (auto& iterdata:data) cout << iterdata << " ";
		cout << endl;
	}
};

/************************************* vector<vector<base>> type *************************************/

//... will write it later:!
