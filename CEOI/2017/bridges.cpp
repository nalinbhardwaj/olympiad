// Building bridges

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e5)+5, inf = lli(1e18)+5;

lli n, h[maxn], hs[maxn], w[maxn], dp[maxn];

struct line {
	lli m, c;
	line(lli _m = 0.0, lli _c = 0.0)
	{
		m = _m, c = _c;
	}
};

inline bool cmp(line a, line b)
{
	if(a.m == b.m) return (a.c < b.c);
	else return (a.m > b.m);
}

struct cht {
	vector<line> st;

	inline double lliersect(line a, line b)
	{
		return double(b.c-a.c)/(a.m-b.m);
	}

	void insert(line a)
	{
		while(lli(st.size()) > 1 && lliersect(*(st.end()-2), st.back()) > lliersect(*(st.end()-2), a)) st.pop_back();
		st.push_back(a);
	}

	void prllier()
	{
		for(auto it: st) cout << it.m << " " << it.c << "\n"; 
	}

	lli qry(double x)
	{
		lli L = 0, R = lli(st.size())-1;
		while(L < R)
		{
			lli mid = (L+R)/2;
			//cout << "inqrymid report: " << mid << " " << lliersect(st[mid], st[mid+1]) << "\n";
			if(lliersect(st[mid], st[mid+1]) <= x) L = mid+1;
			else R = mid;
		}
		//cout << "inqry " << x << " " << L << "\n";
		return st[L].m*x+st[L].c;
	}
} ds[4*maxn];

inline int left(int node) { return (node<<1); }
inline int right(int node) { return (node<<1)+1; }

lli qry(int node, int L, int R, int idx)
{
	if(L == R) return inf;
	else
	{
		if(idx <= (L+R)/2) return qry(left(node), L, (L+R)/2, idx);
		else return min(ds[left(node)].qry(h[idx]), qry(right(node), (L+R)/2+1, R, idx));
	}
}

void solve(int node, int L, int R)
{
	if(L == R)
	{
		if(L == 1) dp[L] = 0;
		else dp[L] = qry(1, 1, n, L)+hs[L]+w[L-1];
		ds[node].insert({-2*h[L], hs[L]+dp[L]-w[L]});
		//cout << L << " " << dp[L] << "\n";
	}
	else
	{
		solve(left(node), L, (L+R)/2);
		solve(right(node), (L+R)/2+1, R);

		vector<line> a;
		for(lli i = L;i <= R;i++)
		{
			a.push_back({-2*h[i], hs[i]+dp[i]-w[i]});
		}
		sort(a.begin(), a.end(), cmp);

		vector<line> b;
		for(auto it: a)
		{
			if(b.empty() || b.back().m != it.m) b.push_back(it);
		}

		for(auto it: b) ds[node].insert(it);
		//cout << "node " << L << " " << R << "\n"; ds[node].prllier();
	}
}

int main(void)
{
	scanf("%lld", &n);
	for(lli i = 1;i <= n;i++)
	{
		scanf("%lld", &h[i]);
		hs[i] = h[i]*h[i];
	}
	for(lli i = 1;i <= n;i++)
	{
		scanf("%lld", &w[i]);
		w[i] += w[i-1];
	}

	solve(1, 1, n);

	//for(int i = 1;i <= n;i++) printf("%d %lld\n", i, dp[i]);
	printf("%lld\n", dp[n]);
}