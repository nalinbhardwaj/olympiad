#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
const int maxn = int(2e3)+5, inf = int(1e9)+5;
 
int n, p, q, A[maxn], nex[maxn][2], memo[maxn][maxn];
 
bool f(int w)
{
	for(int idx = n-1;idx >= 0;idx--)
	{
		nex[idx][0] = int(lower_bound(A, A+n, A[idx]+w)-A);
		nex[idx][1] = int(lower_bound(A, A+n, A[idx]+min(inf, 2*w))-A);
		for(int pp = 0;pp <= p;pp++)
		{
			memo[idx][pp] = inf;
			if(pp) memo[idx][pp] = min(memo[idx][pp], memo[nex[idx][0]][pp-1]);
			memo[idx][pp] = min(memo[idx][pp], memo[nex[idx][1]][pp]+1);
		}
	}
	//cout << w << " " << memo[0][p] << "\n";
 
	return (memo[0][p] <= q);
}
 
int main(void)
{
	scanf("%d%d%d", &n, &p, &q);
	p = min(p, n), q = min(q, n);
	for(int i = 0;i < n;i++) scanf("%d", &A[i]);
	sort(A, A+n);
 
	int L = 0, R = inf, ans = inf+5;
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
