#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<double, double> p;
typedef pair<double, int> p2;

struct fish
{
	int S, E, V;

	fish(int s = 0, int e = 0, int v = 0) : S(s), E(e), V(v) {}

	p getTime(fish& f)
	{
		if (V == f.V)
		{
			if (S <= f.S && f.S <= E) return { 1, 1 };
			else return { -1, -1 };
		}

		double s = (double)(f.S - S) / (V - f.V);
		double e = (double)(f.S - E) / (V - f.V);

		return { min(s, e), max(s, e) };
	}
};

bool compare(p2& a, p2& b)
{
	if (a.first != b.first) return a.first < b.first;
	else return a.second > b.second;
}

int N, ans = 1;
fish f[1001];
vector<p2> tm;

int solve(int idx)
{
	tm.clear();

	for (int j = 0; j < N; j++)
	{
		if (idx == j) continue;
		p t = f[j].getTime(f[idx]);

		if (f[idx].V == f[j].V)
		{
			if (t.first > 0) tm.emplace_back(0, 1);
			else continue;
		}
		else
		{
			tm.emplace_back(t.first, 1);
			tm.emplace_back(t.second, -1);
		}
	}

	sort(tm.begin(), tm.end(), compare);
	int cur = 1, ret = 1;

	for (auto& t : tm)
	{
		cur += t.second;
		if (t.first >= 0) ret = max(ret, cur);
	}

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> f[i].S >> f[i].E >> f[i].V;

	for (int i = 0; i < N; i++)
		ans = max(ans, solve(i));

	cout << ans;
	return 0;
}