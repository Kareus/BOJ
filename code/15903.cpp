#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

ll N, M, x, y, ans;
priority_queue<ll, vector<ll>, greater<ll>> pq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	while (N--)
	{
		cin >> x;
		pq.push(x);
	}

	while (M--)
	{
		x = pq.top();
		pq.pop();
		y = pq.top();
		pq.pop();

		pq.push(x + y);
		pq.push(x + y);
	}

	while (pq.size())
	{
		ans += pq.top();
		pq.pop();
	}

	cout << ans;
	return 0;
}
