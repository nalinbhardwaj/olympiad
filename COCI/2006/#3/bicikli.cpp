#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#include <iomanip>
using namespace std;

const int MOD = int(1e9);

vector<vector<vector<int>>> graph;
vector<vector<int>> reachable;

void rekt()
{
	//assert(0);
	printf("inf\n");
	exit(0);
}

void weed(int node, int type)
{
	reachable[type][node] = 1;
	//if((type == 0 && node != 1) || (type == 1 && node != 0))
	//{
		for(auto it: graph[type][node])
		{
			if(!reachable[type][it]) weed(it, type);
		}
	//}
}

int main(void)
{
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	if(n == 1)
	{
		printf("0\n");
		return 0;
	}
	graph.clear(); graph.resize(2, vector<vector<int>>(n));
	reachable.clear(); reachable.resize(2, vector<int>(n));

	for(int i = 0;i < m;i++)
	{
		scanf("%d%d", &u, &v);
		u--; v--;
		graph[0][u].push_back(v);
		graph[1][v].push_back(u);
	}

	weed(0, 0);
	weed(1, 1);

	vector<int> val(n), deg(n), topo(n);

	for(int i = 0;i < n;i++)
	{
		val[i] = (reachable[0][i] && reachable[1][i]);
		//cout << i << " " << reachable[0][i] << " " << reachable[1][i] << "\n";
	}

	for(int i = 0;i < n;i++)
	{
		if(val[i])
		{
			for(auto it: graph[0][i])
			{
				if(val[it]) deg[it]++;
			}
		}
	}

	set<int> cur;
	int ctr = 1;

	for(int i = 0;i < n;i++)
	{
		if(val[i])
		{
			if(!deg[i]) cur.insert(i);
		}
	}

	vector<pair<int, int>> S;
	while(!cur.empty())
	{
		int top = *cur.begin();
		cur.erase(cur.begin());
		topo[top] = ctr++;
		S.push_back({topo[top], top});

		for(auto it: graph[0][top])
		{
			if(val[it])
			{
				deg[it]--;
				if(!deg[it]) cur.insert(it);
			}
		}
	}

	for(int i = 0;i < n;i++)
	{
		if(val[i])
		{
			for(auto it: graph[0][i])
			{
				if(val[it])
				{
					if(topo[it] < topo[i])
					{
						rekt();
					}
				}
			}
		}
	}
	vector<long long int> dp(n);

	sort(S.rbegin(), S.rend()); dp[1] = 1;
	vector<bool> ya(n);
	for(auto it: S)
	{
		//cout << it.first << " " << it.second << "\n";
		if(val[it.second])
		{
			for(auto gt: graph[0][it.second])
			{
				if(val[gt])
				{
					//cout << it.second << " " << gt << "\n";
					dp[it.second] += dp[gt];
					if(dp[it.second] >= MOD || ya[gt])
					{
						ya[it.second] = 1;
						dp[it.second] %= MOD;
					}
				}
			}
		}
	}

	if(ya[0]) cout << setfill('0') << setw(9) << dp[0] << "\n";
	else cout << dp[0] << "\n";
}