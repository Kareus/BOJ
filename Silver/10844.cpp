#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1e9;
int N, d[101][10], ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= 9; i++) d[1][i] = 1;

	for (int i = 2; i <= N; i++)
	{
		d[i][0] = d[i - 1][1];
		d[i][9] = d[i - 1][8];

		for (int j = 1; j < 9; j++)
			d[i][j] = (d[i - 1][j - 1] + d[i - 1][j + 1]) % MOD;
	}

	for (int i = 0; i <= 9; i++) ans = (ans + d[N][i]) % MOD;

	cout << ans;
	return 0;
}