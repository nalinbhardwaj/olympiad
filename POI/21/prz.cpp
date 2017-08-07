#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = int(1e6)+5;

int c[maxn], x[maxn], y[maxn], ctr[maxn], dpmaxi[maxn], dpmini[maxn], ansmaxi[maxn], ansmini[maxn], prv[maxn];

int main(void)
{
	int n, k, m, l;
	scanf("%d%d", &n, &k);
	for(int i = 0;i < n;i++) scanf("%d", &c[i]);
	scanf("%d%d", &m, &l);
	for(int i = 0;i < m;i++) scanf("%d", &x[i]);
	for(int i = 0;i < l;i++) scanf("%d", &y[i]);

	for(int i = 0;i < m;i++)
	{
		if(i < m-1) prv[x[i]] = x[i+1];
		else prv[x[i]] = -1;
	}

	for(int i = 1;i <= k;i++) dpmini[i] = ansmini[i] = n+1, dpmaxi[i] = ansmaxi[i] = -1;

	for(int i = n-1;i >= 0;i--)
	{
		ansmini[c[i]] = min(ansmini[c[i]], dpmini[x[0]]);
		if(prv[c[i]] == -1) dpmini[c[i]] = min(dpmini[c[i]], i);
		else if(prv[c[i]]) dpmini[c[i]] = min(dpmini[c[i]], dpmini[prv[c[i]]]);
	}

	for(int i = 1;i <= k;i++) prv[i] = 0;

	for(int i = 0;i < l;i++)
	{
		if(i < l-1) prv[y[i]] = y[i+1];
		else prv[y[i]] = -1;
	}

	for(int i = 0;i < n;i++)
	{
		ansmaxi[c[i]] = max(ansmaxi[c[i]], dpmaxi[y[0]]);
		if(prv[c[i]] == -1) dpmaxi[c[i]] = max(dpmaxi[c[i]], i);
		else if(prv[c[i]]) dpmaxi[c[i]] = max(dpmaxi[c[i]], dpmaxi[prv[c[i]]]);
	}

	//for(int i = 1;i <= k;i++) cout << i << " " << ansmini[i] << " " << ansmaxi[i] << "\n";

	for(int i = 1;i <= k;i++)
	{
		if(ansmini[i] <= ansmaxi[i])
		{
			ctr[ansmini[i]]++, ctr[ansmaxi[i]+1]--;
		}
	}

	vector<int> res;
	int v = 0;
	for(int i = 0;i < n;i++)
	{
		v += ctr[i];
		if(v && c[i] == x[m-1]) res.push_back(i);
	}
	printf("%d\n", int(res.size()));
	for(int i = 0;i < int(res.size());i++) printf("%d ", res[i]+1);
	printf("\n");
}