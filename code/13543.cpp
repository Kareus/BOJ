#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

struct splay_node
{
	splay_node* left, * right, * parent;
	ull key, sum[11];
	int size;
	bool flip;
	bool dummy; //for kth range exception

	splay_node(ull key = 0);

	void count();
	void push();
	bool isRight();
};

ull C[11][11];
const ull MOD = 1LL << 32;

void init()
{
	C[0][0] = 1;
	for (int i = 1; i <= 10; i++)
	{
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
}

splay_node::splay_node(ull key)
{
	left = right = parent = NULL;
	this->key = key;
	size = 1;
	flip = dummy = 0;
	for (int i = 0; i <= 10; i++)
		sum[i] = key;
}

void splay_node::count() //update value
{
	size = 1;

	if (left) size += left->size;
	if (right) size += right->size;

	ull sz = left ? left->size : 0;
	ull co[11];

	co[0] = 1;
	for (int i = 1; i <= 10; i++)
		co[i] = co[i - 1] * (sz + 1) % MOD;

	for (int i = 0; i <= 10; i++)
	{
		sum[i] = (co[i] * key) % MOD;
		if (left) sum[i] = (sum[i] + left->sum[i]) % MOD;
		if (right)
			for (int j = 0; j <= i; j++)
			{
				ull r = (right->sum[j] * co[i - j]) % MOD;
				r = (r * C[i][j]) % MOD;
				sum[i] = (sum[i] + r) % MOD;
			}
	}

}

void splay_node::push() //lazy propagation
{
	if (!flip) return;

	swap(left, right);
	if (left) left->flip = !left->flip;
	if (right) right->flip = !right->flip;
	flip = 0;
}

bool splay_node::isRight()
{
	return this == parent->right;
}

struct splayTree
{
	splay_node* root;

	void init(int N, ull* arr)
	{
		root = new splay_node();
		root->dummy = 1; //dummy 1

		splay_node* p = root;
		for (int i = 0; i < N; i++)
		{
			p->right = new splay_node(arr[i]);
			p->right->parent = p;
			p = p->right;
		}

		p->right = new splay_node();
		p->right->parent = p;
		p = p->right;
		p->dummy = 1; //dummy 2

		while (p) //update
		{
			p->count();
			p = p->parent;
		}
	}

	void rotate(splay_node* i) //move i to its parent
	{
		splay_node* p = i->parent;
		splay_node* b;

		if (!p) return; //no parent (root)

		p->push();
		i->push();

		bool R = i->isRight();

		(R ? p->right : p->left) = b = (R ? i->left : i->right);
		(R ? i->left : i->right) = p;

		splay_node* pp = p->parent;
		i->parent = pp;
		p->parent = i;

		if (b) b->parent = p;

		if (i->parent)
		{
			if (pp->left == p) pp->left = i;
			else if (pp->right == p) pp->right = i;
		}
		else root = i;

		p->count();
		i->count();
	}

	void splay(splay_node* i)
	{
		while (i->parent)
		{
			splay_node* p = i->parent;
			splay_node* g = p->parent;
			if (g) rotate(i->isRight() == p->isRight() ? p : i);
			rotate(i);
		}
	}

	void insert(ull key)
	{
		splay_node* p = root;
		splay_node** place;
		if (!p)
		{
			root = new splay_node(key);
			root->count();
			return;
		}

		while (1)
		{
			if (key == p->key) return;
			if (key < p->key)
			{
				if (!p->left)
				{
					place = &p->left;
					break;
				}
				p = p->left;
			}
			else
			{
				if (!p->right)
				{
					place = &p->right;
					break;
				}

				p = p->right;
			}
		}

		splay_node* node = new splay_node(key);
		node->parent = p;
		*place = node;

		splay(node);
	}

	bool find(ull key)
	{
		splay_node* p = root;
		if (!p) return 0;

		while (p)
		{
			if (key == p->key) break;
			if (key < p->key)
			{
				if (!p->left) break;
				else p = p->left;
			}
			else if (key > p->key)
			{
				if (!p->right) break;
				else p = p->right;
			}
		}

		splay(p); //move to root
		return key == p->key;
	}

	void remove(ull key)
	{
		if (!find(key)) return;

		splay_node* p = root; //find moved the node to root
		if (p) p->push();
		if (p->right) p->right->push();

		if (p->left && p->right) //two child
		{
			root = p->left; //move left subtree to root
			root->parent = NULL;

			splay_node* i = root;
			while (i->right) i = i->right;

			i->push();
			splay(i);

			i->right = p->right;
			p->right->parent = i; //move right subtree to root's right
			i->count();
			root = i;

			delete p;
			return;
		}

		if (p->left) //only left
		{
			root = p->left;
			root->parent = NULL;

			delete p;
			return;
		}

		if (p->right) //only right
		{
			root = p->right;
			root->parent = NULL;

			delete p;
			return;
		}

		//only root
		delete p;
		root = NULL;
	}

	void kth(int k) //find k-th element and move to root (k is 0-based)
	{
		splay_node* i = root;

		while (1)
		{
			i->push();

			while (i->left && i->left->size > k)
			{
				i = i->left;
				i->push();
			}

			if (i->left) k -= i->left->size;
			if (!k--) break;

			i = i->right;
		}

		splay(i);
	}

	void gather(int S, int E) //gather [S, E] to root->right->left
	{
		kth(S - 1);

		splay_node* i = root;
		root = i->right;
		root->parent = NULL;

		kth(E - S + 1);
		i->right = root;
		root->parent = i;
		root = i;

		i->count();
	}

	void flip(int S, int E) //flip [S, E]
	{
		gather(S, E);
		splay_node* i = root->right->left
		i->flip = !i->flip;
		i->push();
	}
};

int N, M;
ull arr[100001], a, b, c, d;
splayTree tree;

void insert_before(int idx, ull val)
{
	tree.kth(idx);
	splay_node* i = tree.root->right;
	while (i->left) i = i->left;

	i->left = new splay_node(val);
	i->left->parent = i;
	tree.splay(i);
}

void remove_kth(int k)
{
	tree.kth(k);
	tree.remove(tree.root->key);
}

void update(int idx, ull val)
{
	tree.kth(idx);
	tree.root->key = val;
	tree.root->count();
}

ull sum(int L, int R, int k)
{
	tree.gather(L, R);

	return tree.root->right->left->sum[k];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	init();

	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> arr[i];

	tree.init(N, arr);

	cin >> M;

	while (M--)
	{
		cin >> a >> b;
		if (a == 1)
		{
			cin >> c;
			insert_before(b, c);
		}
		else if (a == 2)
			remove_kth(b + 1);
		else if (a == 3)
		{
			cin >> c;
			update(b + 1, c);
		}
		else
		{
			cin >> c >> d;
			cout << sum(b + 1, c + 1, d) << '\n';
		}
	}

	return 0;
}