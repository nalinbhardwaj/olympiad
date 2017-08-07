#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = int(1e3)+5;

int n, in[maxn];
bool G[maxn][maxn];

void dfs(int node, int comp)
{
	in[node] = comp;
	for(int i = 0;i < n;i++)
	{
		if(!in[i] && G[node][i])
		{
			dfs(i, comp);
		}
	}
}

int main(void)
{
	int m, u, v;
	scanf("%d%d", &n, &m);
	for(int i = 0;i < n;i++) G[i][i] = 1;

	if(!m)
	{
		printf("NE\n");
		return 0;
	}

	while(m--)
	{
		scanf("%d%d", &u, &v);
		u--; v--;
		G[u][v] = G[v][u] = 1;
	}

	int ctr = 1;
	for(int i = 0;i < n;i++)
	{
		if(!in[i])
		{
			dfs(i, ctr++);
		}
	}

	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			if(in[i] == in[j] && !G[i][j])
			{
				printf("NE\n");
				return 0;
			}
		}
	}
	printf("DA\n");
}