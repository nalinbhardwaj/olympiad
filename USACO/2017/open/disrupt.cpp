#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

const int maxn = int(1e5)+5, inf = int(1e9)+5;

int ans[maxn], A[maxn], st[4*maxn+10], start[maxn], en[maxn];
vector<pair<int, int>> E, dis, extra[maxn];
vector<int> graph[maxn];

inline int left(int node) { return (node<<1); }
inline int right(int node) { return (node<<1)+1; }

void upd(int node, int L, int R, int a, int b)
{
	if(L == R) st[node] = min(st[node], b);
	else
	{
		if(a <= (L+R)/2) upd(left(node), L, (L+R)/2, a, b);
		else upd(right(node), (L+R)/2+1, R, a, b);
		st[node] = min(st[node], b);
	}
}

int qry(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return inf;
	else if(a <= L && R <= b) return st[node];
	else return min(qry(left(node), L, (L+R)/2, a, b), qry(right(node), (L+R)/2+1, R, a, b));
}

void dfs0(int node, int par)
{
	start[node] = int(dis.size());
	dis.push_back({node, 0});
	for(auto it: graph[node])
	{
		if(it != par) dfs0(it, node);
	}
	en[node] = int(dis.size());
	dis.push_back({node, 1});
}

int main(void)
{
	ifstream fin("disrupt.in");
	ofstream fout("disrupt.out");

	int n, m, u, v, r;
	fin >> n >> m;
	for(int i = 1;i < n;i++)
	{
		fin >> u >> v;
		u--, v--;
		graph[u].push_back(v), graph[v].push_back(u);
		E.push_back({u, v});
	}

	for(int i = 0;i < m;i++)
	{
		fin >> u >> v >> r;
		u--, v--;
		extra[u].push_back({v, r});
		extra[v].push_back({u, r});
	}

	dfs0(0, -1);

	for(int i = 0;i < 4*maxn;i++) st[i] = inf;
	for(int i = 0;i <= n;i++) ans[i] = inf;

	//for(auto it: dis) cout << it.first << ":" << it.second << " ";
	//cout << '\n';

	//for(int i = 0;i < n;i++) cout << i << ":" << start[i] << " " << en[i] << "\n";

	for(int i = 0;i < int(dis.size());i++)
	{
		int u = dis[i].first;
		if(dis[i].second) continue;

		ans[u] = min(ans[u], qry(1, 0, maxn-1, start[u], en[u]));

		for(auto it: extra[u])
		{
			if(start[it.first] > start[u])
			{
				upd(1, 0, maxn-1, start[it.first], it.second);
				//cout << u << " " << it.first << " " << start[it.first] << "\n";
			}
		}
	}

	for(int i = 0;i < 4*maxn;i++) st[i] = inf;

	for(int i = int(dis.size())-1;i >= 0;i--)
	{
		int u = dis[i].first;
		if(!dis[i].second) continue;

		ans[u] = min(ans[u], qry(1, 0, maxn-1, start[u], en[u]));

		for(auto it: extra[u])
		{
			if(start[it.first] < start[u])
			{
				upd(1, 0, maxn-1, start[it.first], it.second);
			}
		}
	}

	for(auto it: E)
	{
		int u = it.first, v = it.second;
		if(start[u] > start[v]) swap(u, v);
		if(ans[v] == inf) fout << -1 << "\n";
		else fout << ans[v] << "\n";
	}
}