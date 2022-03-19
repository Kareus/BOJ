#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

struct edge
{
	int node;
	bool dir;
	int idx;
	edge(int n, bool d, int i) : node(n), dir(d), idx(i) {};
};

int N, u, v, d[100001], M = 101010, Mi;
vector<edge> graph[100001];
bool visited[100001];
string ans;

int dfs1(int cur)
{
	visited[cur] = 1;

	int ret = 0;
	for (auto& p : graph[cur])
		if (!visited[p.node]) ret += dfs1(p.node) + p.dir;
	return ret;
}

void dfs2(int from, int to, bool dir)
{
	visited[to] = 1;
	if (dir) d[to] = d[from] - 1;
	else d[to] = d[from] + 1;

	for (auto& p : graph[to])
		if (!visited[p.node]) dfs2(to, p.node, p.dir);
}

void dfs3(int cur)
{
	visited[cur] = 1;
	for (auto& p : graph[cur])
		if (!visited[p.node])
		{
			ans[p.idx] = p.dir + '0';
			dfs3(p.node);
		}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	ans.resize(N - 1);

	for (int i = 1; i < N; i++)
	{
		cin >> u >> v;
		graph[u].emplace_back(v, 0, i - 1);
		graph[v].emplace_back(u, 1, i - 1);
	}

	d[1] = dfs1(1);

	memset(visited, 0, sizeof(visited));
	visited[1] = 1;
	for (auto& p : graph[1])
		dfs2(1, p.node, p.dir);

	for (int i = 1; i <= N; i++)
		if (M > d[i])
		{
			M = d[i];
			Mi = i;
		}

	memset(visited, 0, sizeof(visited));
	dfs3(Mi);

	cout << ans;
	return 0;
}