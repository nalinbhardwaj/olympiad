#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e7)+5;

bool P[maxn];
lli res[maxn];

lli powr(lli a, lli b)
{
	if(b == 0) return 1;
	else if(b == 1) return a;
	else
	{
		lli res = powr(a, b/2);
		res *= res;
		if(b%2) res *= a;
		return res;
	}
}

void init()
{
	//res[1] = 1;
	int tmpr, tmp, ctr;
	for(int i = 2;i < maxn;i++)
	{
		if(P[i] == 0)
		{
			res[i] = i+1;
			for(int j = 2*i;j < maxn;j += i)
			{
				if(P[j] == 0)
				{
					res[j] = 1; P[j] = i;
				}
				tmpr = j, tmp = i, ctr = 0;
				while(tmpr%tmp == 0)
				{
					tmpr /= tmp;
					ctr++;
				}
				res[j] *= ((powr(i, ctr+1)-1)/(i-1));
			}
		}
		res[i] -= i;
		//cout << i << " " << res[i] << "\n";
	}

	for(lli i = 1;i < maxn;i++)
	{
		res[i] = abs(i-res[i]);
		res[i] += res[i-1];
	}
}

int main(void)
{
	init();
	lli a, b;
	scanf("%lld%lld", &a, &b);
	printf("%lld\n", res[b]-res[a-1]);
}