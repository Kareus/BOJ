#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, d[100001], a, b, ind = 0, ans = 0;
bool cut[100001];
vector<int> v[10001], c;

int dfs(int cur, bool root) //articulation point
{
	int r = d[cur] = ++ind, child = 0;

	for (int to : v[cur])
		if (!d[to])
		{
			child++;
			int first = dfs(to, 0); //first visited node

			if (!root && first >= d[cur]) cut[cur] = 1;

			r = min(r, first);
		}
		else
			r = min(r, d[to]);

	if (root) cut[cur] = child >= 2;
	return r;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	} //edge can be duplication

	for (int i = 1; i <= N; i++)
		if (!d[i]) dfs(i, 1);

	for (int i = 1; i <= N; i++)
		if (cut[i])
		{
			ans++;
			c.push_back(i);
		}

	cout << ans << '\n';
	for (int& i : c) cout << i << ' ';
	return 0;
}