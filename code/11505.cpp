#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
int N, M, K, a, b;
ll c;
vector<ll> inp;

struct segTree
{
	vector<ll> v;
	int size;

	void assign(int N)
	{
		int h = ceil(log2(N));
		int size = 1 << (h + 1);
		v.resize(size, 1);
	}

	ll init(vector<ll>& input, int index, int start, int end)
	{
		if (start == end) return v[index] = input[start];

		int mid = (start + end) >> 1;

		return v[index] = (init(input, index << 1, start, mid) * init(input, index << 1 | 1, mid + 1, end)) % MOD;
	}

	ll update(int node, int start, int end, int index, ll& now) 
	{
		if (index < start || index > end) return v[node];

		if (start == end) return v[node] = now;

		int mid = (start + end) >> 1;
		return v[node] = (update(node << 1, start, mid, index, now) * update(node << 1 | 1, mid + 1, end, index, now)) % MOD;
	}

	ll query(int node, int start, int end, int from, int to)
	{
		if (from > end || to < start) return 1;

		if (from <= start && end <= to) return v[node];

		int mid = (start + end) >> 1;

		ll res = (query(node << 1, start, mid, from, to) * query(node << 1 | 1, mid + 1, end, from, to)) % MOD;
		return res;
	}
};

segTree seg;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> K;

	M += K;

	for (int i = 0; i < N; i++)
	{
		cin >> a;
		inp.push_back(a);
	}

	seg.assign(N);
	seg.init(inp, 1, 0, N - 1);

	while (M--)
	{
		cin >> a >> b >> c;

		if (a == 1)
			seg.update(1, 0, N - 1, b - 1, c);
		else
			cout << seg.query(1, 0, N - 1, b - 1, c - 1) << '\n';
	}
	return 0;
}