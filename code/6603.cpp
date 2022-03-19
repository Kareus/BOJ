#include <iostream>

using namespace std;

int K, l[14], p[6];

void lotto(int i, int n)
{
	p[n] = l[i];

	if (n == 5)
	{
		for (int j = 0; j < 6; j++) cout << p[j] << ' ';
		cout << '\n';
		return;
	}

	for (int j = i + 1; j < K; j++)
		lotto(j, n + 1);
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (cin >> K)
	{
		if (K == 0) break;

		for (int i = 0; i < K; i++) cin >> l[i];

		for (int i = 0; i <= K - 6; i++)
			lotto(i, 0);

		cout << '\n';
	}
	return 0;
}

//backtracking