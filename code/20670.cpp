#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;

const int MAX = 1e9;
int N, M, K, x, y;
vector<p> A, B, sign;
vector<pair<double, int>> gradA, gradB; //gradient of A, B edges

int ccw(p a, p b, p c)
{
	ll val = a.first * b.second + b.first * c.second + c.first * a.second - a.second * b.first - b.second * c.first - c.second * a.first;
	if (val > 0) return 1;
	else if (val < 0) return -1;
	return 0;
}

void getGradient(vector<p>& hull, vector<pair<double, int>>& grad)
{
	swap(hull[0], *min_element(hull.begin(), hull.end())); //set the min point as hull[0]

	int L = hull.size();
	for (int i = 1; i < L; i++)
	{
		if (hull[i].first == hull[0].first) //same x -> cannot get gradient
			grad.emplace_back(MAX + 1, i);
		else
			grad.emplace_back((double)(hull[i].second - hull[0].second) / (hull[i].first - hull[0].first), i);
	}

	sort(grad.begin(), grad.end());
}

bool isInside(p current, vector<pair<double, int>>& grad, vector<p>& hull)
{
	//we need log N algorithm
	
	if (current.first <= hull[0].first) return 0; //in the opposite side from the polygon (or left side)
	//on the outline if x is same, but sign should not.

	double g = (double)(current.second - hull[0].second) / (current.first - hull[0].first);

	if (g < grad[0].first || g > grad.back().first) return 0; //outside

	int i = lower_bound(grad.begin(), grad.end(), make_pair(g, MAX + 2)) - grad.begin();

	if (grad[i].first == g) //on the line
		return hull[grad[i].second].first >= current.first;

	if (ccw(current, hull[0], hull[grad[i - 1].second]) == -1) return 0;
	if (ccw(current, hull[grad[i - 1].second], hull[grad[i].second]) == -1) return 0;
	if (ccw(current, hull[grad[i].second], hull[0]) == -1) return 0;
	//outside the triangle

	return 1; //inside
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;

	A.resize(N), B.resize(M), sign.resize(K);
	
	for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;
	for (int i = 0; i < M; i++) cin >> B[i].first >> B[i].second; //hull in ccw. no need to graham.
	for (int i = 0; i < K; i++) cin >> sign[i].first >> sign[i].second;

	getGradient(A, gradA);
	getGradient(B, gradB);

	int cnt = 0;

	for (p& i : sign)
		cnt += (!isInside(i, gradA, A) || isInside(i, gradB, B));

	if (cnt == 0) cout << "YES";
	else cout << cnt;
	return 0;
}

/*
point inside a convex hull - O(log N) algorithm
get the min point (most left point in hull) and calculate all gradients from min point to other points in hull.
sort it and you can judge if the point is inside the polygon by those.
let g = gradient of line which from min point to judging point
g < min gradient or g > max gradient -> outside
g = one of gradients -> outside if x value is larger than hull point.
between gradient[i-1] and gradient[i]
-> check if the point is in the triangle of min point, gradient[i-1], gradient[i]. you can get by ccw.
you can get gradient[i] using binary search, O(log N).
*/