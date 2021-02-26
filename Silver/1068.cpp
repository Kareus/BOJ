#include <iostream>
#include <vector>

using namespace std;

int N, x, r;
vector<int> graph[51];

int dfs(int v)
{
	if (v == x) return 0;

	int ret = 0, cnt = 0;

	for (int& i : graph[v])
	{
		ret += dfs(i);
		if (i != x) cnt++;
	}

	return ret + (cnt == 0); //non-leaf node can be leaf node if its only leaf node is deleted!
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> x;
		if (x == -1) r = i;
		else graph[x].push_back(i);
	}

	cin >> x;
	cout << dfs(r);

	return 0;
}
