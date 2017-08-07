// Birthday

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = int(1e6)+5;

int n, A[maxn], loc[maxn], ctr[maxn];

inline int intmod(int a, int b)
{
	return ((a%b)+b)%b;
}

bool f(int x)
{
	if(x > n/2) return true;
	int cur = 0;
	for(int i = 0;i <= n;i++) ctr[i] = 0;
	for(int i = 0;i < n;i++)
	{
		//i needs to be in range loc[i]-x, loc[i]+x;
		pair<int, int> rng = {loc[i]-x-i, loc[i]+x-i};
		rng.first = intmod(rng.first, n), rng.second = intmod(rng.second+1, n);
		//cout << i << " " << rng.first << " " << rng.second << "\n";
		if(rng.first < rng.second)
		{
			ctr[rng.first]++, ctr[rng.second]--;
		}
		else cur++, ctr[rng.first]++, ctr[rng.second]--;
	}

	for(int i = 0;i < n;i++)
	{
		cur += ctr[i];
		if(cur == n) return true;
	}
	return false;
}

int main(void)
{
	scanf("%d", &n);
	for(int i = 0;i < n;i++)
	{
		scanf("%d", &A[i]);
		A[i]--;
		loc[A[i]] = i;
	}

	int L = 0, R = n-1, ans = n;
	while(L <= R)
	{
		int mid = (L+R)/2;
		if(f(mid))
		{
			ans = min(ans, mid);
			R = mid-1;
		}
		else L = mid+1;
	}

	reverse(A, A+n);
	for(int i = 0;i < n;i++) loc[A[i]] = i;

	L = 0, R = n-1;
	while(L <= R)
	{
		int mid = (L+R)/2;
		if(f(mid))
		{
			ans = min(ans, mid);
			R = mid-1;
		}
		else L = mid+1;
	}

	printf("%d\n", ans);
}