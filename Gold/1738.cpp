#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct edge
{
	int from, to, cost;
};

int N, M, d[101], p[101], u, v, w;
bool visited[101]; //can visit node N
edge e[20001];
vector<int> parent[101];
queue<int> q;

bool bellman(int S)
{
	d[S] = 0;

	for (int i = 1; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			if (d[e[j].from] == INF) continue;

			int dist = d[e[j].from] + e[j].cost;

			if (d[e[j].to] > dist)
			{
				d[e[j].to] = dist;
				p[e[j].to] = e[j].from;
			}
		}

	for (int i = 0; i < M; i++)
		if (d[e[i].from] == INF || !visited[e[i].from]) continue; //cannot visit from 1 or cannot visit N
		else if (d[e[i].to] > d[e[i].from] + e[i].cost)
			return 1;

	return 0;
}

void printPath(int n)
{
	if (n != 1)
		printPath(p[n]);

	cout << n << ' ';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N; i++) d[i] = INF;

	for (int i = 0; i < M; i++)
	{
		cin >> u >> v >> w;

		e[i].from = u;
		e[i].to = v;
		e[i].cost = -w;
		parent[v].push_back(u);
	}

	visited[N] = 1;
	q.push(N);

	while (q.size())
	{
		int current = q.front();
		q.pop();

		for (int& from : parent[current])
			if (!visited[from])
			{
				visited[from] = 1;
				q.push(from);
			}
	}

	if (bellman(1) || d[N] == INF)
		cout << -1;
	else printPath(N);

	return 0;
}

/*
bellman-ford
should check the node can be visited from node 1, can visit node N.
we can know the former by d[], but not the latter.
you can use floyd or something else to find out (I used visited, going reverse from N)
negative cycle in this problem is, earning infinite money. (positive cycle in real)
weight * -1 should work in general algorithm.
*/