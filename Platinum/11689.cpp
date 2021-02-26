//have to use euler-pi function

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

ll N, sN, ans;
vector<ll> prime;
bool np[1000001];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	sN = sqrt(N) + 1;

	for (ll i = 2; i <= sN; i++)
	{
		if (np[i]) continue;
		prime.push_back(i);

		for (ll j = i << 1; j <= sN; j += i) np[i] = 1;
	} //get primes

	ans = N;
	for (ll& p : prime)
	{
		if (p * p > N) break;

		if (N % p == 0) ans = ans / p * (p - 1);

		while (N % p == 0) N /= p; //to check N is prime later
	}

	if (N != 1) //there is prime more than sqrt(N) -> N
		ans = ans / N * (N - 1);

	cout << ans;
	return 0;
}