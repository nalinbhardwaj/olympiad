#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int lli;

const lli maxn = 55, inf = lli(1e14)+5;

lli n, a, b, ans = inf, A[maxn], memo[maxn][maxn][maxn*20];

void DP(lli idx, lli p, lli mask)
{
	if(idx == n+1)
	{
		if(a <= p && p <= b) ans = min(ans, mask);
		else return;
	}
	else if(p > b) return;
	else if(memo[idx][p][mask]) return;
	else
	{
		for(lli i = idx;i <= n;i++) DP(i+1, p+1, mask|(A[i]-A[idx-1]));
		memo[idx][p][mask] = 1;
	}
}

int main(void)
{
	scanf("%lld%lld%lld", &n, &a, &b);

	for(lli i = 1;i <= n;i++) scanf("%lld", &A[i]);

	for(lli i = 1;i <= n;i++) A[i] += A[i-1];

	DP(1, 0, 0);
	printf("%lld\n", ans);
}