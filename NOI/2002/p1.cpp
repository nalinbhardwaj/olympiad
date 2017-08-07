// Day 1, Problem 1 - Legend of the Galactic Heroes

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int n = 30005;
int sz[n+2], wt[n+2], par[n+2];

int root(int node)
{
	if(par[node] == node) return par[node];
	else
	{
		int tmp = root(par[node]);
		wt[node] += wt[par[node]];
		par[node] = tmp;
		return par[node];
	}
}

void dsu(int x, int y)
{
	x = root(x);
	y = root(y);
	wt[y] = sz[x];
	sz[x] += sz[y];
	sz[y] = 0;
	par[y] = x;
}

int main(void)
{
	int t, a, b;
	scanf("%d", &t);
	for(int i = 0;i <= n;i++) par[i] = i, sz[i] = 1;
	while(t--)
	{
		char S[3];
		scanf("%s", S);
		if(S[0] == 'M')
		{
			scanf("%d%d", &a, &b);
			a--; b--;
			swap(a, b);
			if(root(a) != root(b)) dsu(a, b);
		}
		else
		{
			scanf("%d%d", &a, &b);
			a--; b--;
			if(root(a) != root(b)) printf("-1\n");
			else printf("%d\n", abs(wt[a]-wt[b])-1);
			//for(int i = 0;i < n;i++) printf("%d ", wt[i]);
			//printf("\n");
		}
	}
}