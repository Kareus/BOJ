#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int N, A, x, y, S;
double C, ans = 0, r;
pair<double, int> arr[100001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cout << fixed;
	cout.precision(6);

	cin >> N >> A;

	for (int i = 0; i < N; i++)
	{
		cin >> x >> y >> arr[i].second;
		arr[i].first = sqrt(x * x + y * y);
	}

	sort(arr, arr + N);

	arr[N].first = 10000;
	arr[N].second = 0; //dummy

	for (int i = 0; i < N; i++)
	{
		S += arr[i].second;
		C += arr[i].first * arr[i].second;

		r = S / (2.0 * A);

		if (arr[i].first <= r && r <= arr[i+1].first) ans = max(ans, r * S - C - A * r * r); //middle

		r = arr[i].first;
		ans = max(ans, r * S - C - A * r * r); //left

		if (i == N - 1) continue; //dummy not allowed here!

		r = arr[i + 1].first;
		ans = max(ans, r * S - C - A * r * r); //right
	}

	cout << ans;
	return 0;
}

/*
* distance from zero : d[i]
c = r - d[i]

(r - d[i]) * w[i]
= r * w[i] - d[i]w[i]

d[i]w[i] is determined
Let C = sum of d[i]w[i]
S = sum of w[i]

earning E = rS - C - Ar^2
          = -Ar^2 + Sr - C
		  = -(Ar^2 - Sr + C)
		  = -(A(r-S/(2A))^2 + C - S^2/(4A))
		  = -A(r-S/(2A))^2 +S^2/(4A) - C

max E = S^2/(4A) - C
but, if S^2/(4A) - C < 0 then 0
also E becomes max when r = S/(2A), so you should check S/(2A) is in left/middle/right of [d[i], d[i+1]]
if r is not in the area, set r as d[i], d[i+1] and calculate.
*/