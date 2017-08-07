#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include "game.h"
using namespace std;
 
const int maxn = 1505;
 
int n, P[maxn], sz[maxn], ctr[maxn][maxn];
 
inline int root(int x)
{
	return ((P[x] == x)?x:(P[x] = root(P[x])));
}
 
void dsu(int x, int y)
{
	x = root(x), y = root(y);
	if(sz[x] < sz[y]) swap(x, y);
	P[y] = x;
	sz[x] += sz[y];
	for(int i = 0;i < n;i++)
	{
		int a = min(i, x), b = max(i, x);
		ctr[a][b] = ctr[min(i, x)][max(i, x)]+ctr[min(i, y)][max(i, y)];
	}
}
 
void initialize(int _N)
{
	n = _N;
	for(int i = 0;i < n;i++)
	{
		P[i] = i, sz[i] = 1;
	}
}
 
int hasEdge(int u, int v)
{
	u = root(u), v = root(v);
	if(u == v) return 0;
	if(u > v) swap(u, v);
	ctr[u][v]++;
	//cout << u << " " << v << " " << ctr[u][v] << " " << sz[u] << " " << sz[v] << "\n";
	if(ctr[u][v] == sz[u]*sz[v])
	{
		dsu(u, v);
		return 1;
	}
	else return 0;
}