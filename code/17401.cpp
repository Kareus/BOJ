#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

struct matrix
{
	int size;
	vector<vector<ll>> m;

	matrix()
	{
		size = 0;
	}

	matrix(int N, ll x = 0)
	{
		init(N, x);
	}

	void init(int N, ll x = 0)
	{
		size = N;
		m.resize(N, vector<ll>(N));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				m[i][j] = (i == j) * x;
	}

	matrix operator* (const matrix& mat)
	{
		matrix r;
		r.init(size);

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				for (int k = 0; k < size; k++)
					r.m[i][j] = (r.m[i][j] + m[i][k] * mat.m[k][j]) % MOD;

		return r;
	}
};

matrix pow_mat(matrix a, ll b)
{
	matrix ret;
	ret.init(a.size, 1);

	while (b)
	{
		if (b % 2) ret = ret * a;
		b >>= 1;
		a = a * a;
	}

	return ret;
}

int T, N, D, M, a, b, c;
vector<matrix> v_mat;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> T >> N >> D;
	v_mat.resize(T, matrix(N));

	for (int i = 0; i < T; i++)
	{
		cin >> M;
		for (int j = 0; j < M; j++)
		{
			cin >> a >> b >> c;
			v_mat[i].m[a - 1][b - 1] = c; //a edge with weight c
		}
	}

	matrix ans(N, 1), mul(N, 1);

	//we can't use pow for this problem
	for (int i = 0; i < T; i++) mul = mul * v_mat[i]; //merge all maps

	ans = ans * pow_mat(mul, D / T); //periods

	int r = D % T;
	for (int i = 0; i < r; i++) ans = ans * v_mat[i]; //each map for remainder

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << ans.m[i][j] << ' ';
		cout << '\n';
	}

	return 0;
}

/*
adjacent matrix and pow for matrix
*/