// Rivers

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 105, maxk = 55, inf = int(2e9)+5;

int n, k, w[maxn], c[maxn], dp[maxn][maxn][maxk], memo[maxn][maxn][maxk];
vector<pair<int, int>> graph[maxn];

void dfs0(int node, int sum)
{
	c[node] = sum;
	for(auto it: graph[node])
	{
		dfs0(it.first, it.second+sum);
	}
}

int dp2(int x, int y, int idx, int kk)
{
	if(idx == int(graph[y].size())) return 0;
	else if(memo[x][graph[y][idx].first][kk] != -1) return memo[x][graph[y][idx].first][kk];
	else
	{
		int res = inf;
		for(int i = 0;i <= kk;i++)
		{
			res = min(res, dp2(x, y, idx+1, kk-i)+dp[x][graph[y][idx].first][i]);
		}
		return memo[x][graph[y][idx].first][kk] = res;
	}
}

void compute(int x, int y)
{
	for(int i = 0;i <= k;i++) dp[x][y][i] = dp2(x, y, 0, i)+(c[y]-c[x])*w[y];

	if(x != y)
	{
		for(int i = 1;i <= k;i++) dp[x][y][i] = min(dp[x][y][i], dp[y][y][i-1]);
	}

	//cout << x << " " << y << " " << dp[x][y][0] << "\n";
}

void dfs2(int anc, int node)
{
	for(auto it: graph[node])
	{
		dfs2(anc, it.first);
	}
	compute(anc, node);
}

void dfs1(int node)
{
	for(auto it: graph[node])
	{
		dfs1(it.first);
	}
	dfs2(node, node);
}

int main(void)
{
	int v, d;
	scanf("%d%d", &n, &k);

	for(int i = 0;i <= n;i++)
	{
		for(int j = 0;j <= n;j++)
		{
			for(int kk = 0;kk <= k;kk++) dp[i][j][kk] = inf;
		}
	}

	for(int i = 0;i <= n;i++)
	{
		for(int j = 0;j <= n;j++)
		{
			for(int kk = 0;kk <= k;kk++) memo[i][j][kk] = -1;
		}
	}

	for(int i = 1;i <= n;i++)
	{
		scanf("%d%d%d", &w[i], &v, &d);
		graph[v].push_back({i, d});
	}

	dfs0(0, -1);
	dfs1(0);

	/*for(int i = 0;i <= n;i++)
	{
		for(int j = 0;j <= n;j++)
		{
			for(int kk = 0;kk <= k;kk++) cout << i << " " << j << " " << kk << " " << dp[i][j][kk] << "\n";
		}
	}*/

	printf("%d\n", dp[0][0][k]);
}