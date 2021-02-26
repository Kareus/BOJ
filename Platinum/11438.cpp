#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int d[100001], lca[100001][20];
int md = (int)log2(100001);
vector<int> g[100001];
int N, M, a, b;

void makeTree(int current, int parent) //establish tree and lca
{
	d[current] = d[parent] + 1;
	lca[current][0] = parent;

	for (int i = 1; i <= md; i++)
		lca[current][i] = lca[lca[current][i - 1]][i - 1]; //current node's 2^i-th ancestor

	for (int& i : g[current])
		if (i != parent)
			makeTree(i, current);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 1; i < N; i++)
	{
		cin >> a >> b ;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	//don't need to reset depth (no same edge in input)
	makeTree(1, 0);

	cin >> M;

	while (M--)
	{
		cin >> a >> b;

		if (d[a] != d[b]) //get to same depth
		{
			if (d[a] > d[b]) swap(a, b);

			for (int i = md; i >= 0; i--)
				if (d[a] <= d[lca[b][i]]) b = lca[b][i];
		}

		if (a != b) //find lca
		{
			for (int i = md; i >= 0; i--)
				if (lca[a][i] != lca[b][i])
					a = lca[a][i], b = lca[b][i];

			//now a,b is under same ancestor
			a = lca[a][0];
		}

		cout << a << '\n';
	}

	return 0;
}
