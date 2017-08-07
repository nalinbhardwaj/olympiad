#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define gc getchar_unlocked

void si(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

typedef long long int lli;

pair<int, int> A[int(1e6)+5], cur[int(1e6)+5];

int main(void)
{
	int n, x, y;
	si(n);
	A[0] = {0, 0}; cur[0] = {0, 0};
	for(int i = 1;i <= n;i++)
	{
		si(x); si(y);
		x /= 2ll; y /= 2ll;
		A[i] = {x, y};
		cur[i] = {y, x};
	}
	sort(A, A+n+1);
	sort(cur, cur+n+1);

	lli res = 0;
	int ptr = n;
	for(int i = 1;i <= n;i++)
	{
		res += lli(cur[ptr].first)*lli(A[i].first-A[i-1].first);
		while(cur[ptr].second <= A[i].first) ptr--;
	}
	printf("%lld\n", res*4ll);
}