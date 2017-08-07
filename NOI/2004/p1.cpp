// Day 1, Problem 1 - The Depressed Cashier

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxv = int(4e5), offset = int(15e4);
int st[4*(maxv+offset+100)], lz[4*(maxv+offset+100)];

inline int left(int node) { return node<<1; }
inline int right(int node) { return (node<<1)+1; }

void shift(int node, int L, int R)
{
	if(L != R)
	{
		if(lz[node])
		{
			lz[left(node)] = 1;
			lz[right(node)] = 1;
			st[left(node)] = 0;
			st[right(node)] = 0;
		}
	}
	lz[node] = 0;
}

void upd(int node, int L, int R, int idx)
{
	if(L == R)
	{
		st[node]++;
	}
	else
	{
		shift(node, L, R);
		if(idx <= (L+R)/2) upd(left(node), L, (L+R)/2, idx);
		else upd(right(node), (L+R)/2+1, R, idx);
		st[node] = st[left(node)]+st[right(node)];
	}
}

int qry(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return 0;
	else if(a <= L && R <= b) return st[node];
	else
	{
		shift(node, L, R);
		return qry(left(node), L, (L+R)/2, a, b)+qry(right(node), (L+R)/2+1, R, a, b);
	}
}

void rngupd(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return;
	else if(a <= L && R <= b)
	{
		lz[node] = 1;
		st[node] = 0;
	}
	else
	{
		shift(node, L, R);
		rngupd(left(node), L, (L+R)/2, a, b);
		rngupd(right(node), (L+R)/2+1, R, a, b);
		st[node] = st[left(node)]+st[right(node)];
	}
}

int main(void)
{
	int n, mini, delta = 0, k, ans = 0;
	scanf("%d%d", &n, &mini);

	string S;
	while(n--)
	{
		ans += qry(1, 0, maxv+offset, 0, mini-delta-1+offset);
		rngupd(1, 0, maxv+offset, 0, mini-delta-1+offset);
		cin >> S;
		scanf("%d", &k);
		if(S[0] == 'I')
		{
			if(k >= mini) upd(1, 0, maxv+offset, k-delta+offset);
			//else ans++;
		}
		else if(S[0] == 'A')
		{
			delta += k;
		}
		else if(S[0] == 'S')
		{
			delta -= k;
		}
		else
		{
			int L = 0, R = maxv+offset, mid, v;

			v = qry(1, 0, maxv+offset, 0, maxv+offset);
			//cout << v << "\n";
			if(v < k)
			{
				printf("-1\n");
				continue;
			}
			else
			{
				while(L <= R)
				{
					mid = (L+R)/2;
					v = qry(1, 0, maxv+offset, mid, maxv+offset);
					//cout << L << " " << R << " " << v << "\n";
					if(v < k)
					{
						R = mid-1;
					}
					else
					{
						L = mid+1;
					}
				}
				printf("%d\n", L-1+delta-offset);
				//printf("-1\n");
			}
		}
		ans += qry(1, 0, maxv+offset, 0, mini-delta-1+offset);
		rngupd(1, 0, maxv+offset, 0, mini-delta-1+offset);
		//cout << "next\n";
	}
	printf("%d\n", ans);
}