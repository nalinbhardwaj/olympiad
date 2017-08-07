#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

const int maxn = 55;

int n, A[maxn];
int LIS[maxn][maxn], LDS[maxn][maxn], P[maxn][maxn], S[maxn][maxn];
vector<int> st;

inline int left(int node) { return node<<1; }
inline int right(int node) { return (node<<1)+1; }

void upd(int node, int L, int R, int idx, int val)
{
	if(L == R)
	{
		st[node] = val;
	}
	else
	{
		if(idx <= (L+R)/2) upd(left(node), L, (L+R)/2, idx, val);
		else upd(right(node), (L+R)/2+1, R, idx, val);
		st[node] = max(st[left(node)], st[right(node)]);
	}
}

int qry(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return 0;
	else if(a <= L && R <= b) return st[node];
	else
	{
		return max(qry(left(node), L, (L+R)/2, a, b), qry(right(node), (L+R)/2+1, R, a, b));
	}
}

void calcp()
{
	st.clear(); st.resize(4*maxn+10);
	for(int i = 0;i < n;i++)
	{
		int tmp = qry(1, 0, maxn-1, 0, A[i])+1;
		upd(1, 0, maxn-1, A[i], tmp);

		for(int val = 1;val < maxn;val++)
		{
			P[i][val] = qry(1, 0, maxn-1, 0, val);
		}
	}
}

void calcs()
{
	st.clear(); st.resize(4*maxn+10);
	for(int i = n-1;i >= 0;i--)
	{
		int tmp = qry(1, 0, maxn-1, A[i], maxn-1)+1;
		upd(1, 0, maxn-1, A[i], tmp);

		for(int val = 1;val < maxn;val++)
		{
			S[i][val] = qry(1, 0, maxn-1, val, maxn-1);
		}
	}
}

bool belongs(int value, int mini, int maxi)
{
	return (value >= mini && value <= maxi);
}

vector<vector<vector<vector<int>>>> memo(maxn, vector<vector<vector<int>>>(maxn, vector<vector<int>>(maxn, vector<int>(maxn, -1))));

int DP(int L, int R, int maxi, int mini)
{
	if(L > R || maxi < mini) return 0;
	else if(memo[L][R][maxi][mini] != -1) return memo[L][R][maxi][mini];
	else
	{
		int res = max(DP(L+1, R, maxi, mini), DP(L, R-1, maxi, mini));

		if(belongs(A[L], mini, maxi))
		{
			res = max(res, DP(L+1, R, maxi, A[L])+1);
			res = max(res, DP(L+1, R-1, A[L], mini)+1);
		}
		if(belongs(A[R], mini, maxi))
		{
			res = max(res, DP(L, R-1, A[R], mini)+1);
			res = max(res, DP(L+1, R-1, maxi, A[R])+1);
		}
		if(belongs(A[L], mini, maxi) && belongs(A[R], mini, maxi) && L != R)
		{
			res = max(res, DP(L+1, R-1, A[L], A[R])+2);
		}
		memo[L][R][maxi][mini] = res;
		return res;
	}
}

int main(void)
{
	ifstream fin("subrev.in");
	ofstream fout("subrev.out");
	fin >> n;
	for(int i = 0;i < n;i++) fin >> A[i];

	int res = 0;
	calcp(); calcs();

	for(int i = 0;i < n;i++)
	{
		for(int j = i;j < n;j++)
		{
			for(int maxi = 1;maxi < maxn;maxi++)
			{
				for(int mini = 1;mini <= maxi;mini++)
				{
					res = max(res, DP(i, j, maxi, mini)+(i?P[i-1][mini]:0)+S[j+1][maxi]);
					/*if(res == 8)
					{
						cout << i << " " << j << " " << maxi << " " << mini << " " << DP(i, j, maxi, mini) << "\n";
						//return 0;
					}*/
				}
			}
		}
	}
	fout << res << "\n";
	//cout << DP(0, n-1, 4, 3) << "\n";
}