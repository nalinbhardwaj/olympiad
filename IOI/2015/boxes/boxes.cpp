#include <iostream>
#include <cstdio>
#include <vector>
#include "boxes.h"
using namespace std;
 
typedef long long int lli;
 
const int maxn = int(1e7)+5;
 
int n, k, l;
lli pref[maxn], suff[maxn];
 
long long delivery(int _N, int _K, int _L, int p[])
{
	n = _N, k = _K, l = _L;
	for(int i = 0;i < n;i++)
	{
		if(i < k) pref[i] = lli(p[i]);
		else pref[i] = lli(p[i])+pref[i-k]+lli(p[i-k]);
	}
 
	for(int i = n-1;i >= 0;i--)
	{
		if(i+k > n-1) suff[i] = lli(l-p[i]);
		else suff[i] = lli(l-p[i])+suff[i+k]+lli(l-p[i+k]);
	}
 
	lli res = suff[0]+min(p[0], l-p[0]);
	res = min(res, pref[n-1]+min(p[n-1], l-p[n-1]));
	for(int i = 0;i < n-1;i++)
	{
		lli c = pref[i]+suff[i+1];
		c += min(p[i], l-p[i])+min(p[i+1], l-p[i+1]);
		res = min(res, c);
	}
	return res;
}