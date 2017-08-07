//Palindromic Partitions

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int lli;

const lli MOD = lli(1e9)+7, base = 31;

lli n;
string S;

lli modpow(lli a, lli b)
{
	if(!b) return 1;
	else if(b == 1) return a;
	else
	{
		lli res = modpow(a, b/2)%MOD;
		res *= res;
		res %= MOD;
		if(b%2) res *= a;
		return res%MOD;
	}
}

lli solve(lli L, lli R)
{
	if(L > R) return 0;

	lli hasha = 0, hashb = 0;
	for(lli i = 0;i < n;i++)
	{
		if(L+i >= R-i) break;
		hasha *= base;
		hasha %= MOD;
		hasha += lli(S[L+i]-'a');
		hasha %= MOD;
		hashb += lli(S[R-i]-'a')*modpow(base, i);
		hashb %= MOD;
		if(hasha == hashb) return solve(L+i+1, R-i-1)+2;
	}
	return 1;
}

int main(void)
{
	lli t;
	scanf("%lld", &t);
	while(t--)
	{
		cin >> S;
		n = lli(S.size());
		printf("%lld\n", solve(0, n-1));
	}
}