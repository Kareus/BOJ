#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N, M, a, b, cur, cnt = 0;
vector<int> graph[10001];
vector<int> ans;
bool visited[10001];

int dfs(int current)
{
	if (visited[current]) return 0;

	visited[current] = 1;

	int ret = 1;

	for (int& next : graph[current])
		if (!visited[next])
			ret += dfs(next);

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	while (M--)
	{
		cin >> a >> b;
		graph[b].push_back(a);
	}

	for (int i = 1; i <= N; i++)
	{
		memset(visited, 0, sizeof(visited));
		cur = dfs(i);
		if (cnt < cur)
		{
			cnt = cur;
			ans.clear();
			ans.push_back(i);
		}
		else if (cnt == cur) ans.push_back(i);
	}

	sort(ans.begin(), ans.end());

	for (int& i : ans) cout << i << ' ';
	return 0;
}
