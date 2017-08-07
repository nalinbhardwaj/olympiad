// Baltic Olympiad in Informatics 2015 Day 1 Problem 3

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
 
const int maxn = int(5e5)+5;
 
vector<int> graph[maxn], S;
 
void dfs(int node, int par)
{
	if(int(graph[node].size()) == 1) S.push_back(node);
	for(auto it: graph[node])
	{
		if(it != par) dfs(it, node);
	}
}
 
int main(void)
{
	int n, u, v;
	scanf("%d", &n);
	for(int i = 1;i < n;i++)
	{
		scanf("%d%d", &u, &v);
		u--, v--;
		graph[u].push_back(v), graph[v].push_back(u);
	}
 
	dfs(0, -1);
 
	int res = ceil(int(S.size())/2.0);
	printf("%d\n", res);
	for(int i = 0;i < res;i++)
	{
		printf("%d %d\n", S[i]+1, S[(res+i)%int(S.size())]+1);
	}
}
