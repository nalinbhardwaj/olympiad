#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
vector<int> A, B;
int memo[3010][105][105][3];

int DP(int x, int a, int b, bool pr)
{
	if(x == n && a > b) return 0;
	if(memo[x][a][b][pr] > 0)
	{
		return memo[x][a][b][pr];
	}
	int res = 0;
	if(x == n)
	{
		if(!pr && a <= m)
		{
			res = max(res, DP(x, a+1, b, 1)+B[a]);
			//cout << B[a] << "\n";
		}
		if(b) res = max(res, DP(x, a, b-1, 0));
	}
	else if(a > b)
	{
		if(!pr) res = max(res, DP(x+1, a, b, 1)+A[x]);
		res = max(res,DP(x+1, a, b, 0));
	}
	else
	{
		if(!pr) res = max(res, DP(x+1, a, b, 1)+A[x]);
		if(!pr && a <= m) res = max(res, DP(x, a+1, b, 1)+B[a]);
		if(b) res = max(res,max(DP(x+1, a, b, 0), DP(x, a, b-1, 0)));
	}
	//cout << x << " " << a << " " << b << " " << pr << " " << res << "\n";
	memo[x][a][b][pr] = res;
	return res;
}

int main(void)
{
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);
	A.clear(); A.resize(n);
	for(int i = 0;i < n;i++) scanf("%d", &A[i]);
	scanf("%d", &m);
	B.clear(); B.resize(m+5);
	for(int i = 1;i <= m;i++) scanf("%d", &B[i]);
	sort(B.rbegin()+1, B.rend()-1);
	//memo.clear();
	//memo.resize(n+5, vector<vector<vector<int> > >(m+5, vector<vector<int> >(m+5, vector<int>(3, -1))));
	printf("%d\n", DP(0, 1, m, 0));
}