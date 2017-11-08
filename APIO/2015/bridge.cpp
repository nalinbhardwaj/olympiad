#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e5)+5, inf = lli(1e17)+5;

lli n, S[maxn], T[maxn], pref[maxn], suff[maxn], psum, asum;
vector<pair<lli, lli>> A;
multiset<lli> peeche, aage;

inline bool cmp(pair<lli, lli>& a, pair<lli, lli>& b)
{
	return (a.first+a.second < b.first+b.second);
}

void daalo(lli v)
{
	if(peeche.empty())
	{
		peeche.insert(v), psum += v;
		return;
	}

	if(v < *peeche.rbegin()) peeche.insert(v), psum += v;
	else aage.insert(v), asum += v;

	while(lli(peeche.size()) < lli(aage.size()))
	{
		lli x = *aage.begin();
		aage.erase(aage.begin()), asum -= x;
		peeche.insert(x), psum += x;
	}

	while(lli(aage.size()) < lli(peeche.size()))
	{
		lli x = *peeche.rbegin();
		peeche.erase(peeche.find(x)), psum -= x;
		aage.insert(x), asum += x;
	}
}

void solve()
{
	n = lli(A.size());
	sort(A.begin(), A.end(), cmp);

	peeche.clear(), aage.clear();
	psum = asum = 0;
	for(lli i = 0;i < n;i++)
	{
		daalo(A[i].first), daalo(A[i].second);
		lli tmp = *peeche.rbegin();
		pref[i] = lli(peeche.size())*tmp-psum+asum-lli(aage.size())*tmp;
		//cout << A[i].first << " " << A[i].second << " " << pref[i] << " " << tmp << "\n";
	}

	peeche.clear(), aage.clear();
	psum = asum = 0;
	for(lli i = n-1;i >= 0;i--)
	{
		daalo(A[i].first), daalo(A[i].second);
		lli tmp = *peeche.rbegin();
		suff[i] = lli(peeche.size())*tmp-psum+asum-lli(aage.size())*tmp;
	}
}

int main(void)
{
	lli k, res = 0;
	string p, q;
	scanf("%lld%lld", &k, &n);

	for(lli i = 0;i < n;i++)
	{
		cin >> p >> S[i] >> q >> T[i];
		if(p == q) res += abs(S[i]-T[i]);
		else
		{
			res++;
			A.push_back({S[i], T[i]});
		}
	}

	if(!A.empty())
	{
		solve();
	
		if(k == 1) res += pref[n-1];
		else
		{
			lli ans = inf;
			for(lli i = 0;i < n-1;i++) ans = min(ans, pref[i]+suff[i+1]);
			res += ans;
		}
	}
	
	printf("%lld\n", res);
}