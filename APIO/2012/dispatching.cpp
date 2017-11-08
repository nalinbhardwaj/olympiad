#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e5)+5;

lli m, C[maxn], L[maxn], ans[maxn], strt[maxn], en[maxn], sz[maxn];
map<lli, lli> rev;
vector<lli> graph[maxn], dis;
pair<lli, lli> st[4*maxn];

inline lli left(lli node) { return (node<<1); }
inline lli right(lli node) { return (node<<1)+1; }

void upd(lli node, lli L, lli R, lli idx, lli a)
{
	st[node].first += a;
	if(a < 0) st[node].second--;
	else st[node].second++;
	if(L == R) return;
	else
	{
		if(idx <= (L+R)/2) upd(left(node), L, (L+R)/2, idx, a);
		else upd(right(node), (L+R)/2+1, R, idx, a);
	}
}

lli qry(lli node, lli L, lli R, lli v)
{
	if(L == R) return ((st[node].first <= v)?st[node].second:0);
	else
	{
		if(st[left(node)].first > v) return qry(left(node), L, (L+R)/2, v);
		else return qry(right(node), (L+R)/2+1, R, v-st[left(node)].first)+st[left(node)].second;
	}
}

void dfs0(lli node, lli par)
{
	sz[node] = 1;
	strt[node] = lli(dis.size());
	dis.push_back(node);
	for(auto it: graph[node])
	{
		if(it != par)
		{
			dfs0(it, node);
			sz[node] += sz[it];
		}
	}
	en[node] = lli(dis.size())-1;
}

void dfs1(lli node, lli par, bool keep)
{
	pair<lli, lli> large = {-1, -1};

	for(auto it: graph[node])
	{
		if(it != par) large = max(large, {sz[it], it});
	}

	for(auto it: graph[node])
	{
		if(it != par && it != large.second) dfs1(it, node, 0);
	}

	if(large.second != -1)
	{
		dfs1(large.second, node, 1);
	}

	for(auto it: graph[node])
	{
		if(it != large.second)
		{
			for(lli i = strt[it];i <= en[it];i++)
			{
				upd(1, 0, maxn-1, rev[dis[i]], C[dis[i]]);
			}
		}
	}

	upd(1, 0, maxn-1, rev[node], C[node]);
	ans[node] = qry(1, 0, maxn-1, m);

	if(!keep)
	{
		for(lli i = strt[node];i <= en[node];i++)
		{
			upd(1, 0, maxn-1, rev[dis[i]], -C[dis[i]]);
		}
	}
}

int main(void)
{
	lli n, b;
	scanf("%lld%lld", &n, &m);
	vector<pair<lli, lli>> s;
	for(lli i = 0;i < n;i++)
	{
		scanf("%lld%lld%lld", &b, &C[i], &L[i]);
		b--;
		if(b >= 0) graph[b].push_back(i);

		s.push_back({C[i], i});
	}
	sort(s.begin(), s.end());

	lli tmp = 0;
	for(auto it: s) rev[it.second] = tmp++;

	dfs0(0, -1);
	dfs1(0, -1, 1);

	lli res = 0;
	for(lli i = 0;i < n;i++) res = max(res, L[i]*ans[i]);
	
	printf("%lld\n", res);
}