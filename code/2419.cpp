#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int N, M, x[305], d[305][305][2], ans;
const int MAX = 1e9;

int diminish(int l, int r, int dir, int candy)
{
	if (candy == 0) return 0;

	int& ret = d[l][r][dir];
	if (ret != -1) return ret;
	ret = MAX;

	int current = dir == 0 ? l : r;

	if (r < N - 1)
		ret = min(ret, diminish(l, r + 1, 1, candy - 1) + candy * (x[r + 1] - x[current])); //go right	

	if (l > 0)
		ret = min(ret, diminish(l - 1, r, 0, candy - 1) + candy * (x[current] - x[l - 1])); //go left

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		cin >> x[i];
		if (abs(x[i]) > M) //cannot eat
		{
			i--;
			N--;
		}
	}

	x[N++] = 0; //pivot point for searching
	sort(x, x + N);

	int pivot = lower_bound(x, x + N, 0) - x;

	for (int i = 0; i < N; i++)
	{
		memset(d, -1, sizeof(d));
		ans = max(ans, i * M - diminish(pivot, pivot, 0, i));
	}

	cout << ans;
	return 0;
}

/*
dynamic programming (but idea was too difficult)

count diminishing candies (as eating candy is difficult to count)
let d[L][R][dir] = diminished candy from L (negative area) to R (positive area), while heading in left/right (dir)
but we don't know how many of baskets we can have, so find every case for i baskets
*/