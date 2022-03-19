#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

struct lazy_segTree
{
	ll v[1 << 18], lazy[1 << 18];

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

int N, M;
ll a, b, c, d, inp[1000001];
lazy_segTree tree;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) cin >> inp[i];

	cin >> M;

	while (M--)
	{
		cin >> a >> b;
		if (a == 1)
		{
			cin >> c >> d;
			tree.update(1, 0, N - 1, b - 1, c - 1, d);
		}
		else cout << inp[b - 1] + tree.query(1, 0, N - 1, b - 1, b - 1) << '\n';
	}

	return 0;
}

/*
result of changed value A[x] = origianl A[x] + d (difference).
we would save only difference in segment tree. (original is in input array)
difference is 0 at first, so we don't need to initialize.
only need to update difference.
just print original A[x] + difference.
*/