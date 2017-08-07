#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int maxn = int(1e6)+5;

int vis[maxn], type[maxn], cnt[maxn];
vector<int> graph[maxn];

void bfs(int node, int comp)
{
	queue<pair<int, int>> Q;
	Q.push({node, -1});
	while(!Q.empty())
	{
		pair<int, int> top = Q.front();
		Q.pop();

		//cout << top.first << "\n";
		vis[top.first] = 1; cnt[comp]++;

		for(auto it: graph[top.first])
		{
			//cout << top.first << " " << it << " " << vis[it] << "\n";
			if(vis[it] && it != top.second) type[comp] = 1;
			else if(!vis[it])
			{
				vis[it] = 1;
				Q.push({it, top.first});
			}
		
		}
	}
}

int main(void)
{
	int n, m, k, ctr = 0, u, v;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0;i < m;i++)
	{
		scanf("%d%d", &u, &v);
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for(int i = 0;i < n;i++)
	{
		if(!vis[i]) bfs(i, ctr++);
	}

	int res1 = 0, res2 = 0;
	for(int i = 0;i < ctr;i++)
	{
		res1 += (cnt[i]/k)*k;
		//cout << i << " " << cnt[i] << "\n";
		if((cnt[i]/k)+bool(cnt[i]%k) > 1)
		{
			if(!type[i]) res2 += (cnt[i]/k)+bool(cnt[i]%k)-1;
			else res2 += (cnt[i]/k)+bool(cnt[i]%k);
		}
	}
	printf("%d %d\n", res1, res2);
}