#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = int(2e5)+5, maxlog = 19;

int n, ctr = 0, st[4*maxn+10], start[maxn], en[maxn], H[maxn], dp[maxn], T[maxn][maxlog+1];
vector<int> graph[maxn];
vector<int> C[maxn];
vector<pair<int, int>> A[maxn];
vector<pair<int, int>> B[maxn];

inline int left(int node) { return (node<<1); }
inline int right(int node) { return (node<<1)+1; }

void upd(int node, int L, int R, int a, int b, int v)
{
	if(a > R || b < L) return;
	else if(a <= L && R <= b) st[node] += v;
	else
	{
		upd(left(node), L, (L+R)/2, a, b, v);
		upd(right(node), (L+R)/2+1, R, a, b, v);
	}
}

int qry(int node, int L, int R, int a)
{
	if(L == R) return st[node];
	else
	{
		if(a <= (L+R)/2) return st[node]+qry(left(node), L, (L+R)/2, a);
		else return st[node]+qry(right(node), (L+R)/2+1, R, a);
	}
}

void dfs0(int node, int par, int ht)
{
	H[node] = ht, T[node][0] = par;
	start[node] = ctr++;
	for(auto it: graph[node])
	{
		if(it != par) dfs0(it, node, ht+1);
	}
	en[node] = ctr++;
}

void init()
{
	for(int i = 1;i <= maxlog;i++)
	{
		for(int j = 0;j < n;j++)
		{
			if(T[j][i-1] != -1) T[j][i] = T[T[j][i-1]][i-1];
		}
	}
}

pair<int, pair<int, int>> LCA(int x, int y)
{
	bool latswap = 0;
	if(H[x] > H[y]) swap(x, y), latswap = 1;
	int kidy = y;
	for(int i = maxlog;i >= 0;i--)
	{
		if(H[y]-(1<<i) >= H[x]) y = T[y][i];
		if(H[kidy]-(1<<i) > H[x]) kidy = T[kidy][i];
	}

	if(x == y)
	{
		if(latswap) return {x, {kidy, -1}};
		else return {x, {-1, kidy}};
	}

	for(int i = maxlog;i >= 0;i--)
	{
		if(T[x][i] != T[y][i]) x = T[x][i], y = T[y][i];
	}
	if(latswap) swap(x, y);
	return {T[x][0], {x, y}};
}

void dfs1(int node, int par)
{
	int s = 0;
	dp[node] = 0;
	for(auto it: graph[node])
	{
		if(it != par)
		{
			dfs1(it, node);
			s += dp[it];
		}
	}
	dp[node] = max(dp[node], s);

	for(int i = 0;i < int(A[node].size());i++)
	{
		int x = A[node][i].first, y = A[node][i].second, c = C[node][i], xx = B[node][i].first, yy = B[node][i].second;
		int tmp = qry(1, 0, maxn-1, start[x])+qry(1, 0, maxn-1, start[y])+c+s;
		tmp -= (xx != -1)*dp[xx]+(yy != -1)*dp[yy];
		dp[node] = max(dp[node], tmp);
	}
	
	upd(1, 0, maxn-1, start[node], start[node], s);
	for(auto it: graph[node])
	{
		if(it != par) upd(1, 0, maxn-1, start[it], en[it], s-dp[it]);
	}
}

int main(void)
{
	int m, x, y, c;
	scanf("%d", &n);
	for(int i = 1;i < n;i++)
	{
		scanf("%d%d", &x, &y);
		x--, y--;
		graph[x].push_back(y), graph[y].push_back(x);
	}

	for(int i = 0;i <= n;i++)
	{
		for(int j = 0;j <= maxlog;j++) T[i][j] = -1;
	}

	dfs0(0, -1, 0);
	init();

	scanf("%d", &m);
	for(int i = 0;i < m;i++)
	{
		scanf("%d%d%d", &x, &y, &c);
		x--, y--;
		pair<int, pair<int, int>> l = LCA(x, y);
		//cout << l.first << " " << l.second.first << " " << l.second.second << "\n";
		A[l.first].push_back({x, y}), C[l.first].push_back(c), B[l.first].push_back(l.second);
	}

	dfs1(0, -1);
	printf("%d\n", dp[0]);
}