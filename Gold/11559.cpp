#include <iostream>
#include <string.h>

using namespace std;

int ans;
char m[12][6];
bool con = 1, visited[12][6];

int dfs(int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= 6 || y >= 12) return 0;
	if (m[y][x] != c) return 0;
	if (visited[y][x]) return 0;
	visited[y][x] = 1;

	return dfs(x - 1, y, c) + dfs(x + 1, y, c) + dfs(x, y - 1, c) + dfs(x, y + 1, c) + 1;
}

void puyo(int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= 6 || y >= 12) return;
	if (m[y][x] != c) return;

	m[y][x] = '.';
	puyo(x + 1, y, c);
	puyo(x - 1, y, c);
	puyo(x, y - 1, c);
	puyo(x, y + 1, c);
}

void down(int x, int y)
{
	for (int i = y; i >= 0; i--)
		if (m[i][x] != '.')
		{
			m[y][x] = m[i][x];
			m[i][x] = '.';
			break;
		}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 0; i < 12; i++) cin >> m[i];

	while (con)
	{
		con = 0;
		memset(visited, 0, sizeof(visited));

		for (int i = 0; i < 6; i++)
			for (int j = 11; j >= 0; j--)
				if (m[j][i] == '.') continue;
				else if (dfs(i, j, m[j][i]) >= 4)
				{
					con = 1;
					puyo(i, j, m[j][i]);
				}

		for (int i = 0; i < 6; i++)
			for (int j = 11; j >= 0; j--)
				if (m[j][i] == '.') down(i, j);

		ans += con;
	}

	cout << ans;
	return 0;
}

/*
just an implementation
*/