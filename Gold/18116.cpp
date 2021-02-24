#include <iostream>

using namespace std;

int N, par[1000001], cnt[1000001], a, b;
char op;

int find(int x)
{
	if (par[x] == x) return x;
	return par[x] = find(par[x]);
}

void merge(int a, int b)
{
	a = find(a);
	b = find(b);

	if (a == b) return;

	par[a] = b;
	cnt[b] += cnt[a];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 1; i <= 1000000; i++)
	{
		par[i] = i;
		cnt[i] = 1;
	}

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> op;
		if (op == 'I')
		{
			cin >> a >> b;
			merge(a, b);
		}
		else
		{
			cin >> a;
			cout << cnt[find(a)] << '\n';
		}
	}
	return 0;
}