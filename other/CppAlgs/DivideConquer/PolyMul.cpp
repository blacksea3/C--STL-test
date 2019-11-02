#include "PolyMul.hpp"

//返回:A*B的多项式乘积
//A和B均是系数数组, 高次幂在前低次幂在后
//A和B一样大, n除1之外一定是偶数
vector<int> PolyMultNaiverecu(vector<int> const& A, vector<int> const& B,
	int n, int al, int bl)
{
	if (n == 1)
	{
		return { A[al] * B[bl] };
	}
	else
	{
		vector<int> D0E0 = PolyMultNaiverecu(A, B, n / 2, al, bl);
		vector<int> D1E1 = PolyMultNaiverecu(A, B, n / 2, al + n / 2, bl + n / 2);
		vector<int> D0E1 = PolyMultNaiverecu(A, B, n / 2, al, bl + n / 2);
		vector<int> D1E0 = PolyMultNaiverecu(A, B, n / 2, al + n / 2, bl);
		vector<int> R(2 * n - 1);
		for (int i = 0; i < n - 1; ++i)
		{
			R[i] = D0E0[i];
		}
		for (int i = n; i < 2 * n - 1; ++i)
		{
			R[i] = D1E1[i - n];
		}
		for (int i = n / 2; i < n + n / 2 - 1; ++i)
		{
			R[i] = D0E1[i - n / 2] + D1E0[i - n / 2];
		}
		return R;
	}
}

//返回:A*B的多项式乘积
//A和B均是系数数组, 高次幂在前低次幂在后
//A和B一样大, n除1之外一定是偶数
vector<int> PolyMultOptrecu(vector<int> const& A, vector<int> const& B,
	int n, int al, int bl)
{
	if (n == 1)
	{
		return { A[al] * B[bl] };
	}
	else
	{
		vector<int> mergeA(n / 2);
		for (int i = 0; i < n / 2; ++i) mergeA[i] = A[i] + A[i + n / 2];
		vector<int> mergeB(n / 2);
		for (int i = 0; i < n / 2; ++i) mergeB[i] = B[i] + B[i + n / 2];

		vector<int> D0E0 = PolyMultNaiverecu(A, B, n / 2, al, bl);
		vector<int> D1E1 = PolyMultNaiverecu(A, B, n / 2, al + n / 2, bl + n / 2);
		vector<int> D0addD1_E0addE1 = PolyMultNaiverecu(mergeA, mergeB, n / 2, al, bl);
		vector<int> R(2 * n - 1);
		for (int i = 0; i < n - 1; ++i)
		{
			R[i] = D0E0[i];
		}
		for (int i = n; i < 2 * n - 1; ++i)
		{
			R[i] = D1E1[i - n];
		}
		for (int i = n / 2; i < n + n / 2 - 1; ++i)
		{
			R[i] = D0addD1_E0addE1[i - n / 2] - D0E0[i - n / 2] - D1E1[i - n / 2];
		}
		return R;
	}
}

void PolyMultInterface()
{
	cout << "Naive DC" << endl;
	vector<int> A = { 2,3 };
	vector<int> B = { 1,2 };
	vector<int> res = PolyMultNaiverecu(A, B, 2, 0, 0);
	cout << "Naive DC" << endl;
	vector<int> A2 = { 2,3 };
	vector<int> B2 = { 1,2 };
	vector<int> res2 = PolyMultOptrecu(A2, B2, 2, 0, 0);
	int i = 1;
}

/*
int main()
{
	PolyMultInterface();
}
*/
