#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

typedef pair<double, double> p;

p pivot;

double ccwd(p a, p b, p c)
{
	double val = a.first * b.second + b.first * c.second + c.first * a.second - a.second * b.first - b.second * c.first - c.second * a.first;
	return val;
}

bool cmp(p& A, p& B)
{
	if (A.first == B.first)
		return A.second < B.second;
	else
		return A.first < B.first;
}

bool compare(p& A, p& B)
{
	double c = ccwd(pivot, A, B);
	if (c == 0) return cmp(A, B);

	return c > 0;
}

void graham(vector<p>& v, vector<p>& hull)
{
	sort(v.begin(), v.end(), cmp);
	pivot = v[0];
	sort(v.begin() + 1, v.end(), compare);

	for (auto& i : v)
	{
		while (hull.size() >= 2 && ccwd(hull[hull.size() - 2], hull[hull.size() - 1], i) <= 0)
			hull.pop_back();

		hull.push_back(i);
	}
}

double getArea(vector<p>& hull, double x)
{
	double ret = 0;
	int S = hull.size();
	p pt, pt2;
	bool ch1 = 0;

	for (int i = 1; i < S; i++)
	{
		if (hull[i].first > x)
		{
			if (!ch1)
			{
				double grad = hull[i].second - hull[i - 1].second;
				grad /= hull[i].first - hull[i - 1].first;
				pt.first = x;
				pt.second = hull[i - 1].second + grad * (x - hull[i - 1].first);

				ret += ccwd(pivot, hull[i - 1], pt);
				ch1 = 1;
			}
			continue;
		}

		if (ch1)
		{
			double grad = hull[i].second - hull[i - 1].second;
			grad /= hull[i].first - hull[i - 1].first;
			pt2.first = x;
			pt2.second = hull[i - 1].second + grad * (x - hull[i - 1].first);

			ret += ccwd(pivot, pt, pt2) + ccwd(pivot, pt2, hull[i]);
			ch1 = 0;
			continue;
		}
		ret += ccwd(pivot, hull[i - 1], hull[i]);
	}

	if (ch1)
	{
		double grad = hull[0].second - hull[S - 1].second;
		grad /= hull[0].first - hull[S - 1].first;
		pt2.first = x;
		pt2.second = hull[S - 1].second + grad * (x - hull[S - 1].first);
		double val = ccwd(pivot, pt, pt2);
		ret += val;
	}

	return ret;
}

int L = 2e9, R = -2e9;
double binary(vector<p>& hull)
{
	pivot = hull[0];

	double mid = 0;
	int S = hull.size();

	double area = 0, temp = 0;
	for (int i = 1; i < S; i++)
	{
		double val = ccwd(pivot, hull[i - 1], hull[i]);
		area += val;
	}

	area = area * 0.5;

	while (L + 1 < R)
	{
		mid = (L + R) / 2;
		temp = getArea(hull, mid);

		if (temp > area) R = mid;
		else if (temp < area) L = mid;
		else break;
	}

	double LL = L, RR = R;
	for (int i = 0; i < 16; i++)
	{
		mid = (LL + RR) / 2;
		temp = getArea(hull, mid);

		if (temp > area) RR = mid;
		else if (temp < area) LL = mid;
	}

	return (LL + RR) * 0.5;
}

int N, x, y;
vector<p> v, hull;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cout << fixed << setprecision(6);
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> x >> y;
		v.emplace_back(x, y);
		L = min(L, x);
		R = max(R, x);
	}

	graham(v, hull);

	cout << binary(hull);
	return 0;
}