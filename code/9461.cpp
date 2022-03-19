#include <iostream>

using namespace std;

int T, N;
long long arr[101];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	arr[1] = arr[2] = arr[3] = 1;
	arr[4] = 2;

	for (int i = 5; i <= 100; i++)
		arr[i] = arr[i - 1] + arr[i - 5]; //or you can use arr[i - 2] + arr[i - 3]. got the equation from just decomposing triangle edges.

	cin >> T;

	while (T--)
	{
		cin >> N;
		cout << arr[N] << '\n';
	}
	return 0;
}