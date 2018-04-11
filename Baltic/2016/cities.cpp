#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
using namespace std;
 
typedef long long int lli;
 
const int maxn = lli(1e5)+5, maxk = 6;
const lli inf = lli(1e17)+5;
 
int n, A[maxk];
lli dp[(1<<maxk)][maxn];
vector<pair<int, int>> graph[maxn];

int main(void)
{
	int k, m, u, v, w;
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 0;i < k;i++)
	{
		scanf("%d", &A[i]);
		A[i]--;
	}
 
	for(int i = 0;i < m;i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		u--, v--;
		graph[u].push_back({v, w}), graph[v].push_back({u, w});
	}
 
	for(int i = 0;i < (1<<k);i++)
	{
		for(int j = 0;j < n;j++) dp[i][j] = inf;
	}
	for(int i = 0;i < k;i++) dp[(1<<i)][A[i]] = 0;
 
 
	for(int mask = 1;mask < (1<<k);mask++)
	{
		priority_queue<pair<lli, int>> Q;
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < k;j++)
			{
				if((mask&(1<<j))) dp[mask][i] = min(dp[mask][i], dp[(mask^(1<<j))][i]+dp[(1<<j)][i]);
			}
			Q.push({-dp[mask][i], i});
		}
 
		while(!Q.empty())
		{
			pair<lli, int> top = Q.top();
			Q.pop();
 
			for(auto it: graph[top.second])
			{
				if(dp[mask][it.first] > dp[mask][top.second]+it.second)
				{
					dp[mask][it.first] = dp[mask][top.second]+it.second;
					Q.push({-dp[mask][it.first], it.first});
				}
			}
		}
	}
 
	lli res = inf;
	for(int i = 0;i < n;i++) res = min(res, dp[(1<<k)-1][i]);
	printf("%lld\n", res);
}