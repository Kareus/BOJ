#include <iostream>
#include <algorithm>

using namespace std;

int N, K, coin[101], ans[10001];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;

	for (int i = 0; i < N; i++) cin >> coin[i];
	sort(coin, coin + N);

	ans[0] = 1;

	for (int i = 0; i < N; i++)
		for (int j = coin[i]; j <= K; j++)
			ans[j] += ans[j - coin[i]];

	cout << ans[K];
	return 0;
}