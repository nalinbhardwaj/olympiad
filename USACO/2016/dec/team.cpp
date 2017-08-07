#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli MOD = lli(1e9)+9;

lli n, m;
vector<lli> A, B;
lli memo[lli(1e3)+5][lli(1e3)+5][11];

inline lli tran(lli x) { return ((x%MOD)+MOD)%MOD; }

lli DP(lli idx, lli idy, lli cow)
{
	if(cow == 0) return 1;
	else if(idx == n || idy == m) return 0;
	else if(memo[idx][idy][cow] != -1707050917) return memo[idx][idy][cow];
	else
	{
		lli res = 0;
		res += tran(tran(tran(DP(idx+1, idy, cow))+tran(DP(idx, idy+1, cow)))-tran(DP(idx+1, idy+1, cow)));
		res = tran(res);
		if(A[idx] > B[idy]) res += tran(DP(idx+1, idy+1, cow-1));
		res = tran(res);
		//cout << idx << " " << idy << " " << cow << ": " << res << "\n";
		memo[idx][idy][cow] = res;
		return res;
	}
}

int main(void)
{
	ifstream fin("team.in");
	ofstream fout("team.out");
	lli k;
	fin >> n >> m >> k;
	A.clear(); A.resize(n);
	B.clear(); B.resize(m);
	for(lli i = 0;i < n;i++) fin >> A[i];
	for(lli i = 0;i < m;i++) fin >> B[i];
	sort(A.rbegin(), A.rend());
	sort(B.rbegin(), B.rend());

	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < m;j++)
		{
			for(int kk = 0;kk <= k;kk++) memo[i][j][kk] = -1707050917;
		}
	}

	fout << DP(0, 0, k) << "\n";

	/*lli res = 0;
	for(lli i = 0;i < n;i++)
	{
		for(lli j = i+1;j < n;j++)
		{
			for(lli k = 0;k < m;k++)
			{
				for(lli l = k+1;l < m;l++)
				{
					res += (A[i] > B[k] && A[j] > B[l]);
				}
			}
		}
	}
	printf("%d\n", res);*/
}