#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

vector<int> A, P, DP[2];

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t--) {
	int n, k, w;
	scanf("%d%d%d", &n, &k, &w);
	A.clear(); A.resize(n+w+3);
	P.clear(); P.resize(n+w+3);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d", &A[i]);
		P[i] = A[i]+P[i-1];
	}
	for(int i = 1;i <= n+w;i++)
	{
		P[i] = A[i]+P[i-1];
	}

	DP[0].clear(); DP[0].resize(n+w+3);
	DP[1].clear(); DP[1].resize(n+w+3);
	for(int m = 1;m <= k;m++)
	{
		int maxi = 0;
		set<pair<int, int>> S;
		for(int i = n+w;i > 0;i--)
		{
			DP[1][i] = max(0, maxi);
			if(!S.empty()) DP[1][i] = max(DP[1][i], S.rbegin()->first-P[i-1]);
			if(i <= n)
			{
				S.erase({DP[0][i+w]+P[i+w-1], i+w});
				maxi = max(DP[0][i+w]+P[i+w-1]-P[i-1], maxi);
			}
			S.insert({DP[0][i]+P[i-1], i});
			//cout << i << " " << m << " " << DP[1][i] << "\n";
		}
		DP[0] = DP[1];
		DP[1].clear(); DP[1].resize(n+k+2);
	}
	printf("%d\n", DP[0][1]); }
}