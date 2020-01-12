#include "judgeFrame.hpp"
#include "template_fillInputArgs.hpp"

//TABLE, will add it in later version

namespace m_JSONFrame {
	void judgeFrame_unittest() {
		{
			string raw = "abcd";
			vector<string> vString = mJSONsplit(raw);
			string p1;
			pair<bool, string> ret = fillInputArgs(vString, 0, &p1);
			if (!ret.first) cout << ret.second << endl;
			else {
				debugPrint<string>(p1);
			}
		}

		{
			string raw = "false\n\n20\n7.89\n\"sstr+-*/ _ing\"\n\n";
			vector<string> vString = mJSONsplit(raw);

			bool p1;
			int p2;
			double p3;
			string p4;

			pair<bool, string> ret = fillInputArgs(vString, 0, &p1, &p2, &p3, &p4);
			if (!ret.first) cout << ret.second << endl;
			else{
				debugPrint<bool>(p1);
				debugPrint<int>(p2);
				debugPrint<double>(p3);
				debugPrint<string>(p4);
			}
		}

		{
			string raw = "[false,true,false,false,true]\n\n[2,3,5,12,-231,43,-3333]\n[312,6.43,123.44,-999.099]\n[\"sstring\",\"dd_fasd\",\"BALA BA&*AB\"]\n\n";
			vector<string> vString = mJSONsplit(raw);

			vector<bool> p1;
			vector<int> p2;
			vector<double> p3;
			vector<string> p4;

			pair<bool, string> ret = fillInputArgs(vString, 0, &p1, &p2, &p3, &p4);
			if (!ret.first) cout << ret.second << endl;
			else {
				debugPrint<vector<bool>>(p1);
				debugPrint<vector<int>>(p2);
				debugPrint<vector<double>>(p3);
				debugPrint<vector<string>>(p4);
			}
		}

		{
			string raw = "[[false, true],[false,false]]\n[[1, 63],[3,-129]]\n\n[[3.66, 4],[6.90,-0.01]]\n[[\"d\", \"*+-8\"],[\"OK\"]]\n";
			vector<string> vString = mJSONsplit(raw);

			vector<vector<bool>> p1;
			vector<vector<int>> p2;
			vector<vector<double>> p3;
			vector<vector<string>> p4;

			pair<bool, string> ret = fillInputArgs(vString, 0, &p1, &p2, &p3, &p4);
			if (!ret.first) cout << ret.second << endl;
			else {
				debugPrint<vector<vector<bool>>>(p1);
				debugPrint<vector<vector<int>>>(p2);
				debugPrint<vector<vector<double>>>(p3);
				debugPrint<vector<vector<string>>>(p4);
			}
		}

		{
			string raw = "[[false, true],[],[true]]\n[[1, 63],[3,-129]]\n\n[[5.66],[6.90,-0.01]]\n[[\"d\", \"88\"],[\"O**K\"]]\n";
			vector<string> vString = mJSONsplit(raw);

			vector<vector<bool>> p1;
			vector<vector<int>> p2;
			vector<vector<double>> p3;
			vector<vector<string>> p4;

			pair<bool, string> ret = fillInputArgs(vString, 0, &p1, &p2, &p3, &p4);
			if (!ret.first) cout << ret.second << endl;
			else {
				debugPrint<vector<vector<bool>>>(p1);
				debugPrint<vector<vector<int>>>(p2);
				debugPrint<vector<vector<double>>>(p3);
				debugPrint<vector<vector<string>>>(p4);
			}
		}

		{
			vector<vector<int>> v = { {1,32,3},{},{4} };
			mGenJson m = mGenJson(v);
			cout << m.getJSONString() << endl;
		}

		{
			vector<string> v = { "dsaddsa", "d*", "" };
			mGenJson m = mGenJson(v);
			cout << m.getJSONString() << endl;
		}

		{
			vector<bool> v = { false, true };
			mGenJson m = mGenJson(v);
			cout << m.getJSONString() << endl;
		}

		{
			vector<double> v = { };
			mGenJson m = mGenJson(v);
			cout << m.getJSONString() << endl;
		}
	}
}
