#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> complexF;
typedef long long ll;

const int MAX = 1 << 21;
const double PI = 3.14159265359;

void FFT(complexF v[], bool inv)
{
	int N = MAX, j = 0;

	for (int i = 1; i < N; i++)
	{
		int bit = (N >> 1);

		while (!((j ^= bit) & bit)) bit >>= 1;
		if (i < j) swap(v[i], v[j]);
	}

	for (int i = 1; i < N; i <<= 1)
	{
		double theta = PI / i * (inv ? 1 : -1);
		complexF w(cos(theta), sin(theta));

		int d_i = i << 1;

		for (int j = 0; j < N; j += d_i)
		{
			complexF product(1, 0);
			for (int k = 0; k < i; k++)
			{
				complexF a = v[j + k], b = v[i + j + k] * product;
				v[j + k] = a + b;
				v[i + j + k] = a - b;
				product *= w;
			}
		}
	}

	if (inv)
		for (int i = 0; i < N; i++)
			v[i] /= N;
}

void convSquare(complexF a[])
{
	FFT(a, 0);
	for (int i = 0; i < MAX; i++) a[i] *= a[i];
	FFT(a, 1);
}

int T, N;
bool chk[MAX >> 1], flag;
complexF prime[MAX];
ll ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	chk[0] = chk[1] = 1;

	for (ll i = 2; i < 1e6; i++)
		if (!chk[i])
		{
			prime[i] = complexF(1, 0);

			for (ll j = i * i; j < 1e6; j += i)
				chk[j] = 1;
		}

	convSquare(prime);

	cin >> T;

	while (T--)
	{
		cin >> N;
		ans = round(prime[N].real());
		flag = !chk[N >> 1];
		if ((N >> 1) % 2 == 0 && (N >> 1) > 2) flag = 0;
		if (flag) ans--; //format of N = p+p. (only one exists)

		cout << ((ans >> 1) + flag) << '\n'; //half + one (p+p format)
	}
	return 0;
}

//FFT
//TL is 0.5 second???