#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int inf = 1707050917;

int main(void)
{
	int n;
	scanf("%d", &n);
	vector<int> A(n);
	for(int i = 0;i < n;i++) scanf("%d", &A[i]);
	sort(A.begin(), A.end());
	vector<int> D(A[0], inf);
	D[0] = 0;
	set<pair<int, int> > Q;
	Q.insert(make_pair(0, D[0]));

	while(!Q.empty())
	{
		pair<int, int> top = *Q.begin();
		Q.erase(Q.begin());

		for(int i = 1;i < n;i++)
		{
			if(D[(top.second+A[i])%A[0]] > D[top.second]+A[i])
			{
				if(D[(top.second+A[i])%A[0]] != inf) Q.erase(make_pair(D[(top.second+A[i])%A[0]], (top.second+A[i])%A[0]));
				D[(top.second+A[i])%A[0]] = D[top.second]+A[i];
				Q.insert(make_pair(D[(top.second+A[i])%A[0]], (top.second+A[i])%A[0]));
			}
		}
	}

	int k, v;
	scanf("%d", &k);
	while(k--)
	{
		scanf("%d", &v);
		if(v >= D[v%A[0]]) printf("TAK\n");
		else printf("NIE\n");
	}
}