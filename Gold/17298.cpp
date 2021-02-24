#include <iostream>
#include <algorithm>
#include <stack>
#include <string.h>

using namespace std;

int N, arr[1000001], o[1000001];
stack<int> s;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		o[i] = -1;
		cin >> arr[i];

		while (!s.empty() && arr[s.top()] < arr[i])
		{
			o[s.top()] = arr[i];
			s.pop();
		}

		s.push(i);
	}

	for (int i = 0; i < N; i++) cout << o[i] << ' ';

	return 0;
}