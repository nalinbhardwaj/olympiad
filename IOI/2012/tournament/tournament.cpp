#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
 
const int maxn = int(1e5)+5;
 
int n, c, r, A[maxn], st[2][4*maxn], stf[4*maxn], stmax[4*maxn], lz[2][4*maxn], winn[maxn];
pair<int, int> R[maxn];
vector<int> starter[maxn], ender[maxn];
 
inline int left(int node) { return (node<<1); }
inline int right(int node) { return (node<<1)+1; }
 
void push(int type, int node, int L, int R)
{
	if(lz[type][node] && L != R)
	{
		st[type][left(node)] = st[type][right(node)] = 0;
		lz[type][left(node)] = lz[type][right(node)] = 1;
	}
	lz[type][node] = 0;
}
 
void build(int type, int node, int L, int R)
{
	if(L == R) st[type][node] = 1, lz[type][node] = 0, stmax[node] = A[L];
	else
	{
		build(type, left(node), L, (L+R)/2), build(type, right(node), (L+R)/2+1, R);
		st[type][node] = st[type][left(node)]+st[type][right(node)], lz[type][node] = 0;
		stmax[node] = max(stmax[left(node)], stmax[right(node)]);
	}
}
 
void upd(int type, int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return;
	else if(a <= L && R <= b) st[type][node] = 0, lz[type][node] = 1;
	else
	{
		push(type, node, L, R);
		upd(type, left(node), L, (L+R)/2, a, b), upd(type, right(node), (L+R)/2+1, R, a, b);
		st[type][node] = st[type][left(node)]+st[type][right(node)];
	}
}
 
int loc(int type, int node, int L, int R, int k)
{
	if(L == R) return L;
	else
	{
		push(type, node, L, R);
		//cout << L << " " << R << " " << k << " " << st[left(node)] << " " << st[right(node)] << "\n";
		if(st[type][left(node)] <= k) return loc(type, right(node), (L+R)/2+1, R, k-st[type][left(node)]);
		else return loc(type, left(node), L, (L+R)/2, k);
	}
}
 
int qry(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return -1;
	else if(a <= L && R <= b) return stmax[node];
	else return max(qry(left(node), L, (L+R)/2, a, b), qry(right(node), (L+R)/2+1, R, a, b));
}
 
void ptupd(int node, int L, int R, int idx, int v)
{
	stf[node] += v;
	if(L == R) return;
	else
	{
		if(idx <= (L+R)/2) ptupd(left(node), L, (L+R)/2, idx, v);
		else ptupd(right(node), (L+R)/2+1, R, idx, v);
	}
}
 
int qryf(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return 0;
	else if(a <= L && R <= b) return stf[node];
	else return qryf(left(node), L, (L+R)/2, a, b)+qryf(right(node), (L+R)/2+1, R, a, b);
}
 
int GetBestPosition(int _N, int _C, int _R, int *_K, int *_S, int *_E)
{
	n = _N, c = _C, r = _R;
	for(int i = 0;i < n-1;i++) A[i] = _K[i];
 
	for(int i = 0;i < c;i++) R[i] = make_pair(_S[i], _E[i]);
 
	build(0, 1, 0, n), build(1, 1, 0, n);
	for(int i = 0;i < c;i++)
	{
		R[i].first = loc(0, 1, 0, n, R[i].first); //cout << "\n";
		R[i].second = loc(1, 1, 0, n, R[i].second); //cout << "\n";
		upd(0, 1, 0, n, R[i].first+1, R[i].second);
		upd(1, 1, 0, n, R[i].first, R[i].second-1);
		winn[i] = qry(1, 0, n, R[i].first, R[i].second-1);
		starter[R[i].first].push_back(i);
		ender[R[i].second].push_back(i);
		//cout << R[i].first << " " << R[i].second << " " << winn[i] << "\n";
	}
 
	int res = -1, resi = -1;
	set<int> baddy;
	baddy.insert(n+1);
	
	for(int i = 0;i < n;i++)
	{
		for(auto it: starter[i])
		{
			if(winn[it] < r) ptupd(1, 0, n, it, 1);
			else baddy.insert(it);
		}
 
		int lim = *baddy.begin();
		int tmp = qryf(1, 0, n, 0, lim);
		if(res < tmp) res = tmp, resi = i;
 
		for(auto it: ender[i])
		{
			if(winn[it] < r) ptupd(1, 0, n, it, -1);
			else baddy.erase(it);
		}
	}
	return resi;
}