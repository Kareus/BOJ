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
	vector<complexF> roots(N >> 1);

	for (int i = 1; i < N; i++)
	{
		int bit = (N >> 1);

		while (j >= bit)
		{
			j -= bit;
			bit >>= 1;
		}

		j += bit;
		if (i < j) swap(v[i], v[j]);
	}

	double theta = 2 * PI / N * (inv ? -1 : 1);

	for (int i = 0; i < (N >> 1); i++)
		roots[i] = complexF(cos(theta * i), sin(theta * i));

	for (int i = 2; i <= N; i <<= 1)
	{
		int step = N / i;

		for (int j = 0; j < N; j += i)
			for (int k = 0; k < (i >> 1); k++)
			{
				complexF a = v[j + k], b = v[j + k + i / 2] * roots[step * k];
				v[j + k] = a + b;
				v[j + k + i / 2] = a - b;
			}
	}

	if (inv)
		for (int i = 0; i < N; i++)
			v[i] /= N;
}

vector<ll> convolution(vector<complexF> a, vector<complexF> b)
{
	int N = 2;
	while (N < a.size() + b.size()) N <<= 1;

	a.resize(N);
	b.resize(N);

	FFT(a, 0);
	FFT(b, 0);

	for (int i = 0; i < N; i++)
		a[i] *= b[i];

	FFT(a, 1);

	vector<ll> res(N);

	for (int i = 0; i < N; i++) res[i] = (ll)round(a[i].real());

	return res;
}

const int MAX = 1e6;
int T, N;
bool chk[1000001];
vector<ll> p1(MAX), p2(MAX);
ll ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	for (int i = 2; i < MAX; i++)
		if (chk[i]) continue;
		else
		{
			p1[i] = 1;
			if (i <= MAX / 2) p2[i << 1] = 1;

			for (int j = i << 1; j < MAX; j += i)
				chk[j] = 1;

		} //prime table -> p1 and 2*p2

	vector<complexF> cp1(p1.begin(), p1.end()), cp2(p2.begin(), p2.end());
	vector<ll> res = convolution(cp1, cp2);

	cin >> T;

	while (T--)
	{
		cin >> N;

		cout << res[N] << '\n';
	}
	return 0;
}

//FFT
//beware of TLE