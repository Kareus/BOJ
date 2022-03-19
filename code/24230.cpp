#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, color[200001], a, b;
vector<int> graph[200001];
bool v[200001];

int dfs(int node, int c)
{
	int ret = color[node] != c;
	v[node] = 1;

	for (int& adj : graph[node])
		if (!v[adj]) ret += dfs(adj, color[node]);

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) cin >> color[i];

	for (int i = 1; i < N; i++)
	{
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	cout << dfs(1, 0);
	return 0;
}