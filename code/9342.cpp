#include <iostream>
#include <string>

using namespace std;

int N, current;
bool infected;
string s;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> s;

		infected = 1;

		if (s[0] < 'A' || s[0] > 'F') infected = 0;

		current = s[0] == 'A' ? 0 : 1;

		if (s[current] != 'A') infected = 0;
		
		while (current < s.size() && s[current] == 'A') current++;

		if (current >= s.size()) infected = 0;
		else if (s[current] != 'F') infected = 0;

		while (current < s.size() && s[current] == 'F') current++;


		if (current >= s.size()) infected = 0;
		else if (s[current] != 'C') infected = 0;

		while (current < s.size() && s[current] == 'C') current++;

		if (current < s.size() - 1) infected = 0;
		else if (current < s.size())
			if (s[current] < 'A' || s[current] > 'F') infected = 0;

		cout << (infected ? "Infected!\n" : "Good\n");
	}

	return 0;
}