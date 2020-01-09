#include "judgeFrame.hpp"

//TABLE, will add it in later version



void judgeFrame_unittest() {
	string raw = "false\n\n20\n7.89\n\"sstr+-*/ _ing\"\n\n";
	vector<string> vString = mJSONsplit(raw);

	mParseJson<bool> mInputPara1 = mParseJson<bool>(vString[0]);
	mParseJson<int> mInputPara2 = mParseJson<int>(vString[1]);
	mParseJson<double> mInputPara3 = mParseJson<double>(vString[2]);
	mParseJson<string> mInputPara4 = mParseJson<string>(vString[3]);

	if (mInputPara1.isUnknownType() || mInputPara1.isDataInvalid()) cout << mInputPara1.getErrorString() << endl;
	else mInputPara1.debugPrint();
	if (mInputPara2.isUnknownType() || mInputPara2.isDataInvalid()) cout << mInputPara2.getErrorString() << endl;
	else mInputPara2.debugPrint();
	if (mInputPara3.isUnknownType() || mInputPara3.isDataInvalid()) cout << mInputPara3.getErrorString() << endl;
	else mInputPara3.debugPrint();
	if (mInputPara4.isUnknownType() || mInputPara4.isDataInvalid()) cout << mInputPara4.getErrorString() << endl;
	else mInputPara4.debugPrint();

	string raw2 = "[false,true,false,false,true]\n\n[2,3,5,12,-231,43,-3333]\n[312,6.43,123.44,-999.099]\n[\"sstring\",\"dd_fasd\",\"BALA BA&*AB\"]\n\n";
	vector<string> vString2 = mJSONsplit(raw2);

	mParseJson<vector<bool>> mInputPara11 = mParseJson<vector<bool>>(vString2[0]);
	mParseJson<vector<int>> mInputPara12 = mParseJson<vector<int>>(vString2[1]);
	mParseJson<vector<double>> mInputPara13 = mParseJson<vector<double>>(vString2[2]);
	mParseJson<vector<string>> mInputPara14 = mParseJson<vector<string>>(vString2[3]);

	if (mInputPara11.isUnknownType() || mInputPara11.isDataInvalid()) cout << mInputPara11.getErrorString() << endl;
	else mInputPara11.debugPrint();
	if (mInputPara12.isUnknownType() || mInputPara12.isDataInvalid()) cout << mInputPara12.getErrorString() << endl;
	else mInputPara12.debugPrint();
	if (mInputPara13.isUnknownType() || mInputPara13.isDataInvalid()) cout << mInputPara13.getErrorString() << endl;
	else mInputPara13.debugPrint();
	if (mInputPara14.isUnknownType() || mInputPara14.isDataInvalid()) cout << mInputPara14.getErrorString() << endl;
	else mInputPara14.debugPrint();

	string raw3 = "[[false, true],[false,false]]\n[[1, 63],[3,-129]]\n\n[[3.66, 4],[6.90,-0.01]]\n[[\"d\", \"*+-8\"],[\"OK\"]]\n";
	vector<string> vString3 = mJSONsplit(raw3);
	mParseJson<vector<vector<bool>>> mInputPara31 = mParseJson<vector<vector<bool>>>(vString3[0]);
	mParseJson<vector<vector<int>>> mInputPara32 = mParseJson<vector<vector<int>>>(vString3[1]);
	mParseJson<vector<vector<double>>> mInputPara33 = mParseJson<vector<vector<double>>>(vString3[2]);
	mParseJson<vector<vector<string>>> mInputPara34 = mParseJson<vector<vector<string>>>(vString3[3]);

	if (mInputPara31.isUnknownType() || mInputPara31.isDataInvalid()) cout << mInputPara31.getErrorString() << endl;
	else mInputPara31.debugPrint();
	if (mInputPara32.isUnknownType() || mInputPara32.isDataInvalid()) cout << mInputPara32.getErrorString() << endl;
	else mInputPara32.debugPrint();
	if (mInputPara33.isUnknownType() || mInputPara33.isDataInvalid()) cout << mInputPara33.getErrorString() << endl;
	else mInputPara33.debugPrint();
	if (mInputPara34.isUnknownType() || mInputPara34.isDataInvalid()) cout << mInputPara34.getErrorString() << endl;
	else mInputPara34.debugPrint();

	string raw4 = "[[false, true],[]]\n[[1, 63],[3,-129]]\n\n[5.66,[6.90,-0.01]]\n[[\"d\", \"8%8\"],[\"O**K\"]]\n";
	vector<string> vString4 = mJSONsplit(raw4);
	mParseJson<vector<vector<bool>>> mInputPara41 = mParseJson<vector<vector<bool>>>(vString4[0]);
	mParseJson<vector<vector<int>>> mInputPara42 = mParseJson<vector<vector<int>>>(vString4[1]);
	mParseJson<vector<vector<double>>> mInputPara43 = mParseJson<vector<vector<double>>>(vString4[2]);
	mParseJson<vector<vector<string>>> mInputPara44 = mParseJson<vector<vector<string>>>(vString4[3]);

	if (mInputPara41.isUnknownType() || mInputPara41.isDataInvalid()) cout << mInputPara41.getErrorString() << endl;
	else mInputPara41.debugPrint();
	if (mInputPara42.isUnknownType() || mInputPara42.isDataInvalid()) cout << mInputPara42.getErrorString() << endl;
	else mInputPara42.debugPrint();
	if (mInputPara43.isUnknownType() || mInputPara43.isDataInvalid()) cout << mInputPara43.getErrorString() << endl;
	else mInputPara43.debugPrint();
	if (mInputPara44.isUnknownType() || mInputPara44.isDataInvalid()) cout << mInputPara44.getErrorString() << endl;
	else mInputPara44.debugPrint();
}
