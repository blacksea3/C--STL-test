#include "cpptemplatetest.h"

template<typename T>
T const mMax(T const& para1, T const & para2)
{
	return (para1 < para2) ? para2 : para1;
}

//cpp11���ԣ��Զ��ƶϺ�����������
template<typename T1, typename T2>
auto mMaxCpp11(T1 const& para1, T2 const& para2) -> decltype(true ? para1 : para2)
{
	return (para1 < para2) ? para2 : para1;
}

//cpp14���ԣ��Զ��ƶϺ�����������
template<typename T1, typename T2>
auto mMaxCpp14(T1 const& para1, T2 const& para2)
{
	return (para1 < para2) ? para2 : para1;
}

//cpp11���ԣ��Զ��ƶϺ����������ͣ�std::decay<xxx>�ɽ����õ���������ȥ��
template<typename T1, typename T2>
auto mMaxCpp11E(T1 const& para1, T2 const& para2) -> typename decay<decltype(true ? para1 : para2)>::type
{
	return (para1 < para2) ? para2 : para1;
}

//cpp14���ԣ�����common_type��common_typeҲ��decay�Ĺ��ܣ��ɽ����õ���������ȥ��
template<typename T1, typename T2>
common_type_t<T1, T2> mMaxCpp14C(T1 const& para1, T2 const& para2)
{
	return (para1 < para2) ? para2 : para1;
}

void cpptemplatetest1()
{
	common_type<int, double>::type cpp11; //cpp11����
	common_type_t<int, double> cpp14;     //cpp14����

	double d1 = 2.1;
	int i1 = 1;
	cout << mMaxCpp11(d1, i1) << endl;
	cout << mMaxCpp14(d1, i1) << endl;
	cout << mMaxCpp11E(d1, i1) << endl;
	cout << mMaxCpp14C(d1, i1) << endl;
}
