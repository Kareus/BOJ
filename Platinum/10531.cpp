#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> complexF;
typedef long long ll;

const double PI = 3.14159265359;

void FFT(vector<complexF>& v, bool inv)
{
	int N = v.size(), j = 0;

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

void convSquare(vector<complexF>& v)
{
	int n = 1;

	while (n <= v.size()) n <<= 1;
	n <<= 1;
	v.resize(n);

	FFT(v, 0);
	for (int i = 0; i < n; i++) v[i] *= v[i];
	FFT(v, 1);
}

int N, M, d, x;
vector<complexF> k(200005);
ll ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> x;
		k[x] = complexF(1, 0);
	}

	k[0] = complexF(1, 0);
	convSquare(k);

	cin >> M;

	while (M--)
	{
		cin >> d;
		if (round(k[d].real()) > 0) ans++;
	}

	cout << ans;
	return 0;
}

//FFT