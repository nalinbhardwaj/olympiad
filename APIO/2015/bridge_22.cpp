#include <bits/stdc++.h>
using namespace std;
 
typedef long long int lli;
 
const lli maxn = lli(1e6)+5, inf = lli(1e15);
 
lli solve1(vector<lli>& B)
{
	lli res = 0;
 
    sort(B.begin(), B.end());
 
    lli mid = B[(lli(B.size())-1)/2];
 
    //cout << mid << "\n";
    for(auto it: B) res += llabs(it-mid);
    return res;
}
 
lli solve2(vector<pair<lli, lli>> A)
{
    vector<lli> tmp;
	for(lli i = 0;i < lli(A.size());i++)
    {
        if(A[i].first > A[i].second) swap(A[i].first, A[i].second);
        tmp.push_back(A[i].first), tmp.push_back(A[i].second);
    }
 
    sort(A.begin(), A.end());
 
    lli res = inf;
    for(auto it: tmp)
    {
        lli cur = 0;
        vector<lli> other;
        for(lli i = 0;i < lli(A.size());i++)
        {
            if(A[i].first <= it) cur += abs(it-A[i].first), cur += abs(it-A[i].second);
            else other.push_back(A[i].first), other.push_back(A[i].second);
        }
        cur += solve1(other);
        //cout << it << " " << cur << "\n";
        res = min(res, cur);
    }
    return res;
}
 
int main(void)
{
    lli n, k, res = 0;
    scanf("%lld%lld", &k, &n);
    vector<pair<lli, lli>> A;
    for(lli i = 0;i < n;i++)
    {
        string s, t;
        lli a, b;
        cin >> s >> a >> t >> b;
        if(s == t) res += llabs(b-a);
        else
        {
            A.push_back({a, b});
            res++;
        }
    }
    
    if(k-1) res += solve2(A);
    else
    {
        vector<lli> tmp;
        for(auto it: A) tmp.push_back(it.first), tmp.push_back(it.second);
        res += solve1(tmp);
    }
    printf("%lld\n", res);
}