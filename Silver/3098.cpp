#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int N, M, F, a, b, d[51][51], con[51], K = 0, ans = 0;
vector<int> graph[51];
bool nex;

bool bfs(int i)
{
	d[i][i] = 0;

	vector<int> fri;

	for (int& adj : graph[i])
		for (int& next : graph[adj])
			if (d[i][next] < 0 && d[adj][next] < K)
			{
				d[i][next] = K;
				fri.emplace_back(next);
			}

	for (int& n : fri)
		graph[i].emplace_back(n);

	return !fri.empty();
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	memset(d, -1, sizeof(d));

	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;

		graph[a].emplace_back(b);
		graph[b].emplace_back(a);
		d[a][b] = d[b][a] = 0;
	}

	nex = 1;

	while (nex)
	{
		nex = 0;
		K++;

		for (int i = 1; i <= N; i++)
			nex |= bfs(i);
	}

	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			con[d[i][j]]++;

	K--;

	cout << K << '\n';

	for (int i = 1; i <= K; i++)
		cout << con[i] << '\n';
	return 0;
}