#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct node
{
    ll m, M, sum, lazy_add, lazy_sqrt;
};

struct segTree_beats
{
    node v[1 << 18];

    void lazy_update(int node, int start, int end)
    {
        if (v[node].lazy_add == 0 && v[node].lazy_sqrt == 0) return;

        if (v[node].lazy_sqrt == 0)
        {
            v[node].sum += v[node].lazy_add * (end - start + 1);
            v[node].M += v[node].lazy_add;
            v[node].m += v[node].lazy_add;

            if (start != end)
            {
                v[node << 1].lazy_add += v[node].lazy_add;
                v[node << 1 | 1].lazy_add += v[node].lazy_add;
            }
        }
        else
        {
            v[node].sum = (v[node].lazy_sqrt + v[node].lazy_add) * (end - start + 1);
            v[node].m = v[node].M = v[node].lazy_sqrt + v[node].lazy_add;

            if (start != end)
            {
                v[node << 1].lazy_add = v[node << 1 | 1].lazy_add = v[node].lazy_add;
                v[node << 1].lazy_sqrt = v[node << 1 | 1].lazy_sqrt = v[node].lazy_sqrt;
            }
        }

        v[node].lazy_add = v[node].lazy_sqrt = 0;
    }

    node init(ll* arr, int node, int start, int end)
    {
        if (start == end) return v[node] = { arr[start], arr[start], arr[start], 0, 0 };

        int mid = (start + end) >> 1;
        init(arr, node << 1, start, mid);
        init(arr, node << 1 | 1, mid + 1, end);

        return v[node] = { min(v[node << 1].m, v[node << 1 | 1].m), max(v[node << 1].M, v[node << 1 |  1].M) , v[node << 1].sum + v[node << 1 | 1].sum, 0, 0};
    }

    void add(int node, int start, int end, int left, int right, ll val)
    {
        lazy_update(node, start, end);

        if (left > end || right < start) return;

        if (left <= start && end <= right)
        {
            v[node].lazy_add += val;
            lazy_update(node, start, end);
            return;
        }

        int mid = (start + end) >> 1;

        add(node << 1, start, mid, left, right, val);
        add(node << 1 | 1, mid + 1, end, left, right, val);

        v[node].m = min(v[node << 1].m, v[node << 1 | 1].m);
        v[node].M = max(v[node << 1].M, v[node << 1 | 1].M);
        v[node].sum = v[node << 1].sum + v[node << 1 | 1].sum;
    }

    void square(int node, int start, int end, int left, int right)
    {
        lazy_update(node, start, end);
        
        if (left > end || right < start) return;
        if (left <= start && end <= right)
        {
            if (floor(sqrt(v[node].m)) == floor(sqrt(v[node].M))) //each results would be all the same
            {
                v[node].lazy_sqrt = floor(sqrt(v[node].m));
                lazy_update(node, start, end);
                return;
            }

            if (v[node].m + 1 == v[node].M) //differernce of sqrt also be 1
            {
                v[node].lazy_add = floor(sqrt(v[node].m)) - v[node].m; //new_val = sqrt(old_val) => new_val = old_val + sqrt(old_val) - old_val
                lazy_update(node, start, end);
                return;
            }
        }

        int mid = (start + end) >> 1;
        square(node << 1, start, mid, left, right);
        square(node << 1 | 1, mid + 1, end, left, right);

        v[node].m = min(v[node << 1].m, v[node << 1 | 1].m);
        v[node].M = max(v[node << 1].M, v[node << 1 | 1].M);
        v[node].sum = v[node << 1].sum + v[node << 1 | 1].sum;
    }

    ll sum(int index, int start, int end, int left, int right)
    {
        lazy_update(index, start, end);

        if (left > end || right < start) return 0;
        if (left <= start && end <= right) return v[index].sum;

        int mid = (start + end) >> 1;
        return sum(index << 1, start, mid, left, right) + sum(index << 1 | 1, mid + 1, end, left, right);
    }
};

int N, M, op, a, b, c, d;
ll arr[100001];
segTree_beats tree;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    tree.init(arr, 1, 0, N - 1);

    cin >> M;

    while (M--)
    {
        cin >> op >> a >> b;
        if (op == 1)
        {
            cin >> c;
            tree.add(1, 0, N - 1, a - 1, b - 1, c);
        }
        else if (op == 2)
            tree.square(1, 0, N - 1, a - 1, b - 1);
        else
            cout << tree.sum(1, 0, N - 1, a - 1, b - 1) << '\n';
    }

    return 0;
}