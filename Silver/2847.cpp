#include <iostream>

using namespace std;

int N, arr[101], ans = 0;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) cin >> arr[i];

	for (int i = N - 1; i >= 1; i--) //no matter until i >= 0
		if (arr[i] >= arr[i + 1])
		{
			ans += arr[i] - arr[i + 1] + 1;
			arr[i] = arr[i + 1] - 1;
		}

	cout << ans;
	return 0;
}