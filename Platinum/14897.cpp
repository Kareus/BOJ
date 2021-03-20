#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

int N, sN, Q, S, E;

struct query
{
	int i, s, e;

	bool operator<(const query& q) //for mo's algorithm
	{
		if (s / sN != q.s / sN) return s / sN < q.s / sN;
		return e < q.e;
	}
};

vector<query> q;
vector<int> inp, temp;
int ans[1000001], current = 0; //answer for queries, current number of differents
int cnt[1000001]; //number counter

void inc(int i)
{
	if (cnt[inp[i]]++ == 0) current++;
}

void dec(int i)
{
	if (--cnt[inp[i]] == 0) current--;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	sN = sqrt(N);

	inp.resize(N);
	for (int i = 0; i < N; i++) cin >> inp[i];

	temp = inp; //copy
	sort(temp.begin(), temp.end());
	temp.erase(unique(temp.begin(), temp.end()), temp.end()); //make it unique

	for (int i = 0; i < N; i++)
		inp[i] = lower_bound(temp.begin(), temp.end(), inp[i]) - temp.begin(); //number of different K < inp[i]

	cin >> Q;
	q.resize(Q);
	
	for (int i = 0; i < Q; i++)
	{
		cin >> q[i].s >> q[i].e;
		q[i].s--, q[i].e--;
		q[i].i = i;
	}

	sort(q.begin(), q.end());

	S = q[0].s, E = q[0].e;

	for (int i = S; i <= E; i++) inc(i);
	ans[q[0].i] = current;

	for (int i = 1; i < Q; i++)
	{
		while (S < q[i].s) dec(S++);
		while (S > q[i].s) inc(--S);

		while (E < q[i].e) inc(++E);
		while (E > q[i].e) dec(E--);

		ans[q[i].i] = current;
	}

	for (int i = 0; i < Q; i++) cout << ans[i] << '\n';
	return 0;
}

//Mo's algorithm