#include <iostream>

using namespace std;

int M, N, B, arr[501][501], low = 300, sum = 0, t = 1e9, h = 0, cur;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> B;

	sum += B;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> arr[i][j];
			low = min(low, arr[i][j]);
			sum += arr[i][j];
		}

	while (low <= 256 && low*N*M <= sum)
	{
		cur = 0;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cur += (arr[i][j] > low ? 2 * (arr[i][j] - low) : low - arr[i][j]);

		if (t >= cur)
		{
			t = cur;
			h = low;
		}

		low++;
	}

	cout << t << ' ' << h;
	return 0;
}