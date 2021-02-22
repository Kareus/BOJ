#include <iostream>

using namespace std;

int T, N, M, x;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> T;

	while (T--)
	{
		cin >> N >> M;
		for (int i = 0; i < M; i++) cin >> x >> x;

		cout << N - 1 << '\n';
	}
	return 0;
}

/*
no same kind of airplane here, an edge means one.
So there can't be less kinds than N - 1 (case of making tree)
You can just print N - 1, as you can make a tree from any connected graph.
*/