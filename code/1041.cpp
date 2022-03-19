#include <iostream>
#include <algorithm>

using namespace std;

long long N, A, B, C, D, E, F, ans, one, two, three;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> A >> B >> C >> D >> E >> F;

	if (N == 1)
		cout << (A + B + C + D + E + F - max({ A,B,C,D,E,F }));
	else
	{
		one = min({ A,B,C,D,E,F });
		two = min({ A + B,A + C,A + D,A + E,B + C,B + D,B + F,C + E,C + F,D + E,D + F,E + F });
		three = min({ A + B + C,A + B + D,A + C + E,A + D + E,B + C + F,B + D + F,C + E + F,D + E + F });

		if (N == 2)
			ans = 4 * (two + three);
		else
		{
			ans = 4 * three;
			ans += (8 * N - 12) * two;
			ans += (5 * (N * N - 4 * N + 4) + 4 * N - 8) * one;
		}

		cout << ans;
	}
	return 0;
}


/*
I just brute-forced...
n = 1 : one 5
n = 2 : four 3, four 2
n >= 3 : four 3, 4*(n-2) 2, four 2, 4*(n-2) 2, 4*(n-2) 1, 5*(n-2)^2 1
        -> 3 : 4, 2 : 8(n-2)+4, 1 : 5(n-2)^2 + 4(n-2)
*/