// Day 1, Problem 3 - Modified Treap

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <set>
#include <map>
#include <climits>
using namespace std;

typedef long long int lli;

const lli inf = 170705091707050917;

int n, k, ctr;
vector<lli> prefix;
vector<vector<int>> A;
lli memo[72][72][72];

// {key, priority, frequency};

lli DP(int L, int R, int prior)
{
	if(L == R)
	{
		if(A[L][1] >= prior) return A[L][2];
		else return A[L][2]+k;
	}
	else if(memo[L][R][prior] != -1) return memo[L][R][prior];
	else
	{
		lli res = inf;

		for(int i = L+1;i < R;i++)
		{
			if(A[i][1] >= prior)
			{
				res = min(res, DP(L, i-1, A[i][1])+DP(i+1, R, A[i][1]));
			}

			res = min(res, DP(L, i-1, prior)+DP(i+1, R, prior)+k);

			//cout << L << " " << R << " " << prior << " " << i << " " << res << "\n";
		}

		if(A[L][1] >= prior) res = min(res, DP(L+1, R, A[L][1]));
		res = min(res, DP(L+1, R, prior)+k);

		if(A[R][1] >= prior) res = min(res, DP(L, R-1, A[R][1]));
		res = min(res, DP(L, R-1, prior)+k);

		memo[L][R][prior] = res+prefix[R]-prefix[L-1];
		return res+prefix[R]-prefix[L-1];
	}
}

int main(void)
{
	scanf("%d%d", &n, &k);
	A.clear(); A.resize(n+1, vector<int>(3));
	prefix.clear(); prefix.resize(n+1);
	memset(memo, -1, sizeof(memo));

	set<int> S;
	map<int, int> mp;
	for(int i = 1;i <= n;i++) scanf("%d", &A[i][0]);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d", &A[i][1]);
		S.insert(A[i][1]);
	}
	int v = 1;
	for(auto it: S) mp[it] = v++;
	for(int i = 1;i <= n;i++)
	{
		A[i][1] = mp[A[i][1]];
	}
	for(int i = 1;i <= n;i++) scanf("%d", &A[i][2]);

	sort(A.begin(), A.end());

	for(int i = 1;i <= n;i++)
	{
		prefix[i] = A[i][2]+prefix[i-1];
	}

	//for(auto it: A) cout << it[0] << " " << it[1] << " " << it[2] << "\n";

	printf("%lld\n", DP(1, n, 0));
}
