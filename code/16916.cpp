#include <iostream>
#include <string>

using namespace std;

string S, P;
int L1, L2, pi[1000001], j = 0; //pi: length of substring which prefix == suffix

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> S >> P;
	L1 = S.size(), L2 = P.size();

	for (int i = 1; i < L2; i++)
	{
		while (j && P[i] != P[j])
			j = pi[j - 1]; //find the length from substring 0 ~ j - 1

		if (P[i] == P[j])
			pi[i] = ++j;
	}

	//kmp
	j = 0;
	for (int i = 0; i < L1; i++)
	{
		while (j && S[i] != P[j])
			j = pi[j - 1];

		if (S[i] == P[j])
			if (++j >= L2) break;
	}

	cout << (j >= L2);
	return 0;
}