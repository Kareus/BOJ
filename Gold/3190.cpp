#include <iostream>
#include <deque>

using namespace std;

int N, K, L, ax, ay, tX, tY, nX, nY, ans, m[101][101], dir[] = {1,0,0,1,-1,0,0,-1}, d = 0, j = 0;
pair<int, char> r[101];
deque<pair<int, int>> snake;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;

	while (K--)
	{
		cin >> ay >> ax;
		m[ay - 1][ax - 1] = 1;
	}

	m[0][0] = 2;
	snake.emplace_back(0, 0);

	cin >> L;
	for (int i = 0; i < L; i++)
		cin >> r[i].first >> r[i].second;

	while (1)
	{
		ans++;

		tX = snake.back().first, tY = snake.back().second;
		nX = snake.front().first + dir[d << 1], nY = snake.front().second + dir[d << 1 | 1];

		if (nX < 0 || nX >= N || nY < 0 || nY >= N)
			break;
		else if (m[nY][nX] == 2)
			break;
		else if (m[nY][nX] != 1)
		{	
			m[tY][tX] = 0;
			snake.pop_back();
		}

		m[nY][nX] = 2;
		snake.emplace_front(nX, nY);

		if (j >= L || r[j].first != ans) continue;

		if (r[j].second == 'L') d = (d + 3) % 4;
		else d = (d + 1) % 4;

		j++;
	}

	cout << ans;
	return 0;
}