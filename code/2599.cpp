#include <iostream>

using namespace std;

int N, A1, A2, B1, B2, C1, C2;
int AB, AC, BA, BC, CA, CB;
bool ok = 0;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> A1 >> A2 >> B1 >> B2 >> C1 >> C2;

	if (A1 > B2 + C2 || B1 > A2 + C2 || C1 > A2 + B2) cout << 0;
	else
	{
		for (AB = 0; AB <= A1; AB++)
		{
			BA = A1 + B1 - C2 - AB;
			CA = A2 - BA;
			AC = A1 - AB;
			BC = B1 - BA;
			CB = C1 - CA;

			if (BA >= 0 && CA >= 0 && AC >= 0 && BC >= 0 && CB >= 0)
			{
				ok = 1;
				break;
			}
		}

		cout << ok << '\n';

		if (ok) cout << AB << ' ' << AC << '\n' << BA << ' ' << BC << '\n' << CA << ' ' << CB;
	}
	return 0;
}

/* note for equation
input:
A1 A2
B1 B2
C1 C2

output:
AB AC(= A1-AB)
BA BC(= B1-BA)
CA CB(= C1-CA)

A1+B1+C1 = A2+B2+C2 = N

AC + BC = A1 - AB + B1 - BA = C2
AB + CB = AB + C1 - CA = B2
BA + CA = A2

A1 + B1 - C2 = AB + BA
C1 - B2 = CA - AB
BA + CA = A2

* BA = A1 + B1 - C2 - AB
* CA = AB + C1 - B2 = A2 - BA
*/