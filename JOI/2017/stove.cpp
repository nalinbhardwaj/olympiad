#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = int(1e5)+5;

int T[maxn];

int main(void)
{
	int n, k;
	scanf("%d%d", &n, &k);
	k--;
	for(int i = 0;i < n;i++) scanf("%d", &T[i]);

	int res = T[n-1]-T[0]+1;
	vector<int> A;
	for(int i = 0;i < n-1;i++) A.push_back(T[i+1]-T[i]-1);
	sort(A.rbegin(), A.rend());
	for(int i = 0;i < k;i++) res -= A[i];
	printf("%d\n", res);
}