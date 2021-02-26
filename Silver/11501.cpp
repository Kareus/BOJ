#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, s;
vector<int> v;
long long ans;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;

	while (T--)
	{
		cin >> N;
		ans = 0;
		v.clear();

		for (int i = 0; i < N; i++)
		{
			cin >> s;
			v.push_back(s);
		}

		reverse(v.begin(), v.end());

		s = 0;

		for (int& i : v)
			if (s < i) s = i;
			else ans += s - i;

		cout << ans << '\n';
	}

	return 0;
}
