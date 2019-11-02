#include "fibonacci.hpp"

long long Fibonacci_naive_recu(long long n)
{
	if (n <= 1) return n;
	else return Fibonacci_naive_recu(n - 1) + Fibonacci_naive_recu(n - 2);
}

void Fibonacci_naive_interface(long long n)
{
	cout << "Fibonacci(" << n << ")=" << Fibonacci_naive_recu(n) << endl;
}

//time:O(n)
void Fibonacci_dp_interface(long long n)
{
	if (n <= 1)
	{
		cout << "Fibonacci(" << n << ")=" << n << endl;
		return;
	}
	
	int res = 0;
	int* dp = new int[n + 1];
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i <= n; ++i) dp[i] = dp[i - 1] + dp[i - 2];
	cout << "Fibonacci(" << n << ")=" << dp[n] << endl;
}

void fibonacci_main()
{
	cout << "recu" << endl;

	estimateFuncTime(Fibonacci_naive_interface,1);
	estimateFuncTime(Fibonacci_naive_interface,2);
	estimateFuncTime(Fibonacci_naive_interface,5);
	estimateFuncTime(Fibonacci_naive_interface,20);
	estimateFuncTime(Fibonacci_naive_interface,30);
	estimateFuncTime(Fibonacci_naive_interface,32);
	estimateFuncTime(Fibonacci_naive_interface,34);
	estimateFuncTime(Fibonacci_naive_interface,36);
	
	cout << "dp" << endl;

        estimateFuncTime(Fibonacci_dp_interface,1);
        estimateFuncTime(Fibonacci_dp_interface,2);
        estimateFuncTime(Fibonacci_dp_interface,5);
        estimateFuncTime(Fibonacci_dp_interface,20);
        estimateFuncTime(Fibonacci_dp_interface,30);
	estimateFuncTime(Fibonacci_dp_interface,32);
        estimateFuncTime(Fibonacci_dp_interface,34);
        estimateFuncTime(Fibonacci_dp_interface,36);
}

/*
int main()
{
	fibonacci_main();
	return 0;
}
*/
