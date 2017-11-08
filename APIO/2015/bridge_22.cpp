#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e5)+5;

lli S[maxn], T[maxn];

int main(void)
{
	lli k, n, res = 0;
	string p, q;
	scanf("%lld%lld", &k, &n);
	vector<lli> A;

	for(lli i = 0;i < n;i++)
	{
		cin >> p >> S[i] >> q >> T[i];
		if(p == q) res += abs(S[i]-T[i]);
		else
		{
			res++;
			A.push_back(S[i]), A.push_back(T[i]);
		}
	}
	sort(A.begin(), A.end());

	if(!A.empty())
	{
		lli x = A[lli(A.size())/2];
		for(auto it: A) res += abs(it-x);
	}

	printf("%lld\n", res);
}