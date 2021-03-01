#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <string>

#define MAX 100001
using namespace std;

int N, M, s, e, r1, r2, d[MAX], d2[MAX], p[MAX];
long long hash1 = 31, hash2 = 73;
vector<int> graph[MAX], t1[MAX], t2[MAX], one, path1, path2;
queue<int> q;

void bfs(int from, int* distance)
{
	q.push(from);
	distance[from] = 0;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		for (int& i : graph[current])
			if (distance[i] > distance[current] + 1) //find shortest path from start
			{
				distance[i] = distance[current] + 1; //distance update
				p[i] = current; //set as parent
				q.push(i);
			}
	}
}

long long isomorphic(int root, int parent) //for tree 1
{
	vector<long long> subtree;
	for (int& i : t1[root])
		if (i != parent) subtree.push_back(hash1 * isomorphic(i, root) ^ hash1); //we will use hashing for generating ID from integer sequence

	if (subtree.empty()) return root;

	sort(subtree.begin(), subtree.end());
	long long val = 0, co = hash2;

	for (long long& i : subtree)
	{
		val += co * i;
		co *= hash2;
	}

	return val;
}

long long isomorphic2(int root, int parent) //for tree 2
{
	vector<long long> subtree;
	for (int& i : t2[root])
		if (i != parent) subtree.push_back(hash1 * isomorphic2(i, root) ^ hash1);

	if (subtree.empty()) return root;

	sort(subtree.begin(), subtree.end());
	long long val = 0, co = hash2;

	for (long long& i : subtree)
	{
		val += co * i;
		co *= hash2;
	}

	return val;
}

int main()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &s, &e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}

	//we will pick up nodes with 1 or 3+ degree as roots (degree 2 can be leaf nodes)

	//non-3+ degree case
	if (N == M) //possible case: straight line or entire cycle
	{
		bool cycle = true;

		for (int i = 1; i <= N; i++)
			if (graph[i].size() != 2)
			{
				cycle = false;
				break;
			}

		if (cycle) //degree is only 2 => entire cycle
		{
			printf(N % 2 ? "NO" : "YES");
			return 0;
		}
		//straight line would work with root method
	}

	//root method
	//find two roots: root can be degree 1, otherwise all the degree 3+ nodes can be chosen as a root
	for (int i = 1; i <= N; i++)
		if (graph[i].size() == 1) one.push_back(i);

	if (one.size() == 1 || one.size() > 2) //cannot be symmetric
	{
		printf("NO");
		return 0;
	}
	else if (one.size() == 2) //degree 1 case (non-3+ degree case)
		r1 = one[0], r2 = one[1]; //should be roots.
	else
	{
		//there must be 3+ degree nodes (3+ degree case)
		//should find (pick) root nodes. ## leaf nodes cannot be roots, but roots can be 2 degrees. so we don't know what is leaf node, but know what is nonleaf node
		//start from nonleaf node, and find leaf node. then we can pick 2 adjacent nodes from leaf node (those are all of them though), to be root nodes.

		int nonleaf = -1;
		for (int i = 1; i <= N; i++)
			if (graph[i].size() > 2)
			{
				nonleaf = i;
				break;
			}

		//find two distinct cycle from nonleaf node
		int v1 = graph[nonleaf][0], v2 = graph[nonleaf][1];

		graph[nonleaf].erase(graph[nonleaf].begin());
		graph[nonleaf].erase(graph[nonleaf].begin());
		graph[v1].erase(find(graph[v1].begin(), graph[v1].end(), nonleaf));
		graph[v2].erase(find(graph[v2].begin(), graph[v2].end(), nonleaf)); //disconnect first two nodes from nonleaf node

		memset(d, 0x3f, sizeof(d)); //set all the distance to be INF
		bfs(nonleaf, d); //bfs for setting distance and parent from nonleaf node

		int n1 = v1, n2 = v2;
		while (n1 != nonleaf) //find paths to nonleaf (n1 will end as nonleaf if there is a cycle between v1 and nonleaf
		{
			path1.push_back(n1);
			n1 = p[n1]; //get to parent node

			if (n1 == 0) //if n1 is 0, there cannot be cycle because n1 is not connected to nonleaf (and this becomes infinite loop)
			{
				printf("NO");
				return 0;
			}
		}

		while (n2 != nonleaf) //same procedure for v2 cycle
		{
			path2.push_back(n2);
			n2 = p[n2];

			if (n2 == 0)
			{
				printf("NO");
				return 0;
			}
		}

		graph[nonleaf].push_back(v1);
		graph[nonleaf].push_back(v2);
		graph[v1].push_back(nonleaf);
		graph[v2].push_back(nonleaf); //restore edges

		//there would be common path, and all we need is nodes from two both ends.
		reverse(path1.begin(), path1.end());
		reverse(path2.begin(), path2.end()); //reverse two paths so that we can start from nonleaf side

		int common = -1, ps1 = path1.size(), ps2 = path2.size();

		for (int i = 0; i < ps1 && i < ps2; i++)
			if (path1[i] == path2[i])
				common = i;

		//there should be midpoint, as it becomes leaf node. so number of the common path + 1 (nonleaf) should be odd number
		if (common < 0 || common % 2 == 0) //no common path, or there is not midpoint (cannot find leaf node)
		{
			printf("NO");
			return 0;
		}

		int leaf = path1[common >> 1]; //leaf node number

		if (graph[leaf].size() != 2) //degree of leaf node should be 2
		{
			printf("NO");
			return 0;
		}

		//nonleaf and end node of common path can be root nodes
		r1 = nonleaf, r2 = path1[common];
	}

	//now we know the root nodes, so we have to check the trees are mirror-symmetric.
	memset(d, 0x3f, sizeof(d));
	memset(d2, 0x3f, sizeof(d2));
	bfs(r1, d);
	bfs(r2, d2); //have to judge whether root the node belongs, run bfs with two roots

	//create two trees

	int n1 = 0, n2 = 0, e1 = 0, e2 = 0; //number of nodes/edges
	for (int i = 1; i <= N; i++)
		for (int& j : graph[i])
		{
			if (i > j) continue; //to prevent judging twice (i-j, j-i)
			int dist1 = d[i] + d[j], dist2 = d2[i] + d2[j]; //2 * distance from i-j edge to each roots\

			if (dist1 == dist2) //cannot happen in mirror-symmetric (only leaf 'nodes' can have same distance)
			{
				printf("NO");
				return 0;
			}
			else if (dist1 < dist2) //near to root1
			{
				t1[i].push_back(j);
				t1[j].push_back(i);
				e1++;
			}
			else
			{
				t2[i].push_back(j);
				t2[j].push_back(i);
				e2++;
			}
		}

	for (int i = 1; i <= N; i++)
	{
		if (t1[i].size() > 0) n1++;
		if (t2[i].size() > 0) n2++;
	}

	if (n1 - 1 != e1 || n2 - 1 != e2) //not trees
	{
		printf("NO");
		return 0;
	}


	//after we make up two trees, use isomorphism method to check those have same composition
	printf(isomorphic(r1, -1) == isomorphic2(r2, -1) ? "YES" : "NO");
	return 0;
}

/*
I used scanf/printf for getting TLE when I used cin/cout. but now I think I wouldn't.
got hashing idea from https://koosaga.com/84
Thanks, koosaga!
*/