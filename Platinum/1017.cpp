#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

bool prime[2010], visited[51];
int N, a, matchA[51], matchB[51], X;
vector<int> g1, g2;

bool dfs(int a)
{
	if (visited[a]) return 0;
	visited[a] = 1;

	for (int b = 0; b < g2.size(); b++)
		if (b == X) continue;
		else if (!prime[g1[a] + g2[b]]) continue;
		else if (matchB[b] == -1 || dfs(matchB[b]))
		{
			matchA[a] = b;
			matchB[b] = a;
			return 1;
		}

	return 0;
}

bool match()
{
	if (!prime[g1[0] + g2[X]]) return 0;

	memset(matchA, -1, sizeof(matchA));
	memset(matchB, -1, sizeof(matchB));

	matchA[0] = X;
	matchB[X] = 0;

	int connected = 1;

	for (int i = 1; i < g1.size(); i++)
	{
		memset(visited, 0, sizeof(visited));
		visited[0] = 1;
		connected += dfs(i);
	}

	return connected == g1.size();
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	for (int i = 2; i <= 2005; i++)
	{
		prime[i] = 1;

		for (int j = 2; j * j <= i; j++)
			if (i % j == 0)
			{
				prime[i] = 0;
				break;
			}
	}

	cin >> N;

	cin >> a;
	g1.push_back(a);

	for (int i = 1; i < N; i++)
	{
		cin >> a;
		(a % 2 == g1[0] % 2 ? g1 : g2).push_back(a);
	}

	if (g1.size() != g2.size())
	{
		cout << -1;
		return 0;
	}

	int cnt = 0;
	vector<int> v;

	for (X = 0; X < g2.size(); X++)
		if (match())
			v.push_back(g2[matchA[0]]);

	if (v.empty()) cout << -1;
	else
	{
		sort(v.begin(), v.end());
		for (int& i : v) cout << i << ' ';
	}
	return 0;
}