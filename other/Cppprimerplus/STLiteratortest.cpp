#include "STLiteratortest.h"

//测试STL的ostream_iterator和istream_iterator的使用效果
void streamIteratorTest()
{
	//ostream_iterator
	vector<int> dice(10);
	for (int index = 0; index < 10; ++index) dice[index] = index;
	ostream_iterator<int, char> out_iter(cout, " ");
	copy(dice.begin(), dice.end(), out_iter);
	cout << endl;
	copy(dice.begin(), dice.begin() + 5, out_iter);
	cout << endl;
	copy(dice.rbegin(), dice.rend(), out_iter);
	cout << endl;

	//istream_iterator
	vector<string> vs(2);
	vs[0] = "vs[0]";
	vs[1] = "vs[1]";
	istream_iterator<string> is(cin);
	istream_iterator<string> eof;  //直到文件结尾/类型不匹配或出现其他输入故障时结束输入，win下用ctrl+Z强制退出输入
	back_insert_iterator<vector<string>> back_iter(vs);   //此处定义后向插入迭代器，从vs尾部插入
	copy(is, eof, back_iter);
}
