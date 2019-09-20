#include "STLiteratortest.h"

//����STL��ostream_iterator��istream_iterator��ʹ��Ч��
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
	istream_iterator<string> eof;  //ֱ���ļ���β/���Ͳ�ƥ�����������������ʱ�������룬win����ctrl+Zǿ���˳�����
	back_insert_iterator<vector<string>> back_iter(vs);   //�˴��������������������vsβ������
	copy(is, eof, back_iter);
}
