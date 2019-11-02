#include "mGCD.hpp"

long long mGCD_naive_recu(long long a, long long b)
{
	long long res = 0;
	for (int i = 1; i <= (a + b); ++i) if (a%i == 0 && b%i == 0) res = i;
	return res;
}

void mGCD_naive_interface(long long a, long long b)
{
	cout << "GCD(a" << a << "," << b << ")=" << mGCD_naive_recu(a, b) << endl;
}

//time: O(log(ab))
long long mGCD_euclid_recu(long long a, long long b)
{
	if (b == 0) return a;
	else
	{
		a = a%b;
		return mGCD_euclid_recu(b, a);
	}
}

void mGCD_euclid_interface(long long a, long long b)
{
       cout << "GCD(a" << a << "," << b << ")=" << mGCD_euclid_recu(a, b) << endl;
} 


void mGCD_main()
{
	cout << "naive:" << endl;
	estimateFuncTime(mGCD_naive_interface, 357, 234);
        estimateFuncTime(mGCD_naive_interface, 3918848, 1653264);
	cout << "euclid" << endl;
	estimateFuncTime(mGCD_euclid_interface, 3918848, 1653264);
	estimateFuncTime(mGCD_euclid_interface, 357, 234);
}

