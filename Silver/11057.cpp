#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 10007;
int N, d[1001][10], ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) d[i][0] = 1;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= 9; j++)
			d[i][j] = (d[i - 1][j] + d[i][j - 1]) % MOD;

	for (int i = 0; i <= 9; i++) ans = (ans + d[N][i]) % MOD;

	cout << ans;
	return 0;
}