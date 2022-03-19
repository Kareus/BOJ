#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
string S;
ll d[301][301];

ll getCount(int L, int R)
{
	if (L >= R) return 1;

	ll& ret = d[L][R];
	if (ret >= 0) return ret;
	ret = 0;

	for (int i = L + 1; i <= R; i += 2)
		if (S[L] != S[i]) ret = (ret + getCount(L + 1, i - 1) * getCount(i + 1, R)) % MOD;

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(d, -1, sizeof(d));
	cin >> S;

	if (S.size() % 2) cout << 0;
	else
		cout << getCount(0, S.size() - 1);
	return 0;
}