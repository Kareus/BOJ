//note: same as 2188
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int N, M, a, b, matchA[101], matchB[101];
bool graph[101][101], visited[101];

bool dfs(int a)
{
	if (visited[a]) return 0;
	visited[a] = 1;

	for (int b = 1; b <= N; b++)
		if (graph[a][b])
			if (matchB[b] == -1 || dfs(matchB[b]))
			{
				matchA[a] = b;
				matchB[b] = a;

				return 1;
			}

	return 0;
}

int match()
{
	memset(matchA, -1, sizeof(matchA));
	memset(matchB, -1, sizeof(matchB));

	int connected = 0;

	for (int i = 1; i <= N; i++)
	{
		memset(visited, 0, sizeof(visited));

		if (dfs(i)) connected++;
	}

	return connected;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		graph[a][b] = 1;
	}

	cout << match();
	return 0;
}