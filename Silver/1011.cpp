#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int T, x, y, n;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> T;

	while (T--)
	{
		cin >> x >> y;
		n = sqrt(y - x);
		if (n * n == y - x) cout << 2 * n - 1 << '\n';
		else cout << 2 * n + (2 * n * n + 2 * n + 1 < 2 * (y - x)) << '\n';
	}

	return 0;
}

/*
example
1 1 = 1
2 2 = 1 + 1
3 3 = 1 + 1 + 1
4 3 = 1 + 2 + 1
5 4 = 1 + 1 + 2 + 1
6 4 = 1 + 2 + 2 + 1
7 5 = 1 + 2 + 2 + 1+ 1
8 5 = 1 + 2 + 2 + 2 + 1
9 5 = 1 + 2 + 3 + 2 + 1
10 6 = 1 + 2 + 2 + 2 + 2 + 1
11 6 = 1 + 2 + 2 + 3 + 2 + 1

1 2 3      2 1
k(k+1)/2 + (k-1)+k/2
 = (k^2 + k + k^2 - k) / 2
  = k^2
-> maximum value of n, which can be represented as sum of 2k-1 terms is k^2

if n = k^2 : ans = 2k-1 = 2sqrt(n)-1
else k^2 < n < (k+1)^2인 n이 k^2에 가까운 경우: ans = 2k (2k-1 + 1)
	  k^2 < n < (k+1)^2인 n이 (k+1)^2에 가까운 경우: ans = 2k+1 (2(k+1)-1)
	  case 2 = (k+1)^2 - n < n - k^2 =  2k^2 + 2k+1 < 2n
   => ans = 2k + (2k^2 + 2k + 1 < 2n)

n = y - x, k = sqrt(n) in above code.
*/