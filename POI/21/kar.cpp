#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = int(2e5)+5;

struct pnode {
	bool res[2][2];
	pnode()
	{
		for(int i = 0;i < 2;i++)
		{
			for(int j = 0;j < 2;j++) res[i][j] = 0;
		}
	}
};

int A[maxn][2];
pnode st[4*maxn];

inline int left(int node) { return (node<<1); }
inline int right(int node) { return (node<<1)+1; }

void combine(pnode& ret, pnode& a, pnode& b, int mid)
{
	for(int i = 0;i < 2;i++)
	{
		for(int j = 0;j < 2;j++)
		{
			ret.res[i][j] = 0;
			for(int k = 0;k < 2;k++)
			{
				for(int l = 0;l < 2;l++)
				{
					ret.res[i][j] = max(ret.res[i][j], bool(a.res[i][k]&b.res[l][j]&(A[mid][k] <= A[mid+1][l])));
					if(ret.res[i][j]) break;
				}
				if(ret.res[i][j]) break;
			}
		}
	}
}

void build(int node, int L, int R)
{
	if(L == R)
	{
		for(int i = 0;i < 2;i++)st[node].res[i][i] = 1;
	}
	else
	{
		build(left(node), L, (L+R)/2);
		build(right(node), (L+R)/2+1, R);
		combine(st[node], st[left(node)], st[right(node)], (L+R)/2);
	}
}

void upd(int node, int L, int R, int idx)
{
	if(L == R) return;
	else
	{
		if(idx <= (L+R)/2) upd(left(node), L, (L+R)/2, idx);
		else upd(right(node), (L+R)/2+1, R, idx);
		combine(st[node], st[left(node)], st[right(node)], (L+R)/2);
	}
}

int main(void)
{
	int n, m, x, y;
	scanf("%d", &n);
	for(int i = 0;i < n;i++)
	{
		scanf("%d%d", &A[i][0], &A[i][1]);
		sort(A[i], A[i]+2);
	}

	build(1, 0, n-1);

	scanf("%d", &m);
	while(m--)
	{
		scanf("%d%d", &x, &y);
		x--, y--;
		swap(A[x][0], A[y][0]), swap(A[x][1], A[y][1]);
		upd(1, 0, n-1, x), upd(1, 0, n-1, y);

		bool ans = 0;
		for(int i = 0;i < 2;i++)
		{
			for(int j = 0;j < 2;j++)
			{
				ans = max(ans, st[1].res[i][j]);
			}
		}
		if(ans) printf("TAK\n");
		else printf("NIE\n");
	}
}