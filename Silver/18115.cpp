#include <iostream>
#include <deque>

using namespace std;

int N, A[1000001], top = 0;
deque<int> a;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) cin >> A[i];

	for (int i = N; i >= 1; i--)
	{
		if (A[i] == 1)
		{
			if (top) a.push_front(top);
			top = N - i + 1;
		}
		else if (A[i] == 2)
			a.push_front(N - i + 1);
		else if (A[i] == 3)
			a.push_back(N - i + 1);
	}

	if (top) cout << top << ' ';

	while (a.size())
	{
		cout << a.front() << ' ';
		a.pop_front();
	}

	return 0;
}