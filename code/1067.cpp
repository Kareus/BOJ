#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> complexF;
const double PI = 3.14159265359;

void FFT(vector<complexF>& v, complexF w)
{
	if (v.size() == 1) return;

	int N = v.size();
	vector<complexF> odd, even;

	for (int i = 0; i < N; i++)
		(i % 2 ? odd : even).push_back(v[i]);

	FFT(even, w * w);
	FFT(odd, w * w);

	complexF product(1, 0);

	N >>= 1;
	for (int i = 0; i < N; i++)
	{
		v[i] = even[i] + product * odd[i];
		v[i + N] = even[i] - product * odd[i];
		product *= w;
	}
}

vector<complexF> convolution(vector<complexF> a, vector<complexF> b)
{
	int N = 1;
	while (N <= a.size() || N <= b.size()) N <<= 1;
	N <<= 1;

	a.resize(N);
	b.resize(N);

	vector<complexF> res;
	res.resize(N);

	complexF w(cos(2 * PI / N), sin(2 * PI / N));

	FFT(a, w);
	FFT(b, w);

	for (int i = 0; i < N; i++)
		res[i] = a[i] * b[i];

	FFT(res, complexF(1, 0) / w);

	for (int i = 0; i < N; i++)
	{
		res[i] /= complexF(N, 0);
		res[i] = complexF(round(res[i].real()), round(res[i].imag()));
	}

	return res;
}

int N;
vector<int> x, y;
long long ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	x.resize(N << 1);
	y.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> x[i];
		x[i + N] = x[i];
	}

	for (int i = N - 1; i >= 0; i--) cin >> y[i];

	vector<complexF> cx(x.begin(), x.end()), cy(y.begin(), y.end());

	vector<complexF> res = convolution(cx, cy);

	for (auto& i : res) ans = max(ans, (long long)i.real());

	cout << ans;
	return 0;
}

//Fast Fourier Transform
//Theory explanation from https://blog.naver.com/kks227/221633584963