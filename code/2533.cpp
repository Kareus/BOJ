#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int N, u, v, d[1000001][2];
vector<int> inp[1000001], graph[1000001];
bool visited[1000001];

void dfs(int i) //generate rooted tree from input
{
	visited[i] = 1;

	for (int& next : inp[i])
		if (!visited[next])
		{
			graph[i].push_back(next);
			dfs(next);
		}
}

int getEA(int node, bool on) //node is early adaptor when on is true
{
	int& ret = d[node][on];
	if (ret != -1) return ret;
	ret = 0;

	if (on)
	{
		for (int& next : graph[node])
			ret += min(getEA(next, 0), getEA(next, 1)); //ea or not

		ret++; //node is ea
	}
	else
		for (int& next : graph[node])
			ret += getEA(next, 1); //neighbor should be only ea

	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 1; i < N; i++)
	{
		cin >> u >> v;
		inp[u].push_back(v);
		inp[v].push_back(u);
	}

	dfs(1); //root node is 1

	memset(d, -1, sizeof(d));

	cout << min(getEA(1, 0), getEA(1,1));
	return 0;
}