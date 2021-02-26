#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, input[100001];

struct segTree
{
	vector<int> v;

	void assign(int N)
	{
		int h = ceil(log2(N));
		int size = 1 << (h + 1);
		v.clear();
		v.resize(size);
	}

	int init(int* input, int index, int start, int end)
	{
		if (start == end) return v[index] = start;

		int mid = (start + end) >> 1;

		int left = init(input, index << 1, start, mid), right = init(input, index << 1 | 1, mid + 1, end);

		return v[index] = (input[left] <= input[right] ? left : right);
	}

	int query(int index, int start, int end, int left, int right)
	{
		if (left > end || right < start) return -1;
		if (left <= start && end <= right) return v[index];

		int mid = (start + end) >> 1;
		int L = query(index << 1, start, mid, left, right), R = query(index << 1 | 1, mid + 1, end, left, right);

		if (L < 0 && R < 0) return -1;
		if (L < 0) return R;
		if (R < 0) return L;

		return (input[L] <= input[R] ? L : R);
	}

};

segTree s;

long long getMaxArea(int start, int end)
{
	if (start > end) return 0;
	if (start == end) return input[start];

	long long ret = end - start + 1;
	int pivot = s.query(1, 0, N - 1, start, end);
	ret *= input[pivot]; //current max area

	return max({ getMaxArea(start, pivot - 1), getMaxArea(pivot + 1, end), ret });
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	while (1)
	{
		cin >> N;

		if (N == 0) break;

		for (int i = 0; i < N; i++) cin >> input[i];

		s.assign(N);
		s.init(input, 1, 0, N - 1);

		cout << getMaxArea(0, N - 1) << '\n';
	}
	return 0;
}