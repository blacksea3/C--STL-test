#include "pch.h"

/*
����ʽ����
vector��     ��̬���飻����������ʣ���ȡ/�޸Ŀ죻������ܿ죬Խ��ǰ���������Խ����ɾ��ͬ����������������С�ٷ��䣬�ڴ���ƶ��������ִ������ࡣ
deque��     ˫��̬���飬������vector��ͬ�����ˣ�ͷβ����ܿ죬�м��������ɾ��ͬ��
array��       ��̬���飻����������ʣ���ȡ/�޸Ŀ죬��֧�ֲ���/ɾ����
list��          ˫������������������ʣ���ȡ/�޸���������λ�ò���ɾ���졣
forward_list�� ���������������ޣ�����/�ݲ��о�
*/

void init_test()
{
	clock_t startTime, endTime;
	startTime = clock();//��ʱ��ʼ

	cout << "����10000 int��С,Ĭ����ֵ,��ʼ��" << endl;
	for (int i = 0; i < 10000; ++i)
	{
		vector<int> mvector(10000);
	}
	endTime = clock();//��ʱ����
	cout << "vector *10000 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int i = 0; i < 10; ++i)
	{
		list<int> mlist(10000);
	}
	endTime = clock();//��ʱ����
	cout << "list *10 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int i = 0; i < 10; ++i)
	{
		deque<int> mdeque(10000);
	}
	endTime = clock();//��ʱ����
	cout << "deque *10 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int i = 0; i < 1000000; ++i)
	{
		array<int, 10000> marray;
	}
	endTime = clock();//��ʱ����
	cout << "array *1000000 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

void insert_test()
{
	clock_t startTime, endTime;

	cout << "��ʼ����0��С����������λ�ò���" << endl;
	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector;
		for (int i = 0; i < 100000; ++i)
		{
			mvector.insert(mvector.begin(), 0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "vector ����100000��int, 5�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.insert(mlist.begin(), 0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "list ����100000��int, 5�� insertд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.push_front(0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "list ����100000��int, 5�� push_frontд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.insert(mdeque.begin(), 0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "deque ����100000��int, 5��, insertд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.push_front(0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "deque ����100000��int, 5��, push_frontд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	///////////*********************************************************/////////////////
	cout << "��ʼ����0��С�������ĩβ����" << endl;
	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector;
		for (int i = 0; i < 100000; ++i)
		{
			mvector.insert(mvector.end(), 0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "vector ����100000��int, 5�� insertд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector;
		for (int i = 0; i < 100000; ++i)
		{
			mvector.push_back(0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "vector ����100000��int, 5�� push_backд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.insert(mlist.end(), 0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "list ����100000��int, 5�� endд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.push_back(0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "list ����100000��int, 5�� push_backд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.insert(mdeque.end(), 0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "deque ����100000��int, 5��, insertд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//��ʱ��ʼ
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.push_back(0);
		}
	}
	endTime = clock();//��ʱ����
	cout << "deque ����100000��int, 5��, push_backд�� time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

void delete_test()
{
	clock_t startTime, endTime, intervalTime;

	cout << "��ʼ����100000��С����������λ��ɾ�����ȳ�ʼ���ټ�ʱ" << endl;
	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mvector.erase(mvector.begin());
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	cout << "vector ɾ��100000��int, 5�� eraseд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mlist.erase(mlist.begin());
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	cout << "list ɾ��100000��int, 5�� eraseд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mlist.pop_front();
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//��ʱ����
	cout << "list ɾ��100000��int, 5�� pop_frontд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.erase(mdeque.begin());
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//��ʱ����
	cout << "deque ɾ��100000��int, 5��, eraseд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.pop_front();
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//��ʱ����
	cout << "deque ɾ��100000��int, 5��, pop_frontд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	///////////*****************************************************************************************/////////////////
	cout << "��ʼ����0��С�������ĩβɾ�����ȳ�ʼ���ټ�ʱ" << endl;
	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mvector.pop_back();
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//��ʱ����
	cout << "vector ɾ��100000��int, 5�� pop_backд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mlist.pop_back();
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//��ʱ����
	cout << "list ɾ��100000��int, 5�� pop_backд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque(100000);
		startTime = clock();//��ʱ��ʼ
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.pop_back();
		}
		endTime = clock();//��ʱ����
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//��ʱ����
	cout << "deque ɾ��100000��int, 5��, pop_backд�� time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;
}



//��������
void mvector()
{
	//���г��õ�

	//��ʼ��
	cout << "vector ��ʼ��" << endl;
	cout << "vector<int> v1(5), Ĭ��ֵ" << endl;
	vector<int> v1(5);
	for (auto v : v1) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v2(5, 1), ���1" << endl;
	vector<int> v2(5, 1);
	for (auto v : v2) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v4; ���б�" << endl;
	vector<int> v4;
	for (auto v : v4) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v5 = {1, 2, 3, 4, 5};" << endl;
	vector<int> v5 = { 1, 2, 3, 4, 5 };
	for (auto v : v5) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v6(v5); Copy����" << endl;
	vector<int> v6(v5);
	for (auto v : v6) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v7 = v5; Copy����" << endl;
	vector<int> v7 = v5;
	for (auto v : v7) cout << v << " ";
	cout << endl << endl;

	//��ȡֵ����
	cout << "��ȡֵ" << endl;
	vector<int> v8 = { 1,3,5,7,9,11,13 };
	cout << "vector<int> v8 = { 1,3,5,7,9,11,13 };" << endl;
	for (auto v : v8) cout << v << " ";
	cout << endl << endl;

	cout << "cout << v8[3]" << endl;
	cout << v8[3] << endl;

	vector<int>::iterator iterv = v8.begin();
	cout << "vector<int>::iterator iterv = v8.begin(); cout << *(iterv+3);" << endl;
	cout << *(iterv + 3) << endl;

	//����
	cout << "����" << endl;
	cout << "vector<int>::iterator iterv = v8.begin(); v8.insert(iterv, 100);" << endl;
	v8.insert(iterv, 100);
	for (auto v : v8) cout << v << " ";
	cout << endl << endl;

	iterv = v8.begin();
	cout << "iterv = v8.begin(); v8.insert(iterv + 3, 300);" << endl;
	v8.insert(iterv  + 3, 300);
	for (auto v : v8) cout << v << " ";
	cout << endl << endl;

	cout << "v8.push_back(500);" << endl;
	v8.push_back(500);
	for (auto v : v8) cout << v << " ";
	cout << endl << endl;

	//ɾ��
	vector<int> v9 = { 1,3,5,7,9,11,13 };
	cout << "vector<int> v9 = { 1,3,5,7,9,11,13 };" << endl;
	
	cout << "v9.erase(v9.begin());" << endl;
	v9.erase(v9.begin());
	for (auto v : v9) cout << v << " ";
	cout << endl << endl;

	cout << "v9.erase(v9.begin() + 3);" << endl;
	v9.erase(v9.begin() + 3);
	for (auto v : v9) cout << v << " ";
	cout << endl << endl;

	cout << "v9.pop_back();" << endl;
	v9.pop_back();
	for (auto v : v9) cout << v << " ";
	cout << endl << endl;

	//����,Ȼ��ɾ��
	vector<int> v10 = { 1,3,5,7,9,11,13 };
	cout << "vector<int> v10 = { 1,3,5,7,9,11,13 };" << endl;

	cout << "vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), 9); v10.erase(iterv10);" << endl;
	vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), 9); v10.erase(iterv10);
	for (auto v : v10) cout << v << " ";
	cout << endl << endl;

	cout << "for (int i = 0; i < 5; ++i)" << endl;
	cout << "{" << endl;
	cout << "    vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), i);" << endl;
	cout << "    if (iterv == v10.end()) cout << \"��Ԫ��ֵ\" << i << \" \";" << endl;
	cout << "{" << endl;
	for (int i = 0; i < 5; ++i)
	{
		vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), i);
		if (iterv10 == v10.end()) cout << "��Ԫ��ֵ" << i << " ";
	}
	cout << endl << endl;

	//����
	cout << "for (vector<int>::iterator iiter = v10.begin(); iiter != v10.end(); ++iiter)" << endl;
	cout << "    cout << *(iiter) << \" \"" << endl;
	for (vector<int>::iterator iiter = v10.begin(); iiter != v10.end(); ++iiter)
		cout << *(iiter) << " ";
	cout << endl << endl;

	cout << "for (auto v:v10) cout << v << \" \";" << endl;
	for (auto v:v10) cout << v << " ";
	cout << endl << endl;
}

bool m_cmp2(const int& p1, const int& p2)
{
	return p1 > p2;  //�Ҳ�֪��Ϊʲô����д��return (p1 > p2) ���� return p1 >= p2 ?????????;
}

//�Զ�������
bool m_cmp(const pair<int, int>& p1, const pair<int, int>& p2)
{
	/*return !(p1.second > p2.second); //����ƾʲô>=�ֿ�����??? ����Ҳ����*/

	
	if (p1.first > p2.first) return true;
	else if (p1.first < p2.first) return false;
	else return p1.second >= p2.second;  //����ƾʲô>=�ֿ�����??? ����Ҳ����
}

void mvector_sort()
{
	//����
	vector<int> v11 = { 1,6,8,20,3,41,5,-32,6 };
	cout << "vector<int> v11 = { 1,6,8,20,3,41,5,-32,6 }; sort(v11.begin(), v11.end());" << endl;
	sort(v11.begin(), v11.end());
	for (auto v : v11) cout << v << " ";
	cout << endl << endl;

	vector<int> v12 = { 1,6,8,20,3,41,5,-32,6 };
	cout << "vector<int> v12 = { 1,6,8,20,3,41,5,-32,6 }; sort(v12.begin(), v12.end(), greater<int>());" << endl;
	sort(v12.begin(), v12.end(), greater<int>());
	for (auto v : v12) cout << v << " ";
	cout << endl << endl;

	vector<int> v13 = { 1,6,8,20,3,41,5,-32,6 };
	cout << "vector<int> v13 = { 1,6,8,20,3,41,5,-32,6 }; sort(v13.begin(), v13.end(), m_cmp2);"<< endl;
	sort(v13.begin(), v13.end(), m_cmp2);
	for (auto v : v13) cout << v << " ";
	cout << endl << endl;

	cout << "vector<pair<int,int>> v14, ����first��second�ǵ�������" << endl;
	vector<pair<int, int>> v14;
	v14.push_back(pair<int, int> {1, 20});
	v14.push_back(pair<int, int> {10, 2});
	v14.push_back(pair<int, int> {6, 6});
	for (auto v : v14) cout << v.first << " " << v.second << " ";
	cout << endl << endl;

	sort(v14.begin(), v14.end(), m_cmp);
	for (auto v : v14) cout << v.first << " " << v.second << " ";
	cout << endl << endl;
}

void mvector_other()
{
	//����ɾ��
	cout << "����ɾ��" << endl;
	vector<int> v15 = { 1,4,1,1,4,1,1,1,1,4,4,1 };
	for (auto v : v15) cout << v << " ";
	cout << endl << endl;
	vector<int>::iterator iterv15;
	for (iterv15 = v15.begin(); iterv15 != v15.end();)
	{
		if (*iterv15 == 1)
			iterv15 = v15.erase(iterv15);
		else
			iterv15++;
	}
	for (auto v : v15) cout << v << " ";
	cout << endl << endl;

	//�������
	cout << "�������" << endl;
	vector<int> v16 = { 1,4,1,1,4,1,1,1,1,4,4,1 };
	for (auto v : v16) cout << v << " ";
	cout << endl << endl;
	vector<int>::iterator iterv16;
	for (iterv16 = v16.begin(); iterv16 != v16.end();)
	{
		if (*iterv16 == 4)
		{
			iterv16 = v16.insert(iterv16, 5);
			iterv16 += 2;
		}
		else
			iterv16++;
	}
	for (auto v : v16) cout << v << " ";
	cout << endl << endl;

	//reverse
	cout << "reverse(v17.begin(), v17.end());" << endl;
	vector<int> v17 = { 1,4,6,0,15,22,-331,41,69 };
	for (auto v : v17) cout << v << " ";
	cout << endl << endl;
	reverse(v17.begin(), v17.end());
	for (auto v : v17) cout << v << " ";
	cout << endl << endl;
}
