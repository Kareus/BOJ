#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int N, arr[300001], th;
double ans = 0;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	if (N == 0)
	{
		cout << 0;
		return 0;
	}

	for (int i = 0; i < N; i++) cin >> arr[i];
	sort(arr, arr + N);

	th = round(N * 15.0 / 100);

	for (int i = th; i < N - th; i++) ans += arr[i];

	cout << round(ans / (N - 2 * th));
	return 0;
}