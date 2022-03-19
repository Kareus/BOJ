#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

ll N, A[100001], B[100001], d[100001], ans;

struct line
{
	ll a, b;
	double s = 0;

	line(ll a, ll b, double s) : a(a), b(b), s(s) {}

	bool operator<(const line& l) const
	{
		return s < l.s;
	}
};

vector<line> v;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < N; i++) cin >> B[i];

	v.emplace_back(B[0], 0, 0); //D[i] when j = 0 : y = B[0] * A[i]

	for (int i = 1; i < N; i++)
	{
		line current(0, 0, A[i]); //y = A[i]
		line L = *(upper_bound(v.begin(), v.end(), current) - 1); //find the mininum line when x = A[i]

		d[i] = L.a * A[i] + L.b;

		line nxt(B[i], d[i], 0); //i-th line, based on d[i]
		double crossPoint = 0;

		while (v.size())
		{
			line prv = v.back();
			crossPoint = (double)(prv.b - nxt.b) / (nxt.a - prv.a); //nxt.a - prv.a should not be 0 => B[i] must be unique.

			if (crossPoint <= prv.s) v.pop_back(); //nxt line would result smaller value in [crossPoint, prv.s]. remove prv.
			else break;
		}

		nxt.s = crossPoint;
		v.push_back(nxt);
	}

	cout << d[N - 1];
	return 0;
}