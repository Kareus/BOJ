#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

struct Trie
{
	Trie* next[26];
	Trie* fail;
	bool finish;

	Trie() : fail(0), finish(0)
	{
		memset(next, 0, sizeof(next));
	}

	~Trie()
	{
		for (int i = 0; i < 26; i++)
			if (next[i]) delete next[i];
	}

	void insert(const char* key)
	{
		if (!*key)
		{
			finish = 1;
			return;
		}

		int cur = *key - 'a';

		if (!next[cur]) next[cur] = new Trie();

		next[cur]->insert(key + 1);
	}	
};

void aho_fail(Trie* root)
{
	queue<Trie*> q;
	root->fail = root;
	q.push(root);

	while (!q.empty())
	{
		Trie* cur = q.front();
		q.pop();

		for (int i = 0; i < 26; i++)
		{
			Trie* child = cur->next[i];
			if (!child) continue;

			if (root == cur) child->fail = root; //first childs must go to root
			else
			{
				Trie* f = cur->fail;
				while (f != root && !f->next[i]) f = f->fail;
				if (f->next[i]) f = f->next[i]; //find suffix from upper nodes
				child->fail = f;
			}

			if (child->fail->finish) child->finish = 1;
			q.push(child);
		}
	}
}

Trie root, *cur;
int N, Q, k;
string S;
bool ans;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> S;
		root.insert(S.c_str());
	}

	aho_fail(&root);

	cin >> Q;

	while (Q--)
	{
		cin >> S;
		ans = 0;

		cur = &root;

		for (char& c : S)
		{
			k = c - 'a';
			while (cur != &root && !cur->next[k]) cur = cur->fail;

			if (cur->next[k]) cur = cur->next[k];

			if (cur->finish)
			{
				ans = 1;
				break;
			}
		}

		cout << (ans ? "YES\n" : "NO\n");
	}
	return 0;
}