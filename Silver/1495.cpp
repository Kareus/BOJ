#include <iostream>
#include <algorithm>

using namespace std;

int N, M, S, V, ans = -1;
bool vol[101][1001];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> S >> M;

	vol[0][S] = 1;

	for (int i = 0; i < N; i++)
	{
		cin >> V;
		for (int j = 0; j <= M; j++)
			if (vol[i][j])
			{
				if (j - V >= 0) vol[i + 1][j - V] = 1;
				if (j + V <= M) vol[i + 1][j + V] = 1;
			}
	}

	for (int i = M; i >= 0; i--)
		if (vol[N][i])
		{
			ans = i;
			break;
		}

	cout << ans;
	return 0;
}