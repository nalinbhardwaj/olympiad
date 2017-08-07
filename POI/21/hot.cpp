#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int lli;

inline lli C2(lli v) { return v*(v-1)/2ll; }
inline lli C3(lli v) { return v*(v-1)*(v-2)/6ll; }

const int maxn = int(5e3)+5;
vector<int> graph[maxn];
int tot[maxn+1], tots[maxn+1], n;

void dfs1(int node, int par, int ht)
{
	if(ht > n/3+1) return;
	tot[ht]++;
	for(vector<int>::iterator it = graph[node].begin();it != graph[node].end();it++)
	{
		if(*it != par) dfs1(*it, node, ht+1);
	}
}

void dfs2(int node, int par, int ht)
{
	if(ht > n/3+1) return;
	tots[ht]++;
	for(vector<int>::iterator it = graph[node].begin();it != graph[node].end();it++)
	{
		if(*it != par) dfs2(*it, node, ht+1);
	}
}

int main(void)
{
	int u, v;
	lli res = 0;
	scanf("%d", &n);

	for(int i = 1;i < n;i++)
	{
		scanf("%d%d", &u, &v);
		u--; v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for(int root = 0;root < n;root++)
	{
		for(int i = 0;i <= n/3+1;i++) tot[i] = 0;
		dfs1(root, -1, 0);
		for(int i = 1;i <= n/3+1;i++) res += C3(tot[i]);
		for(vector<int>::iterator it = graph[root].begin();it != graph[root].end();it++)
		{
			for(int i = 1;i <= n/3+1;i++) tots[i] = 0;
			dfs2(*it, root, 1);
			for(int i = 1;i <= n/3+1;i++)
			{
				res -= C3(tots[i]);
				res -= C2(tots[i])*lli(tot[i]-tots[i]);
			}
		}
	}
	printf("%lld\n", res);
}