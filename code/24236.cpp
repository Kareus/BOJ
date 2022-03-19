#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int N, R, C, T;

const ll MAX = 1e15;

struct Node
{
	int left, right;
	ll val[3][3]; //- 0 +
};

struct segTree
{
	Node v[1 << 18];

	void init(int* input, int index, int rangeStart, int rangeEnd)
	{
		if (rangeStart == rangeEnd)
		{
			v[index].left = v[index].right = input[rangeStart];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					v[index].val[i][j] = MAX;

			if (input[rangeStart] == 0)
			{
				v[index].val[0][0] = v[index].val[2][2] = C;
				v[index].val[1][1] = 0;
			}
			else
			{
				v[index].val[0][0] = input[rangeStart] < 0 ? 0 : min((input[rangeStart] + 1) * C, R);
				v[index].val[1][1] = abs(input[rangeStart]) * C;
				v[index].val[2][2] = input[rangeStart] > 0 ? 0 : min((-input[rangeStart] + 1) * C, R);
			}
			return;
		}

		int mid = (rangeStart + rangeEnd) >> 1;

		init(input, index << 1, rangeStart, mid);
		init(input, index << 1 | 1, mid + 1, rangeEnd);

		v[index].left = v[index << 1].left;
		v[index].right = v[index << 1 | 1].right;

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				v[index].val[i][j] = MAX;
				for (int k = 0; k < 3; k++)
					v[index].val[i][j] = min(v[index].val[i][j], v[index << 1].val[i][k] + min(v[index << 1 | 1].val[(k + 1) % 3][j], v[index << 1 | 1].val[(k + 2) % 3][j]));
			}

		return;
	}

	void update(int nodeIndex, int rangeStart, int rangeEnd, int index, int val)
	{
		if (index < rangeStart || index > rangeEnd) return;

		if (rangeStart != rangeEnd)
		{
			int mid = (rangeStart + rangeEnd) >> 1;
			update(nodeIndex << 1, rangeStart, mid, index, val);
			update(nodeIndex << 1 | 1, mid + 1, rangeEnd, index, val);

			v[nodeIndex].left = v[nodeIndex << 1].left;
			v[nodeIndex].right = v[nodeIndex << 1 | 1].right;

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					v[nodeIndex].val[i][j] = MAX;
					for (int k = 0; k < 3; k++)
						v[nodeIndex].val[i][j] = min(v[nodeIndex].val[i][j], v[nodeIndex << 1].val[i][k] + min(v[nodeIndex << 1 | 1].val[(k + 1) % 3][j], v[nodeIndex << 1 | 1].val[(k + 2) % 3][j]));
				}
		}
		else
		{
			v[nodeIndex].left = v[nodeIndex].right = val;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					v[nodeIndex].val[i][j] = MAX;

			if (val == 0)
			{
				v[nodeIndex].val[0][0] = v[nodeIndex].val[2][2] = C;
				v[nodeIndex].val[1][1] = 0;
			}
			else
			{
				v[nodeIndex].val[0][0] = val < 0 ? 0 : min((val + 1) * C, R);
				v[nodeIndex].val[1][1] = abs(val) * C;
				v[nodeIndex].val[2][2] = val > 0 ? 0 : min((-val + 1) * C, R);
			}
		}
	}

	ll query()
	{
		ll ret = MAX;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				ret = min(ret, v[1].val[i][j]);
		return ret;
	}
};

segTree tree;
int input[101010], K, V;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> R >> C >> T;
	
	for (int i = 0; i < N; i++) cin >> input[i];
	tree.init(input, 1, 0, N - 1);
	cout << tree.query() << '\n';

	while (T--)
	{
		cin >> K >> V;
		tree.update(1, 0, N - 1, K - 1, V);
		cout << tree.query() << '\n';
	}

	return 0;
}