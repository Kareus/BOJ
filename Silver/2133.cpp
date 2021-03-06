#include <iostream>
#include <algorithm>

using namespace std;

int N, d[31];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	if (N % 2) cout << 0;
	else
	{
		d[0] = 1; //for range-end
		d[2] = 3;

		for (int i = 4; i <= N; i += 2)
		{
			d[i] = 3 * d[i - 2]; //first case

			for (int j = 4; j <= i; j += 2)
				d[i] += 2 * d[i - j]; //to end
		}

		cout << d[N];
	}
	return 0;
}

/*
I hate this.
*/