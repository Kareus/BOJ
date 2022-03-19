#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> p;

const int MAX = 1e9 + 5;
int N, ans;
p line[200001];
vector<p> v;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) cin >> line[i].first >> line[i].second;

	sort(line, line + N);

	v.push_back(line[0]);

	for (int i = 1; i < N; i++)
		if (v.back().second >= line[i].first)
			v.back().second = max(v.back().second, line[i].second);
		else
			v.push_back(line[i]);

	N = v.size();

	for (int i = 0; i < N && i <= ans; i++)
	{
		p P = { v[i].second * 2 - v[i].first, MAX };
		auto it = upper_bound(v.begin(), v.end(), P);
		it--;
		ans = max(ans, (int)(it - v.begin()));
	}

	cout << v[ans].second;
	return 0;
}