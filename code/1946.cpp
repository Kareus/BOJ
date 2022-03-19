#include <iostream>
#include <algorithm>

using namespace std;

int T, N, ans, thres;
pair<int, int> r[100001];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> T;
	while (T--)
	{
		cin >> N;
		ans = 0;

		for (int i = 0; i < N; i++) cin >> r[i].first >> r[i].second;

		sort(r, r + N);
		thres = r[0].second; //rank B should be smaller than at least threshold

		for (int i = 0; i < N; i++)
			if (r[i].second <= thres)
			{
				ans++;
				thres = r[i].second; //now rank should be smaller!
			}

		cout << ans << '\n';
	}
	return 0;
}