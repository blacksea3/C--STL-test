#pragma once
#include "mParseJson.hpp"

using std::pair;

namespace m_JSONFrame {
	/*****generic type func debugPrint template*****/
	template<typename T>
	void debugPrint(T data) {
		cout << "type not implemented yet!" << endl;
		const std::type_info& st = typeid(T);
		cout << "type:" << st.name() << endl;
		cout << endl;
	}

	template<typename T>
	void debugPrint(T* data) {
		cout << "type not implemented yet!" << endl;
		const std::type_info& st = typeid(T);
		cout << "type:" << st.name() << endl;
		cout << endl;
	}

	/*****base type func debugPrint template*****/
	template<>
	void debugPrint<bool>(bool data) {
		const std::type_info& st = typeid(bool);
		cout << st.name() << endl;
		if (data) cout << "true" << endl;
		else cout << data << endl;
		cout << endl;
	}

	template<>
	void debugPrint<int>(int data) {
		const std::type_info& st = typeid(int);
		cout << st.name() << endl;
		cout << data << endl;
		cout << endl;
	}

	template<>
	void debugPrint<double>(double data) {
		const std::type_info& st = typeid(double);
		cout << st.name() << endl;
		cout << data << endl;
		cout << endl;
	}

	template<>
	void debugPrint<string>(string data) {
		const std::type_info& st = typeid(string);
		cout << st.name() << endl;
		cout << data << endl;
		cout << endl;
	}

	/*****vector<base> type func debugPrint template*****/
	template<>
	void debugPrint<vector<bool>>(vector<bool> data) {
		const std::type_info& st = typeid(vector<bool>);
		cout << st.name() << endl;
		for (const auto& d : data) {
			if (d) cout << "true ";
			else cout << "false ";
			cout << endl;
		}
		cout << endl;
	}

	template<>
	void debugPrint<vector<int>>(vector<int> data) {
		const std::type_info& st = typeid(vector<int>);
		cout << st.name() << endl;
		for (const auto& d : data) {
			cout << d << " ";
		}
		cout << endl;
		cout << endl;
	}

	template<>
	void debugPrint<vector<double>>(vector<double> data) {
		const std::type_info& st = typeid(vector<double>);
		for (const auto& d : data) {
			cout << d << " ";
		}
		cout << endl;
		cout << endl;
	}

	template<>
	void debugPrint<vector<string>>(vector<string> data) {
		const std::type_info& st = typeid(vector<string>);
		cout << st.name() << endl;
		for (const auto& d : data) {
			cout << d << " ";
		}
		cout << endl;
		cout << endl;
	}

	/*****vector<vector<base>> type func debugPrint template*****/
	template<>
	void debugPrint<vector<vector<bool>>>(vector<vector<bool>> data) {
		const std::type_info& st = typeid(vector<vector<bool>>);
		cout << st.name() << endl;
		for (const auto& d : data) {
			for (const auto& ind : d) {
				if (ind) cout << "true ";
				else cout << "false ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}

	template<>
	void debugPrint<vector<vector<int>>>(vector<vector<int>> data) {
		const std::type_info& st = typeid(vector<vector<int>>);
		cout << st.name() << endl;
		for (const auto& d : data) {
			for (const auto& ind : d) {
				cout << ind << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}

	template<>
	void debugPrint<vector<vector<double>>>(vector<vector<double>> data) {
		const std::type_info& st = typeid(vector<vector<double>>);
		for (const auto& d : data) {
			for (const auto& ind : d) {
				cout << ind << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}

	template<>
	void debugPrint<vector<vector<string>>>(vector<vector<string>> data) {
		const std::type_info& st = typeid(vector<vector<string>>);
		cout << st.name() << endl;
		for (const auto& d : data) {
			for (const auto& ind : d) {
				cout << ind << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
	}

	/*
	 * these paras are all pointers!
	 */
	pair<bool, string> fillInputArgs(const vector<string>& rawJSONStr, int fillIndex) {
		return { true, "fillInputArgs OK" };
	}

	/*
	 * note: you should use all paras as pointers of (FirstArg and ...Args)
	 */
	template<typename FirstArg, typename ...Args>
	pair<bool, string> fillInputArgs(const vector<string>& rawJSONStr, int fillIndex, FirstArg* t, Args ...args) {

		mParseJson<FirstArg> mParres = mParseJson<FirstArg>(rawJSONStr[fillIndex]);
		cout << "The " << fillIndex << "th para type is:" << endl;
		const std::type_info& st = typeid(t);
		cout << st.name() << endl;

		if (mParres.isUnknownType() || mParres.isDataInvalid()) {
			return { false, mParres.getErrorString()};
		} else {
			*t = mParres.getData();
			return fillInputArgs(rawJSONStr, fillIndex + 1, args...);
		}
	}
}
