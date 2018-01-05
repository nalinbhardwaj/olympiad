#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int lli;

const lli maxn = 20;

lli memo[maxn][12][12][2][2][2];
string A[2];

inline bool ispal(lli x, lli y, lli z) { return ((y == z) || (x == z)); }

lli DP(lli idx, lli prev, lli pprev, lli less, lli started, lli type)
{
	if(idx == lli(A[type].size())) return 1;
	else if(memo[idx][prev][pprev][less][started][type] != -1) return memo[idx][prev][pprev][less][started][type];
	else
	{
		lli res = 0, val = (less?9:lli(A[type][idx]-'0'));
		for(lli i = 0;i <= val;i++)
		{
			if(ispal(pprev, prev, i)) continue;
			if(!started && !i) res += DP(idx+1, 10, prev, max(less, lli(i < val)), started, type);
			else res += DP(idx+1, i, prev, max(less, lli(i < val)), 1, type);
		}
		return memo[idx][prev][pprev][less][started][type] = res;
	}
}

int main(void)
{
	lli a, b;
	scanf("%lld%lld", &a, &b);
	A[0] = to_string(b), A[1] = to_string(a-1);

	for(lli i = 0;i < maxn;i++)
	{
		for(lli j = 0;j < 11;j++)
		{
			for(lli k = 0;k < 11;k++)
			{
				for(lli l = 0;l < 2;l++)
				{
					for(lli m = 0;m < 2;m++) memo[i][j][k][l][m][0] = memo[i][j][k][l][m][1] = -1;
				}
			}
		}
	}

	lli res = DP(0, 10, 10, 0, 0, 0)-DP(0, 10, 10, 0, 0, 1);
	printf("%lld\n", res);
}