#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1999;
int N, A[1000001], B[1000001], m = 0, M = 1 << 30;
int bitA[31], bitB[31], ans1, x;
int minA[31][2], minB[31][2], maxA[31][2], maxB[31][2], ans2, y;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 2; j++)
		{
			minA[i][j] = minB[i][j] = M;
			maxA[i][j] = maxB[i][j] = m;
		}

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> A[i];

		x = A[i];
		for (int j = 0; j < 30; j++, x >>= 1) if (x & 1) bitA[j]++;
	}

	for (int i = 0; i < N; i++)
	{
		cin >> B[i];

		x = B[i];
		for (int j = 0; j < 30; j++, x >>= 1) if (x & 1) bitB[j] = (bitB[j] + bitA[j]) % MOD;
	}

	int mask = 1;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int firstA = 0, firstB = 0;
			if (A[j] & (1 << i)) firstA = 1;
			if (B[j] & (1 << i)) firstB = 1;

			minA[i][firstA] = min(minA[i][firstA], A[j] & mask);
			maxA[i][firstA] = max(maxA[i][firstA], A[j] & mask);
			minB[i][firstB] = min(minB[i][firstB], B[j] & mask);
			maxB[i][firstB] = max(maxB[i][firstB], B[j] & mask);
		}
		mask = (mask << 1) | 1;
	}

	for (int i = 0; i <= 28; i++)
	{
		ans1 += ((1 << i) % MOD * bitB[i]) % MOD;
		ans1 %= MOD;
	}

	ans2 = (1 << 30) - 1;
	mask = 1;

	for (int i = 0; i < 30; i++, mask <<= 1)
	{
		if (minA[i][0] != M && minB[i][0] != M && ((minA[i][0] + minB[i][0]) & mask) == 0)
			ans2 &= ~mask;
		if (minA[i][1] != M && minB[i][1] != M && ((minA[i][1] + minB[i][1]) & mask) == 0)
			ans2 &= ~mask;
		if (maxA[i][1] != m && maxB[i][0] != m && ((maxA[i][1] + maxB[i][0]) & mask) == 0)
			ans2 &= ~mask;
		if (maxA[i][0] != m && maxB[i][1] != m && ((maxA[i][0] + maxB[i][1]) & mask) == 0)
			ans2 &= ~mask;
	}
	
	cout << ans1 << ' ' << ans2;
	return 0;
}