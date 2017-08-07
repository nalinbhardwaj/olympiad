#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#include "dreaming.h"
using namespace std;
 
const int maxn = int(1e5)+5, inf = int(2e9)+5;
 
int n, m, l, D[2][maxn], vis[maxn];
vector<int> cur_comp;
vector<pair<pair<int, int>, int>> guys;
vector<pair<int, int>> graph[maxn];
 
int dfs(int node, int par, int d, int type)
{
	D[type][node] = d;
	if(type) cur_comp.push_back(node);
	int cur = node;
	for(auto it: graph[node])
	{
		if(it.first != par)
		{
			int tmp = dfs(it.first, node, d+it.second, type);
			if(D[type][cur] < D[type][tmp]) cur = tmp;
		}
	}
	return cur;
}
 
 
int travelTime(int _N, int _M, int _L, int _A[], int _B[], int _T[]) {
	n = _N, m = _M, l = _L;
	for(int i = 0;i < m;i++)
	{
		graph[_A[i]].push_back({_B[i], _T[i]});
		graph[_B[i]].push_back({_A[i], _T[i]});
	}
 
	pair<pair<int, int>, int> prev = {{-1, -1}, -1};
	for(int i = 0;i < n;i++)
	{
		if(!vis[i])
		{
			cur_comp.clear();
			int f1 = dfs(i, -1, 0, 0);
			int f2 = dfs(f1, -1, 0, 0);
			dfs(f2, -1, 0, 1);
			pair<pair<int, int>, int> mini = {{inf, -inf}, inf};
			for(auto it: cur_comp)
			{
				mini = min(mini, {{max(D[0][it], D[1][it]), min(D[0][it], D[1][it])}, it});
				vis[it] = 1;
			}
			guys.push_back(mini);
		}
	}
	
	sort(guys.rbegin(), guys.rend());
 
	for(auto it: guys)
	{
		if(prev.second == -1)
		{
			prev = it;
			continue;
		}
 
		pair<pair<int, int>, int> t1, t2;
		if(it.first.first+l+prev.first.first > prev.first.first+prev.first.second) t1 = {{max(it.first.first+l, prev.first.first), min(it.first.first+l, prev.first.first)}, prev.second};
		else t1 = prev;
 
		if(it.first.first+prev.first.first+l > it.first.first+it.first.second) t2 = {{max(it.first.first, prev.first.first+l), min(it.first.first, prev.first.first+l)}, it.second};
		else t2 = it;
		
		prev = min(t1, t2);
	}
 
	return prev.first.first+prev.first.second;
}