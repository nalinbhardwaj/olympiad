// SPOJ submission 19472792 (CPP14) plaintext list. Status: AC, problem CEOI09HA, contest OI. By nib (nibnalin), 2017-05-24 12:10:45.

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
 
typedef long double dbl;
typedef long long int lli;
 
const lli maxn = lli(1e5)+5;
 
struct line {
	lli m, c;
	line(lli _m = 0.00, lli _c = 0.00)
	{
		m = _m, c = _c;
	}
};
 
struct cht {
	int sz = 0;
	line st[maxn];
	vector<pair<int, line>> changes;
	dbl intersect(line a, line b)
	{
		return dbl(b.c-a.c)/(a.m-b.m);
	}
 
	void insert(line a)
	{
		//cout << a.m << " " << a.c << "\n";
		changes.push_back({sz, {0, 0}});
		int L = 0, R = sz-1;
		while(L < R)
		{
			int mid = (L+R)/2;
			if(intersect(st[mid], a) < intersect(st[mid], st[mid+1])) R = mid;
			else L = mid+1;
		}
		sz = R+1;
		changes.back().second = st[sz];
		st[sz++] = a;
	}
 
	lli query(dbl x)
	{
		if(!sz) return 0;
		int L = 0, R = sz-1;
		while(L < R)
		{
			int mid = (L+R)/2;
			//cout << mid << " " << lliersect(mid, mid+1) << "\n";
			if(x < intersect(st[mid], st[mid+1])) R = mid;
			else L = mid+1;
		}
		return st[L].m*x+st[L].c;
	}
 
	void rollback()
	{
		if(!changes.empty())
		{
			pair<int, line> top = changes.back();
			changes.resize(lli(changes.size())-1);
			st[sz-1] = top.second;
			sz = top.first;
		}
	}
 
	void prllier()
	{
		for(lli i = 0;i < sz;i++) cout << st[i].m << " " << st[i].c << "\n";
	}
};
 
cht C;
lli V[maxn], S[maxn], D[maxn], dp[maxn];
vector<pair<int, lli>> graph[maxn];
 
void dfs(int node, int par, lli upar)
{
	D[node] = upar;
	dp[node] = C.query(V[node])+D[node]*V[node]+S[node];
	C.insert({-D[node], dp[node]});
	//cout << -D[node] << " " << dp[node] << "\n";
	for(auto it: graph[node])
	{
		if(it.first != par) dfs(it.first, node, upar+it.second);
	}
	C.rollback();
}
 
int main(void)
{
	int n, u, v, d;
	scanf("%d", &n);
	for(int i = 1;i < n;i++)
	{
		scanf("%d%d%d", &u, &v, &d);
		u--, v--;
		graph[u].push_back({v, d});
		graph[v].push_back({u, d});
	}
	for(int i = 1;i < n;i++) scanf("%lld%lld", &S[i], &V[i]);
	dfs(0, -1, 0);
 
	for(int i = 1;i < n;i++) printf("%lld ", dp[i]);
	printf("\n");
} 