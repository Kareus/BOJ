#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int N, sN, Q, S, E, K;

struct query
{
	int i, s, e, k;

	bool operator<(const query& q)
	{
		if (s / sN != q.s / sN) return s / sN < q.s / sN;
		return e < q.e;
	}
};

struct fenwick
{
	int v[MAX];

	void update(int i, int diff)
	{
		while (i <= MAX)
		{
			v[i] += diff;
			i += i & -i;
		}
	}

	ll query(ll i)
	{
		if (i < 1) return 0;
		if (i >= MAX) i = MAX - 1;
		ll ret = 0;

		while (i > 0)
		{
			ret += v[i];
			i -= i & -i;
		}

		return ret;
	}
};

int inpA[MAX], inpB[MAX];
ll ans[MAX];
vector<query> q;
fenwick treeA, treeB;

void inc(int i)
{
	treeA.update(inpA[i], 1);
	treeB.update(inpB[i], 1);
}

void dec(int i)
{
	treeA.update(inpA[i], -1);
	treeB.update(inpB[i], -1);
}

ll getQuery(ll k)
{
	ll sq = sqrt(k), ret = 0;
	for (ll i = 1; i <= sq; i++)
	{
		ret += treeA.query(k / i) * (treeB.query(i) - treeB.query(i - 1));
		ret += (treeB.query(k / i) - treeB.query(sq)) * (treeA.query(i) - treeA.query(i - 1));
	}
	
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	sN = sqrt(N);

	for (int i = 0; i < N; i++)
		cin >> inpA[i];

	for (int i = 0; i < N; i++)
		cin >> inpB[i];

	cin >> Q;
	q.resize(Q);

	for (int i = 0; i < Q; i++)
	{
		cin >> q[i].s >> q[i].e >> q[i].k;
		q[i].s--, q[i].e--;
		q[i].i = i;
	}

	sort(q.begin(), q.end());

	S = q[0].s, E = q[0].e;

	for (int i = S; i <= E; i++) inc(i);
	ans[q[0].i] = getQuery(q[0].k);

	for (int i = 0; i < Q; i++)
	{
		while (S < q[i].s) dec(S++);
		while (S > q[i].s) inc(--S);

		while (E < q[i].e) inc(++E);
		while (E > q[i].e) dec(E--);

		ans[q[i].i] = getQuery(q[i].k);
	}

	for (int i = 0; i < Q; i++) cout << ans[i] << '\n';
	return 0;
}