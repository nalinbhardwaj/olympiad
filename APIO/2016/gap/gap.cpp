#include <iostream>
#include <cstdio>
#include <vector>
#include "gap.h"
using namespace std;
 
typedef long long int lli;
 
const lli maxn = lli(1e5)+5, inf = lli(1e18)+1;
 
lli ans = 0, A[maxn];
 
void sub1(lli n)
{
	pair<lli, lli> range = {0, inf};
	lli L = 0, R = n-1;
	while(L <= R)
	{
		MinMax(range.first, range.second, &A[L], &A[R]);
		range.first = A[L]+1, range.second = A[R]-1;
		L++, R--;
	}
	for(lli i = 1;i < n;i++) ans = max(ans, A[i]-A[i-1]);
}
 
void sub2(lli n)
{
	pair<lli, lli> range;
	MinMax(0, inf, &range.first, &range.second);
	lli sz = (range.second-range.first+n-1)/(n-1);
	lli prev = range.first;
	pair<lli, lli> cur = {range.first+1, min(range.second-1, range.first+sz)};
	while(cur.first < range.second)
	{
		pair<lli, lli> res;
		//cout << cur.first << " " << cur.second << "\n";
		MinMax(cur.first, cur.second, &res.first, &res.second);
		if(res.first != -1)
		{
			ans = max(ans, res.first-prev);
			prev = res.second;
		}
		cur.first = cur.second+1;
		cur.second = min(range.second-1, cur.first+sz-1);
	}
	ans = max(ans, range.second-prev);
}
 
lli findGap(int t, int n)
{
	if(t == 1) sub1(n);
	else sub2(n);
	return ans;
}