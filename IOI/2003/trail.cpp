// Trail Maintenance

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 205;

int n, P[maxn];
vector<pair<int, pair<int, int>>> edges;

inline int root(int node)
{
	if(P[node] == node) return node;
	else return (P[node] = root(P[node]));
}

void solve()
{
	sort(edges.begin(), edges.end());
	vector<pair<int, pair<int, int>>> nex;
	int res = 0, comp = 0;

	for(int i = 0;i < n;i++) P[i] = i;

	for(auto it: edges)
	{
		if(root(it.second.first) != root(it.second.second))
		{
			res += it.first;
			P[root(it.second.second)] = root(it.second.first);
			nex.push_back(it);
		}
	}

	for(int i = 0;i < n;i++)
	{
		comp += (root(i) == i);
	}
	if(comp > 1) printf("-1\n");
	else printf("%d\n", res);
	fflush(stdout);

	edges = nex;
}

int main(void)
{
	int w, u, v, c;
	scanf("%d%d", &n, &w);
	for(int i = 0;i < w;i++)
	{
		scanf("%d%d%d", &u, &v, &c);
		u--, v--;
		edges.push_back({c, {u, v}});
		solve();
	}
}