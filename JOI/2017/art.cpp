#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli maxn = lli(5e5)+5;

lli P[maxn];
pair<lli, lli> A[maxn];

int main(void)
{
	lli n;
	scanf("%lld", &n);
	for(lli i = 1;i <= n;i++) scanf("%lld%lld", &A[i].first, &A[i].second);
	sort(A+1, A+n+1);

	for(lli i = 1;i <= n;i++) P[i] = A[i].second+P[i-1];

	lli res = 0, maxi = 0;
	for(lli i = 1;i <= n;i++)
	{
		maxi = max(maxi, A[i].first-P[i-1]);
		res = max(res, P[i]-A[i].first+maxi);
	}
	printf("%lld\n", res);
}