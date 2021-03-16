#include <iostream>
#include <string>

using namespace std;

int T;
bool y;
string s;
const char *p;

bool judge1()
{
	if (*p++ != '1') return 0;
	if (*p++ != '0') return 0;
	if (*p++ != '0') return 0;
	while (*p == '0') p++;

	if (*p++ != '1') return 0;

	while (*p == '1')
	{
		const char* temp = p;
		if (!judge1()) p = temp + 1;
	}
	return 1;
}

bool judge2()
{
	if (*p++ != '0') return 0;
	if (*p++ != '1') return 0;
	return 1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> T;

	while (T--)
	{
		cin >> s;
		p = s.c_str();

		y = 1;
		while (*p)
			if (!(*p == '1' ? judge1() : judge2()))
			{
				y = 0;
				break;
			}

		cout << (y ? "YES\n" : "NO\n");
	}

	return 0;
}