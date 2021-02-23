#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll N, M, T[100001], low, high, mid, ans, s, mt = 0;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		cin >> T[i];
		mt = max(mt, T[i]);
	}

	high = ans = mt * M; //max waiting time

	while (low <= high)
	{
		mid = (low + high) >> 1;
		s = 0;

		for (int i = 0; i < N; i++)
			s += mid / T[i]; //number of people handled in time

		if (s >= M) //can handle -> time can be less
		{
			high = mid - 1;
			ans = min(ans, mid);
		}
		else low = mid + 1;
	}

	cout << ans;
	return 0;
}