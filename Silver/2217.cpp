#include <iostream>
#include <algorithm>

using namespace std;

int N, rope[100001], ans = 0;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) cin >> rope[i];

	sort(rope, rope + N);

	for (int i = 0; i < N; i++) ans = max(ans, (N - i) * rope[i]);

	cout << ans;
	return 0;
}