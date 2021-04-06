#include <iostream>
#include <unordered_map>

using namespace std;

int N, M, op, i, x, train[100001], ans;
unordered_map<int, bool> check;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	while (M--)
	{
		cin >> op >> i;

		if (op <= 2)
		{
			cin >> x;

			x = 1 << (x - 1);
			if (op == 1) train[i] |= x;
			else train[i] &= ((1 << 20) - 1) - x;
		}
		else if (op == 3) train[i] = (train[i] << 1 & ((1 << 20) - 1));
		else train[i] >>= 1;
	}

	for (int i = 1; i <= N; i++)
		if (check[train[i]]) continue;
		else
		{
			check[train[i]] = 1;
			ans++;
		}

	cout << ans;
	return 0;
}

/*
bitmask
I got many WA on this, huh. (due to problem about index and handling 0th and 21th bits)
and... tested about bitset and counting uniques, resulted in bunch of WAs.
just solve with integer, go steady. do not experiment like me, lol
*/