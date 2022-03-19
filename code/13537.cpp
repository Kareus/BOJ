#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct mergeTree
{
	vector<int> v[1 << 18];

	void init(int* input, int index, int start, int end)
	{
		if (start == end)
		{
			v[index].push_back(input[start]);
			return;
		}

		int mid = (start + end) >> 1;

		init(input, index << 1, start, mid);
		init(input, index << 1 | 1, mid + 1, end);

		v[index].resize(v[index << 1].size() + v[index << 1 | 1].size());
		merge(v[index << 1].begin(), v[index << 1].end(), v[index << 1 | 1].begin(), v[index << 1 | 1].end(), v[index].begin());
	}

	int query(int index, int start, int end, int left, int right, int k)
	{
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return v[index].end() - upper_bound(v[index].begin(), v[index].end(), k);

		int mid = (start + end) >> 1;
		return query(index << 1, start, mid, left, right, k) + query(index << 1 | 1, mid + 1, end, left, right, k);
	}
};

int N, M, a, b, c, inp[100001];
mergeTree tree;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) cin >> inp[i];

	tree.init(inp, 1, 0, N - 1);

	cin >> M;

	while (M--)
	{
		cin >> a >> b >> c;
		cout << tree.query(1, 0, N - 1, a - 1, b - 1, c) << '\n';
	}

	return 0;
}

//merge sort tree