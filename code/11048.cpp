#include <iostream>
#include <algorithm>

using namespace std;

int N, M, d[1001][1001];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			cin >> d[i][j];
			d[i][j] += max(d[i - 1][j], d[i][j - 1]);
		}

	cout << d[N][M];
	return 0;
}