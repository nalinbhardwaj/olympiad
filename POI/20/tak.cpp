#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;

void rekt()
{
	printf("0\n");
	exit(0);
}

int main(void)
{
	lli n, m, d;
	scanf("%lld%lld%lld", &m, &d, &n);
	vector<lli> A(n);
	for(lli i = 0;i < n;i++) scanf("%lld", &A[i]);
	sort(A.rbegin(), A.rend());
	lli l = d, r = m-d, res = 0, del = -1;

	for(lli i = 0;i < n;i++)
	{
		if(!l || A[i] < l) break;
		del = A[i]-2ll*l;
		l = max(0ll, 2ll*l-A[i]), res++;
	}
	if(l == 0 && r <= del)
	{
		printf("%lld\n", res);
		return 0;
	}
	else if(l) rekt();

	l = d, r = m-d, res = 1;

	if(A[0] < r) rekt();
	lli spec = n-1;
	while(A[spec] < r) spec--;

	A[spec] -= r;

	for(lli i = 0;i < n;i++)
	{
		if(i == spec) continue;
		l = max(0ll, 2ll*l-A[i]), res++;

		if(2ll*l <= A[spec])
		{
			l = 0;
			break;
		}
	}

	if(l) rekt();
	printf("%lld\n", res);
}