#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

char m[51][51];
int N, M, visited[51][51], sea_idx = 1, isl_idx = 1, dir[] = { -1,0,1,0,0,-1,0,1,-1,-1,-1,1,1,-1,1,1 };
set<int> graph_sea[2500], graph_isl[2500];
int ans[2500], isg[2500], seg[2500], mx;

void dfs_sea(int x, int y) //first search for finding sea area
{
	visited[y][x] = -sea_idx;
	int nx, ny;

	for (int i = 0; i < 4; i++)
	{
		nx = x + dir[i << 1], ny = y + dir[i << 1 | 1];

		if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
		if (m[ny][nx] == '.' && !visited[ny][nx]) dfs_sea(nx, ny);
	}
}

void dfs_isl(int x, int y) //first search for finding island area
{
	visited[y][x] = isl_idx;

	int nx, ny;

	for (int i = 0; i < 8; i++)
	{
		nx = x + dir[i << 1], ny = y + dir[i << 1 | 1];

		if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
		if (m[ny][nx] == 'x' && !visited[ny][nx]) dfs_isl(nx, ny);
	}
}

void boundaryCheck() //boundary sea check
{
	for (int i = 0; i < M; i++)
	{
		if (m[0][i] == '.' && !visited[0][i]) dfs_sea(i, 0);
		if (m[N - 1][i] == '.' && !visited[N - 1][i]) dfs_sea(i, N - 1);
	}

	for (int i = 0; i < N; i++)
	{
		if (m[i][0] == '.' && !visited[i][0]) dfs_sea(0, i);
		if (m[i][M - 1] == '.' && !visited[i][M - 1]) dfs_sea(M - 1, i);
	}

	sea_idx++;
}

void dfs_sea2(int x, int y, int s) //second search finding sea-island relation
{
	// beaware of negative value. only argument s is positive here. (sorry for bad spaghetti, huh)
	visited[y][x] = 0; //we reset visited to zero for checking in this function (as we filled in first search)
	int nx, ny;

	for (int i = 0; i < 4; i++)
	{
		nx = x + dir[i << 1], ny = y + dir[i << 1 | 1];

		if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;

		if (m[ny][nx] == '.' && visited[ny][nx] == -s) dfs_sea2(nx, ny, s);
		else if (m[ny][nx] == 'x' && visited[ny][nx])
		{
			graph_sea[s].insert(visited[ny][nx]);
			graph_isl[visited[ny][nx]].insert(-s); //insert in opposite, too. as we set visited of current area to 0
		}
	}
}

void dfs_isl2(int x, int y, int s) //second search finding island-sea relation
{
	//actually, has no difference with above function. you can use one of both, but I don't know there is counter.
	visited[y][x] = 0;

	int nx, ny;

	for (int i = 0; i < 8; i++)
	{
		nx = x + dir[i << 1], ny = y + dir[i << 1 | 1];

		if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
		if (m[ny][nx] == 'x' && visited[ny][nx] == s) dfs_isl2(nx, ny, s);
		else if (m[ny][nx] == '.' && visited[ny][nx])
		{
			graph_isl[s].insert(visited[ny][nx]);
			graph_sea[-visited[ny][nx]].insert(s); //negative is evil.
		}
	}
}

int dfs_graph(int current, int parent) //to find height of island
{
	//current > 0 : island, current < 0 : sea
	set<int>& adj = current > 0 ? graph_isl[current] : graph_sea[-current];

	int num = 1;

	for (int a : adj)
		if (a == parent) continue; //avoid re-visiting edges
		else num = max(num, dfs_graph(a, current) + (current < 0)); //add height only we are visiting island from sea

	if (current > 0) isg[current] = num; //set height of island
	return num;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	bool isl = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> m[i][j];
			if (m[i][j] == 'x') isl = 1;
		}

	if (!isl) //no island
	{
		cout << -1;
		return 0;
	}

	boundaryCheck();

	//get area of island or sea
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (!visited[i][j])
				if (m[i][j] == '.')
				{
					dfs_sea(j, i);
					sea_idx++;
				}
				else
				{
					dfs_isl(j, i);
					isl_idx++;
				}

	//get island-sea relation
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (visited[i][j]) m[i][j] == '.' ? dfs_sea2(j, i, -visited[i][j]) : dfs_isl2(j, i, visited[i][j]);

	if (graph_sea[1].empty()) graph_sea[1].insert(1); //no boundary sea

	dfs_graph(-1, 0); //get height

	for (int i = 1; i < isl_idx; i++)
	{
		ans[isg[i]]++;
		mx = max(mx, isg[i]);
	} //count islands in same height

	for (int i = 1; i <= mx; i++)
		cout << ans[i] << ' ';

	return 0;
}

/*
hard bfs/dfs problem, similar to boj 16000 (actually, 16000 was easier for me)
check thers is any island first.
label sea as negative value, island as positive value and graph search it. (I did flood fill)
let boundary sea as -1, (all other sea starts from -2 even if -1 doesn't exist)
redo graph search to find relation of island-sea. (added to each graph vectors for islands and seas)
start from boundary sea (-1).
* if boundary sea doesn't exist, there should be boundary island and it should labeled 1.
* we can connect island 1 to boundary sea, as it doesn't exist. (-1 -> 1)
beware of already visiting edges. I used parent node and current node to avoid re-visiting.
height increments when the inner sea has inner islands.
height starts from 1 (not 0) in this code.
*/