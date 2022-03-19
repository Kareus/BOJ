#include <iostream>
#include <string>

using namespace std;

string str;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	getline(cin, str);

	const char* p = str.c_str();
	while (*p)
	{
		cout << *p;

		if (*p == 'a' || *p == 'e' || *p == 'i' || *p == 'o' || *p == 'u') p += 2;
		p++;
	}
	return 0;
}