#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> p;

const int INF = 1e9 + 5;
int N, a[200001];
p range[200001];

struct segTree
{
	p v[1 << 19];

	p update(int node, int start, int end, int index, int minval, int maxval)
	{
		if (index < start || index > end) return v[node];

		if (start != end)
		{
			int mid = (start + end) >> 1;
			p u1 = update(node << 1, start, mid, index, minval, maxval), u2 = update(node << 1 | 1, mid + 1, end, index, minval, maxval);
			return v[node] = { min(u1.first, u2.first), max(u1.second, u2.second) };
		}
		else return v[node] = { minval, maxval };
	}

	p query(int index, int start, int end, int left, int right)
	{
		if (left > end || right < start) return { INF, -INF };
		if (left <= start && end <= right) return v[index];

		int mid = (start + end) >> 1;

		p q1 = query(index << 1, start, mid, left, right), q2 = query(index << 1 | 1, mid + 1, end, left, right);
		return { min(q1.first, q2.first), max(q1.second, q2.second) };
	}
};

int ans = -1;
segTree tree;
p q;
priority_queue<p, vector<p>, greater<p>> L, R;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> a[i] >> range[i].first >> range[i].second;
		L.emplace(i + range[i].first, i);
		R.emplace(i + range[i].second + 1, i);
		tree.update(1, 0, N - 1, i, INF, -INF);
	}

	for (int i = 0; i < N; i++)
	{
		while (L.size() && L.top().first == i)
		{
			int j = L.top().second;
			tree.update(1, 0, N - 1, j, a[j], a[j]);
			L.pop();
		}

		while (R.size() && R.top().first == i)
		{
			tree.update(1, 0, N - 1, R.top().second, INF, -INF);
			R.pop();
		}

		q = tree.query(1, 0, N - 1, i - range[i].second, i - range[i].first);
		ans = max(ans, max(q.second - a[i], a[i] - q.first));
	}

	cout << ans;
	return 0;
}