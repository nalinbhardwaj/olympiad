// Mean Sequence

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int lli;

const lli maxn = lli(5e6)+5, inf = lli(1e17)+5;

lli m[maxn];
pair<lli, lli> rng[maxn];

int main(void)
{
	lli n;
	scanf("%lld", &n);
	for(lli i = 0;i < n;i++) scanf("%lld", &m[i]);

	rng[0] = {-inf, m[0]};
	for(int i = 1;i <= n;i++)
	{
		rng[i] = {2ll*m[i-1]-rng[i-1].second, 2ll*m[i-1]-rng[i-1].first};
		rng[i].first = max(rng[i].first, m[i-1]);
		if(i < n) rng[i].second = min(rng[i].second, m[i]);
	}
	printf("%lld\n", max(0ll, rng[n].second-rng[n].first+1));
}