#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

struct node
{
	ll M, M2, cnt, sum; //M = max, M2 = second max, cnt = count of nodes which max is M
};

struct segTree_beats
{
	node v[1 << 21]; //assign would take long

	node merge(node a, node b)
	{
		if (a.M == b.M) return { a.M, max(a.M2, b.M2), a.cnt + b.cnt, a.sum + b.sum };
		if (a.M < b.M) swap(a, b);
		return { a.M, max(a.M2, b.M), a.cnt, a.sum + b.sum };
	}

	void lazy_update(int node, int start, int end)
	{
		if (start == end) return; //not for leaf node

		if (v[node << 1].M > v[node].M)
		{
			v[node << 1].sum -= v[node << 1].cnt * (v[node << 1].M - v[node].M);
			v[node << 1].M = v[node].M;
		}

		if (v[node << 1 | 1].M > v[node].M)
		{
			v[node << 1 | 1].sum -= v[node << 1 | 1].cnt * (v[node << 1 | 1].M - v[node].M);
			v[node << 1 | 1].M = v[node].M;
		}
	}

	node init(ll* arr, int node, int start, int end)
	{
		if (start == end) return v[node] = { arr[start], -1, 1, arr[start] };

		int mid = (start + end) >> 1;
		return v[node] = merge(init(arr, node << 1, start, mid), init(arr, node << 1 | 1, mid + 1, end));
	}

	void update(int node, int start, int end, int left, int right, ll x)
	{
		lazy_update(node, start, end);

		if (left > end || right < start || v[node].M <= x) return; //break

		if (left <= start && end <= right && v[node].M2 < x) //tag (we need to go further if M2 is still bigger than x)
		{
			v[node].sum -= v[node].cnt * (v[node].M - x);
			v[node].M = x;
			lazy_update(node, start, end);
			return;
		}

		int mid = (start + end) >> 1;
		update(node << 1, start, mid, left, right, x);
		update(node << 1 | 1, mid + 1, end, left, right, x);

		v[node] = merge(v[node << 1], v[node << 1 | 1]);
	}

	ll maxval(int index, int start, int end, int left, int right)
	{
		lazy_update(index, start, end);

		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return v[index].M;

		int mid = (start + end) >> 1;
		return max(maxval(index << 1, start, mid, left, right), maxval(index << 1 | 1, mid + 1, end, left, right));
	}

	ll sum(int index, int start, int end, int left, int right)
	{
		lazy_update(index, start, end);

		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return v[index].sum;

		int mid = (start + end) >> 1;
		return sum(index << 1, start, mid, left, right) + sum(index << 1 | 1, mid + 1, end, left, right);
	}
};

int N, M, op, a, b, c;
ll arr[1000001];
segTree_beats tree;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	tree.init(arr, 1, 0, N - 1);

	cin >> M;

	while (M--)
	{
		cin >> op;
		if (op == 1)
		{
			cin >> a >> b >> c;
			tree.update(1, 0, N - 1, a - 1, b - 1, c);
		}
		else if (op == 2)
		{
			cin >> a >> b;
			cout << tree.maxval(1, 0, N - 1, a - 1, b - 1) << '\n';
		}
		else if (op == 3)
		{
			cin >> a >> b;
			cout << tree.sum(1, 0, N - 1, a - 1, b - 1) << '\n';
		}
	}

	return 0;
}

/*
Segment Tree Beats
*/