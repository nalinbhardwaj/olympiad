#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
 
typedef long long int lli;
 
const lli maxn = lli(2e3)+5, MOD = lli(1e9)+7;
 
lli n, cs, cf, memo[maxn][maxn];
 
inline lli c2(lli x)
{
	return ((x*(x-1ll)))%MOD;
}
 
lli DP(lli idx, lli chains, lli start, lli end)
{
	if(idx == n) return (!start && !end && !chains);
	if(idx > cs && !start) return 0;
	if(idx > cf && !end) return 0;
	else if(memo[idx][chains] != -1) return memo[idx][chains]%MOD;
	else if(idx == cs)
	{
		lli res = DP(idx+1, chains, 1, end)%MOD;
		if(chains)
		{
			res += chains*DP(idx+1, chains-1, 1, end)%MOD;
			res %= MOD;
		}
		if(end)
		{
			res += DP(idx+1, chains, 0, 0)%MOD;
			res %= MOD;
		}
		res %= MOD;
		memo[idx][chains] = res;
		//cout << idx << " " << chains << " " << start << " " << end << ": " << res << "\n";
		return res;
	}
	else if(idx == cf)
	{
		lli res = DP(idx+1, chains, start, 1)%MOD;
		if(chains)
		{
			res += chains*DP(idx+1, chains-1, start, 1)%MOD;
			res %= MOD;
		}
		if(start)
		{
			res += DP(idx+1, chains, 0, 0)%MOD;
			res %= MOD;
		}
		res %= MOD;
		memo[idx][chains] = res;
		//cout << idx << " " << chains << " " << start << " " << end << ": " << res << "\n";
		return res;
	}
	else
	{
		lli res = DP(idx+1, chains+1, start, end)%MOD;
		if(chains > 1)
		{
			res += c2(chains)*DP(idx+1, chains-1, start, end)%MOD;
			res %= MOD;
		}
		if(start && chains)
		{
			res += chains*DP(idx+1, chains-1, start, end)%MOD;
			res %= MOD;
		}
		if(chains && end)
		{
			res += chains*DP(idx+1, chains-1, start, end)%MOD;
			res %= MOD;
		}
		if(start && end)
		{
			res += DP(idx+1, chains, start-1, end-1)%MOD;
			res %= MOD;
		}
		res %= MOD;
		memo[idx][chains] = res;
		//cout << idx << " " << chains << " " << start << " " << end << ": " << res << "\n";
		return res;
	}
}
 
int main(void)
{
	scanf("%lld%lld%lld", &n, &cs, &cf);
	cs--, cf--;
 
	for(lli i = 0;i <= n;i++)
	{
		for(lli j = 0;j <= n;j++)
		{
			memo[i][j] = -1;
		}
	}
 
	printf("%lld\n", DP(0, 0, 0, 0)%MOD);
}