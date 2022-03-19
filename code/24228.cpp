#include <iostream>
#include <algorithm>

using namespace std;

long long N, R;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> R;

	cout << N + 2 * R - 1;
	return 0;
}