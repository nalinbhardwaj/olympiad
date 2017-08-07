#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

const int maxn = int(1e5)+5, off = 4;

int n, st[maxn*4], A[maxn], B[maxn], rev[maxn];
vector<vector<int>> memo(maxn, vector<int>(10, -1));

inline int left(int node) { return node<<1; }
inline int right(int node) { return (node<<1)+1; }

int qry(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return 0;
	else if(a <= L && R <= b) return st[node];
	else
	{
		return max(qry(left(node), L, (L+R)/2, a, b), qry(right(node), (L+R)/2+1, R, a, b));
	}
}

void upd(int node, int L, int R, int idx, int v)
{
	if(L == R)
	{
		st[node] = max(st[node], v);
	}
	else
	{
		if(idx <= (L+R)/2) upd(left(node), L, (L+R)/2, idx, v);
		else upd(right(node), (L+R)/2+1, R, idx, v);
		st[node] = max(st[left(node)], st[right(node)]);
	}
}

void solve()
{
	for(int idx = n-1;idx >= 0;idx--)
	{
		for(int i = max(0, A[idx]-4);i <= min(n-1, A[idx]+4);i++)
		{
			memo[idx][i-A[idx]+off] = qry(1, 0, n-1, rev[i]+1, n-1)+1;
		}
		for(int i = max(0, A[idx]-4);i <= min(n-1, A[idx]+4);i++)
		{
			upd(1, 0, n-1, rev[i], memo[idx][i-A[idx]+off]);
		}
	}
}

int main(void)
{
	ifstream fin("nocross.in");
	ofstream fout("nocross.out");
	fin >> n;
	for(int i = 0;i < n;i++)
	{
		fin >> A[i];
		A[i]--;
	}
	for(int i = 0;i < n;i++)
	{
		fin >> B[i];
		B[i]--;
		rev[B[i]] = i;
	}

	solve();
	int res = 0;
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j <= 8;j++) res = max(res, memo[i][j]);
	}
	fout << res << "\n";
}