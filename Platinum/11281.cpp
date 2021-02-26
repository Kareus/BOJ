#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

int N, M, x, a, b, d[20005], SCC[20005], S;
stack<int> s;
vector<int> neighbor[20005];
int var[10001];

int getNode(int x) //t f t f ...
{
	if (x < 0) return getNode(-x) + 1;
	else return 2 * (x - 1);
}

int Not(int x)
{
	return x % 2 ? x - 1 : x + 1;
}

int dfs(int node)
{
	d[node] = ++x;
	s.push(node);

	int parent = d[node];

	for (int i : neighbor[node])
		if (d[i] == 0) parent = min(parent, dfs(i));
		else if (SCC[i] == 0) parent = min(parent, d[i]);

	if (parent == d[node])
	{
		int num;

		do
		{
			num = s.top();
			s.pop();
			SCC[num] = S;
		} while (num != node);

		S++;
	}

	return parent;
}

int main()
{
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	x = 0;
	S = 1;

	memset(d, 0, sizeof(d));
	memset(SCC, 0, sizeof(SCC));
	memset(var, -1, sizeof(var));

	for (int i = 0; i < 2 * N; i++)
		neighbor[i].clear();

	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		a = getNode(a);
		b = getNode(b);

		neighbor[Not(a)].push_back(b);
		neighbor[Not(b)].push_back(a);
	}

	for (int i = 0; i < 2 * N; i++)
		if (d[i] == 0) dfs(i);

	bool ans = 1;
	vector<pair<int, int>> p;

	for (int i = 0; i < N; i++)
		if (SCC[2 * i] == SCC[2 * i + 1])
		{
			ans = 0;
			break;
		}
		else
		{
			p.emplace_back(SCC[2 * i], 2 * i);
			p.emplace_back(SCC[2 * i + 1], 2 * i + 1);
		}

	cout << ans << '\n';

	if (ans == 1)
	{
		sort(p.begin(), p.end());

		for (auto i = p.rbegin(); i != p.rend(); i++)
		{
			int v = i->second;

			if (var[v >> 1] == -1) var[v >> 1] = (v % 2);
		}

		for (int i = 0; i < N; i++)
			cout << var[i] << ' ';
	}
	return 0;
}