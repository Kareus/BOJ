#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int M, op, x, b, bit[30];

struct Trie
{
	int cnt, val;

	Trie* next[2];
	Trie() : cnt(0), val(-1)
	{
		memset(next, 0, sizeof(next));
	}

	~Trie()
	{
		for (int i = 0; i < 2; i++)
			if (next[i]) delete next[i];
	}

	void insert(int i)
	{
		cnt++;

		if (i == 30)
		{
			val = x;
			return;
		}

		if (!next[bit[i]])
			next[bit[i]] = new Trie();
		
		next[bit[i]]->insert(i + 1);
	}

	void remove(int i)
	{
		if (--cnt == 0) val = -1;
		if (i == 30) return;

		next[bit[i]]->remove(i + 1);
	}

	int query(int i)
	{
		if (val != -1) return val ^ x;

		int b = bit[i] & 1;
		if (next[b ^ 1] && next[b ^ 1]->cnt)
			return next[b ^ 1]->query(i + 1);
		else
			return next[b]->query(i + 1);
	}
};

Trie root;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> M;

	root.insert(0); //0 is already in

	while (M--)
	{
		cin >> op >> x;

		b = x;
		for (int i = 29; i >= 0; i--, b >>= 1) bit[i] = b & 1; //pre-process

		if (op == 1) root.insert(0);
		else if (op == 2) root.remove(0);
		else cout << root.query(0) << '\n';
	}

	return 0;
}

/*
trie (difficult)
convert number to binary to use in trie.
go to the opposite direction of x as you can, and you get maximum of xor value.
*/