#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

string S;
pair<int, char> sum[27];
char x;
int b, id, ans, N;
stack<char> digit;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (x = 'A'; x <= 'Z'; x++) sum[x - 'A'].second = x;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> S;

		for (char& c : S) digit.push(c);

		b = 1;

		while (digit.size())
		{
			x = digit.top();
			digit.pop();

			sum[x - 'A'].first += b;
			b *= 10;
		}
	}

	sort(sum, sum + 27);

	id = 9;
	for (int i = 26; i >= 0 && sum[i].first; i--)
		ans += sum[i].first * id--;

	cout << ans;
	return 0;
}