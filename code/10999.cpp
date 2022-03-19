#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

struct lazy_segTree
{
	vector<ll> v, lazy;

	void assign(int s)
	{
		int h = ceil(log2(s));
		int size = 1 << (h + 1);
		v.resize(size, 0);
		lazy.resize(size, 0);
	}

	ll init(ll* input, int index, int start, int end)
	{
		if (start == end) return v[index] = input[start];

		int mid = (start + end) >> 1;

		return v[index] = init(input, index << 1, start, mid) + init(input, index << 1 | 1, mid + 1, end);
	}

	void lazy_update(int node, int start, int end)
	{
		if (lazy[node])
		{
			v[node] += lazy[node] * (end - start + 1);

			if (start != end)
			{
				lazy[node << 1] += lazy[node];
				lazy[node << 1 | 1] += lazy[node];
			}

			lazy[node] = 0;
		}
	}

	void update(int node, int start, int end, int left, int right, ll val)
	{
		lazy_update(node, start, end);

		if (left > end || right < start) return;

		if (left <= start && end <= right)
		{
			v[node] += val * (end - start + 1);

			if (start != end)
			{
				lazy[node << 1] += val;
				lazy[node << 1 | 1] += val;
			}
			return;
		}

		int mid = (start + end) >> 1;
		update(node << 1, start, mid, left, right, val);
		update(node << 1 | 1, mid + 1, end, left, right, val);
		v[node] = v[node << 1] + v[node << 1 | 1];
	}

	ll query(int index, int start, int end, int left, int right)
	{
		lazy_update(index, start, end);
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return v[index];

		int mid = (start + end) >> 1;
		return query(index << 1, start, mid, left, right) + query(index << 1 | 1, mid + 1, end, left, right);
	}
};

int N, M, K;
ll a, b, c, d, inp[1000001];
lazy_segTree tree;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) cin >> inp[i];

	tree.assign(N);
	tree.init(inp, 1, 0, N - 1);

	M += K;

	while (M--)
	{
		cin >> a >> b >> c;
		if (a == 1)
		{
			cin >> d;
			tree.update(1, 0, N - 1, b - 1, c - 1, d);
		}
		else cout << tree.query(1, 0, N - 1, b - 1, c - 1) << '\n';
	}

	return 0;
}