#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long ll;

unordered_map<int, ll> ans;

struct Trie
{
	unordered_map<int, Trie*> next;
	int S, val;
	int finish;

	Trie() : S(0), finish(0), val(-1)
	{
	}

	~Trie()
	{
		for (auto& p : next)
			delete p.second;
	}

	void insert(vector<int>& v, int key)
	{
		if (key >= v.size())
		{
			finish++;
			return;
		}

		if (next.find(v[key]) == next.end())
		{
			next[v[key]] = new Trie;
			next[v[key]]->val = v[key];
		}

		next[v[key]]->insert(v, key + 1);
	}

	int solve()
	{
		S = 0;
		ll cnt = 0, sq = 0;
		for (auto& p : next)
		{
			cnt = p.second->solve();
			S += cnt;
			sq += cnt * cnt;
		}

		ans[val] += ((ll)S * S - sq) / 2;
		return S += finish;
	}
};

Trie trie;
int N, Q, S, a;
vector<int> A;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> Q;
	for (int i = 0; i < N; i++)
	{
		cin >> S;
		A.clear();
		for (int j = 0; j < S; j++)
		{
			cin >> a;
			A.push_back(a);
		}

		trie.insert(A, 0);
	}

	trie.solve();
	
	while (Q--)
	{
		cin >> a;
		cout << ans[a] << '\n';
	}
	return 0;
}