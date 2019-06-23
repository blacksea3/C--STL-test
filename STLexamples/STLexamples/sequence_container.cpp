#include "pch.h"

/*
序列式容器
vector：     动态数组；允许随机访问，读取/修改快；最后插入很快，越往前，插入操作越慢，删除同理；插入操作或将引起大小再分配，内存的移动，但出现次数不多。
deque：     双向动态数组，几乎与vector相同；除了：头尾插入很快，中间插入慢，删除同理。
array：       静态数组；允许随机访问，读取/修改快，不支持插入/删除。
list：          双向链表；不允许随机访问，读取/修改慢；任意位置插入删除快。
forward_list： 单向链表，功能受限，特殊/暂不研究
*/

void init_test()
{
	clock_t startTime, endTime;
	startTime = clock();//计时开始

	cout << "都是10000 int大小,默认数值,初始化" << endl;
	for (int i = 0; i < 10000; ++i)
	{
		vector<int> mvector(10000);
	}
	endTime = clock();//计时结束
	cout << "vector *10000 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int i = 0; i < 10; ++i)
	{
		list<int> mlist(10000);
	}
	endTime = clock();//计时结束
	cout << "list *10 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int i = 0; i < 10; ++i)
	{
		deque<int> mdeque(10000);
	}
	endTime = clock();//计时结束
	cout << "deque *10 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int i = 0; i < 1000000; ++i)
	{
		array<int, 10000> marray;
	}
	endTime = clock();//计时结束
	cout << "array *1000000 init time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

void insert_test()
{
	clock_t startTime, endTime;

	cout << "初始都是0大小，首先在首位置插入" << endl;
	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector;
		for (int i = 0; i < 100000; ++i)
		{
			mvector.insert(mvector.begin(), 0);
		}
	}
	endTime = clock();//计时结束
	cout << "vector 插入100000个int, 5遍 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.insert(mlist.begin(), 0);
		}
	}
	endTime = clock();//计时结束
	cout << "list 插入100000个int, 5遍 insert写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.push_front(0);
		}
	}
	endTime = clock();//计时结束
	cout << "list 插入100000个int, 5遍 push_front写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.insert(mdeque.begin(), 0);
		}
	}
	endTime = clock();//计时结束
	cout << "deque 插入100000个int, 5遍, insert写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.push_front(0);
		}
	}
	endTime = clock();//计时结束
	cout << "deque 插入100000个int, 5遍, push_front写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	///////////*********************************************************/////////////////
	cout << "初始都是0大小，其次在末尾插入" << endl;
	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector;
		for (int i = 0; i < 100000; ++i)
		{
			mvector.insert(mvector.end(), 0);
		}
	}
	endTime = clock();//计时结束
	cout << "vector 插入100000个int, 5遍 insert写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector;
		for (int i = 0; i < 100000; ++i)
		{
			mvector.push_back(0);
		}
	}
	endTime = clock();//计时结束
	cout << "vector 插入100000个int, 5遍 push_back写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.insert(mlist.end(), 0);
		}
	}
	endTime = clock();//计时结束
	cout << "list 插入100000个int, 5遍 end写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist;
		for (int i = 0; i < 100000; ++i)
		{
			mlist.push_back(0);
		}
	}
	endTime = clock();//计时结束
	cout << "list 插入100000个int, 5遍 push_back写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.insert(mdeque.end(), 0);
		}
	}
	endTime = clock();//计时结束
	cout << "deque 插入100000个int, 5遍, insert写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();//计时开始
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque;
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.push_back(0);
		}
	}
	endTime = clock();//计时结束
	cout << "deque 插入100000个int, 5遍, push_back写法 time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

void delete_test()
{
	clock_t startTime, endTime, intervalTime;

	cout << "初始都是100000大小，首先在首位置删除，先初始化再计时" << endl;
	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mvector.erase(mvector.begin());
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	cout << "vector 删除100000个int, 5遍 erase写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mlist.erase(mlist.begin());
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	cout << "list 删除100000个int, 5遍 erase写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mlist.pop_front();
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//计时结束
	cout << "list 删除100000个int, 5遍 pop_front写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.erase(mdeque.begin());
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//计时结束
	cout << "deque 删除100000个int, 5遍, erase写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.pop_front();
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//计时结束
	cout << "deque 删除100000个int, 5遍, pop_front写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	///////////*****************************************************************************************/////////////////
	cout << "初始都是0大小，其次在末尾删除，先初始化再计时" << endl;
	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		vector<int> mvector(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mvector.pop_back();
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//计时结束
	cout << "vector 删除100000个int, 5遍 pop_back写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		list<int> mlist(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mlist.pop_back();
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//计时结束
	cout << "list 删除100000个int, 5遍 pop_back写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;

	intervalTime = 0;
	for (int t = 0; t < 5; ++t)
	{
		deque<int> mdeque(100000);
		startTime = clock();//计时开始
		for (int i = 0; i < 100000; ++i)
		{
			mdeque.pop_back();
		}
		endTime = clock();//计时结束
		intervalTime += (endTime - startTime);
	}
	endTime = clock();//计时结束
	cout << "deque 删除100000个int, 5遍, pop_back写法 time is: " << (double)intervalTime / CLOCKS_PER_SEC << "s" << endl;
}



//常见操作
void mvector()
{
	//就列常用的

	//初始化
	cout << "vector 初始化" << endl;
	cout << "vector<int> v1(5), 默认值" << endl;
	vector<int> v1(5);
	for (auto v : v1) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v2(5, 1), 填充1" << endl;
	vector<int> v2(5, 1);
	for (auto v : v2) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v4; 空列表" << endl;
	vector<int> v4;
	for (auto v : v4) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v5 = {1, 2, 3, 4, 5};" << endl;
	vector<int> v5 = { 1, 2, 3, 4, 5 };
	for (auto v : v5) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v6(v5); Copy构造" << endl;
	vector<int> v6(v5);
	for (auto v : v6) cout << v << " ";
	cout << endl << endl;

	cout << "vector<int> v7 = v5; Copy构造" << endl;
	vector<int> v7 = v5;
	for (auto v : v7) cout << v << " ";
	cout << endl << endl;

	//读取值操作
	cout << "读取值" << endl;
	vector<int> v8 = { 1,3,5,7,9,11,13 };
	cout << "vector<int> v8 = { 1,3,5,7,9,11,13 };" << endl;
	for (auto v : v8) cout << v << " ";
	cout << endl << endl;

	cout << "cout << v8[3]" << endl;
	cout << v8[3] << endl;

	vector<int>::iterator iterv = v8.begin();
	cout << "vector<int>::iterator iterv = v8.begin(); cout << *(iterv+3);" << endl;
	cout << *(iterv + 3) << endl;

	//插入
	cout << "插入" << endl;
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

	//删除
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

	//查找,然后删除
	vector<int> v10 = { 1,3,5,7,9,11,13 };
	cout << "vector<int> v10 = { 1,3,5,7,9,11,13 };" << endl;

	cout << "vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), 9); v10.erase(iterv10);" << endl;
	vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), 9); v10.erase(iterv10);
	for (auto v : v10) cout << v << " ";
	cout << endl << endl;

	cout << "for (int i = 0; i < 5; ++i)" << endl;
	cout << "{" << endl;
	cout << "    vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), i);" << endl;
	cout << "    if (iterv == v10.end()) cout << \"有元素值\" << i << \" \";" << endl;
	cout << "{" << endl;
	for (int i = 0; i < 5; ++i)
	{
		vector<int>::iterator iterv10 = find(v10.begin(), v10.end(), i);
		if (iterv10 == v10.end()) cout << "有元素值" << i << " ";
	}
	cout << endl << endl;

	//遍历
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
	return p1 > p2;  //我不知道为什么不能写成return (p1 > p2) 或者 return p1 >= p2 ?????????;
}

//自定义排序
bool m_cmp(const pair<int, int>& p1, const pair<int, int>& p2)
{
	/*return !(p1.second > p2.second); //这里凭什么>=又可以用??? 括号也可以*/

	
	if (p1.first > p2.first) return true;
	else if (p1.first < p2.first) return false;
	else return p1.second >= p2.second;  //这里凭什么>=又可以用??? 括号也可以
}

void mvector_sort()
{
	//排序
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

	cout << "vector<pair<int,int>> v14, 按先first后second非递增排序" << endl;
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
	//遍历删除
	cout << "遍历删除" << endl;
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

	//遍历添加
	cout << "遍历添加" << endl;
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
