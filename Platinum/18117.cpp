#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull mul_dq(ull a, ull b, ull mod)
{
	ull val = 0;

	while (b)
	{
		if (b % 2) val = (val + a) % mod;
		a = (a << 1) % mod;
		b >>= 1;
	}

	return val;
}

ull pow_dq(ull a, ull b, ull mod) //a*10^b % mod
{
	ull x = 10;

	while (b)
	{
		if (b % 2) a = mul_dq(a, x, mod);
		b >>= 1;
		x = mul_dq(x, x, mod);
	}

	return a;
}

int T;
ull a, b, i, n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;

	while (T--)
	{
		cin >> a >> b >> i >> n;

		a = pow_dq(a, i - 1, b);

		for (i = 0; i < n; i++)
		{
			cout << a * 10 / b;
			a = mul_dq(a, 10, b);
		}

		cout << '\n';
	}
	return 0;
}

/*
* if x = yb + z, x/b 's first digit bdp = floor(10*z / b) = floor(x mod b * 10 / b) (as z = x mod b)
 => a/b's i-th digit below decimal point d = floor((a*10^(i-1) mod b) * 10 / b)
 a*10^i <= 10^36 (can overflow) -> need to handle using divide and conquer in pow and modular.
 but b <= 10^18, overflow yet. -> apply dq in multiplye, too. (x*y = 2x*(y/2) or 2x*((y-1)/2)+x)
*/