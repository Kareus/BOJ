#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, M, x, y, a, b, d[101], f[101], ans;
vector<int> graph[101];

void dfs(int v, int parent)
{
	if (d[v]) return;
	d[v] = d[parent] + 1;
	f[v] = a;

	for (int& i : graph[v])
		dfs(i, v);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> a >> b >> M;

	while (M--)
	{
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x); //actually, it doesn't matter if y is x's parent to solve.
	}

	dfs(a, 0); //let a is root. otherwise you should use lca.

	if (f[a] != f[b]) cout << -1;
	else cout << abs(d[a] - d[b]);
	return 0;
}
