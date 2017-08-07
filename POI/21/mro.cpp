#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e6)+5, inf = lli(1e10)+5;

lli m[maxn];
pair<lli, lli> val[maxn];
vector<lli> graph[maxn];

void dfs(lli node, lli par, lli L, lli R)
{
	val[node] = make_pair(L, R);
	lli d = lli(graph[node].size())-1;
	L *= d, R *= d;
	R += d-1;
	L = min(L, inf), R = min(R, inf);
	for(vector<lli>::iterator it = graph[node].begin();it != graph[node].end();it++)
	{
		if(*it != par) dfs(*it, node, L, R);
	}
}

int main(void)
{
	lli n, k, g, u, v;
	scanf("%lld%lld%lld", &n, &g, &k);
	for(lli i = 0;i < g;i++) scanf("%lld", &m[i]);
	sort(m, m+g);

	pair<lli, lli> gg;
	for(lli i = 1;i < n;i++)
	{
		scanf("%lld%lld", &u, &v);
		u--, v--;
		if(i == 1) gg = make_pair(u, v);
		graph[u].push_back(v), graph[v].push_back(u);
	}

	dfs(gg.first, gg.second, k, k), dfs(gg.second, gg.first, k, k);

	lli res = 0;
	for(lli i = 0;i < n;i++)
	{
		if(lli(graph[i].size()) == 1)
		{
			//prllif("%d %d %d ", i, val[i].first, val[i].second);
			lli up = lli(upper_bound(m, m+g, val[i].second)-m)-1;
			lli down = lli(lower_bound(m, m+g, val[i].first)-m)-1;
			res += up-down;
		}
	}
	printf("%lld\n", res*k);
}