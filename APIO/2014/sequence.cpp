// APIO 2014 Problem 2 - Split the sequence

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
 
typedef long long int lli;
typedef long double dbl;
 
const lli maxn = lli(1e5)+5, maxk = 205;
 
int A[maxn], dp2[maxn][maxk];
lli p[maxn], dp[maxn][2];
 
struct line {
	int id;
	dbl m, c;
	line(dbl _m = 0.00, dbl _c = 0.00, int _id = -1)
	{
		m = _m, c = _c, id = _id;
	}
};
 
struct CHT {
	int sz = 0, ptr = 0;
	line st[maxn];
 
	inline dbl intersect(line a, line b)
	{
		return (b.c-a.c)/(a.m-b.m);
	}
 
	inline void clr()
	{
		ptr = sz = 0;
	}
 
	void printer()
	{
		cout << sz << " " << ptr << "\n";
		for(int i = 0;i < sz;i++)
		{
			cout << i << " " << st[i].id << " ";
			if(i < sz-1) cout << intersect(st[i], st[i+1]) << " ";
			cout << "\n";
		}
		
		cout << "\n";
	}
 
	void insert(line a)
	{
		while(sz > 1)
		{
			if(intersect(st[sz-1], a) <= intersect(st[sz-2], st[sz-1])) sz--;
			else break;
		}
		ptr = min(ptr, sz);
		st[sz++] = a;
	}
 
	pair<lli, int> qry(lli x)
	{
		if(!sz) return {0, -1};
		while(ptr < sz-1 && intersect(st[ptr], st[ptr+1]) <= x) ptr++;
		return {lli(st[ptr].m*x+st[ptr].c), st[ptr].id};
	}
} C;
 
int main(void)
{
	int n, k;
	scanf("%d%d", &n, &k);
	vector<int> zr;
	for(int i = 1;i <= n;i++)
	{
		scanf("%d", &A[i]);
		if(A[i] == 0) zr.push_back(i);
	}
 
	for(int i = 1;i <= n;i++) p[i] = lli(A[i])+p[i-1];
 
	for(int i = 0;i <= n;i++) dp[i][0] = 0, dp2[i][0] = -1;
 
	for(int kk = 1;kk <= k;kk++)
	{
		C.clr();
		for(int i = 1;i <= n;i++)
		{
			//C.printer();
			pair<lli, int> tmp = ((i >= kk-1)?(C.qry(p[i])):(make_pair(0ll, -1)));
			dp[i][kk%2] = tmp.first, dp2[i][kk] = tmp.second;
			if(A[i] && i >= kk-1) C.insert({dbl(p[i]), dbl(dp[i][(kk-1)%2]-p[i]*p[i]), i});
		}
	}
	printf("%lld\n", dp[n][k%2]);
 
	int idx = n, ptr = 0;
	for(int kk = k;kk > 0;kk--)
	{
		if(dp2[idx][kk] == -1) printf("%d ", zr[ptr++]);
		else
		{
			printf("%d ", dp2[idx][kk]);
			idx = dp2[idx][kk];
		}
	}
	printf("\n");
}