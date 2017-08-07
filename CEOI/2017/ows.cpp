//One way streets

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <cstdlib>
#include <cassert>
using namespace std;

const int maxn = int(1e5)+5;

int n, m, p, ctr = 0, dfsctr = 1, vis[maxn], dfs_low[maxn], dfs_num[maxn], ans[maxn], comp[maxn], P[maxn], st[maxn], en[maxn];
pair<int, int> E[maxn], cit[maxn], incom[maxn], exi[maxn];
vector<pair<int, int>> graph[maxn];
set<int> tr[maxn];

void dfs0(int node, int par)
{
	vis[node] = 1;
	dfs_low[node] = dfs_num[node] = ctr++;
	for(auto it: graph[node])
	{
		if(!vis[it.first])
		{
			dfs0(it.first, it.second);
			dfs_low[node] = min(dfs_low[node], dfs_low[it.first]);
		}
		else if(par != it.second) dfs_low[node] = min(dfs_low[node], dfs_num[it.first]);
	}
}

void dfs1(int node, int cmp)
{
	vis[node] = 1;
	comp[node] = cmp;
	for(auto it: graph[node])
	{
		if(!vis[it.first] && ans[it.second]) dfs1(it.first, cmp);
	}
}

void dfs2(int node, int par)
{
	st[node] = dfsctr++;
	P[node] = par;
	for(auto it: tr[node])
	{
		if(it != par) dfs2(it, node);
	}
	en[node] = dfsctr++;
}

void dfs3(int node, int par)
{
	vis[node] = 1;
	for(auto it: tr[node])
	{
		if(it != par) dfs3(it, node);
	}

	for(auto it: tr[node])
	{
		if(it != par)
		{
			incom[node].first = min(incom[node].first, incom[it].first);
			incom[node].second = max(incom[node].second, incom[it].second);
			exi[node].first = min(exi[node].first, exi[it].first);
			exi[node].second = max(exi[node].second, exi[it].second);
		}
	}
}

inline bool fits(int x, int y)
{
	return (st[x] <= y && y <= en[x]);
}

void bru()
{
	for(int i = 0;i < m;i++)
	{
		int u = comp[E[i].first], v = comp[E[i].second];
		if(u == v)
		{
			printf("B");
			continue;
		}
		
		if(P[v] == u) swap(u, v);
		bool out = 0, in = 0;
		for(int j = 0;j < p;j++)
		{
			int a = comp[cit[j].first], b = comp[cit[j].second];
			if(fits(u, st[a]) != fits(u, st[b]))
			{
				if(fits(u, st[a])) out = 1;
				else in = 1;
			}
		}
		if(!out && !in)
		{
			printf("B");
			continue;
		}
		if(out)
		{
			if(v == comp[E[i].first]) printf("L");
			else printf("R");
		}
		else if(in)
		{
			if(u == comp[E[i].first]) printf("L");
			else printf("R");
		}
	}
	printf("\n");

	exit(0);
}

int main(void)
{
	int a, b;
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++)
	{
		scanf("%d%d", &a, &b);
		a--, b--;
		graph[a].push_back({b, i});
		graph[b].push_back({a, i});
		E[i] = {a, b};
	}

	scanf("%d", &p);
	for(int i = 0;i < p;i++)
	{
		scanf("%d%d", &a, &b);
		a--, b--;
		cit[i] = {a, b};
	}

	for(int i = 0;i < n;i++)
	{
		if(!vis[i]) dfs0(i, -1);
	}

	for(int i = 0;i < m;i++)
	{
		int u = E[i].first, v = E[i].second;
		if(dfs_num[v] < dfs_num[u]) swap(u, v);
		if(dfs_num[u] >= dfs_low[v])
		{
			ans[i] = 3;
			//cout << "not bridge " << i << "\n";
		}
	}

	for(int i = 0;i < n;i++) vis[i] = 0;

	int cc = 1;

	for(int i = 0;i < n;i++)
	{
		if(!vis[i]) dfs1(i, cc++);
	}

	for(int i = 0;i < m;i++)
	{
		int u = comp[E[i].first], v = comp[E[i].second];
		if(u != v)
		{
			//cout << "tredge " << u << " " << v << "\n";
			tr[u].insert(v), tr[v].insert(u);
		}
	}

	for(int i = 1;i < cc;i++)
	{
		if(!st[i]) dfs2(i, -1);
	}

	//bru();

	for(int i = 1;i < cc;i++)
	{
		incom[i] = {st[i], st[i]};
		exi[i] = {st[i], st[i]};
		//cout << i << ": " << st[i] << " " << en[i] << " " << incom[i].first << " " << incom[i].second << " : " << exi[i].first << " " << exi[i].second << "\n";
		vis[i] = 0;
	}

	for(int i = 0;i < p;i++)
	{
		a = comp[cit[i].first], b = comp[cit[i].second];
		exi[a].first = min(exi[a].first, st[b]);
		exi[a].second = max(exi[a].second, st[b]);
		incom[b].first = min(incom[b].first, st[a]);
		incom[b].second = max(incom[b].second, st[a]);
	}

	for(int i = 1;i < cc;i++)
	{
		if(!vis[i]) dfs3(i, -1);
	}

	for(int i = 0;i < m;i++)
	{
		int u = comp[E[i].first], v = comp[E[i].second];
		if(u == v)
		{
			printf("B");
			continue;
		}
		
		if(P[v] == u) swap(u, v);
		bool out = 0, in = 0;
		if(!fits(u, incom[u].first) || !fits(u, incom[u].second)) in = 1;
		if(!fits(u, exi[u].first) || !fits(u, exi[u].second)) out = 1;
		if(!out && !in)
		{
			printf("B");
			continue;
		}
		if(out)
		{
			if(v == comp[E[i].first]) printf("L");
			else printf("R");
		}
		else if(in)
		{
			if(u == comp[E[i].first]) printf("L");
			else printf("R");
		}
	}
	printf("\n");
}