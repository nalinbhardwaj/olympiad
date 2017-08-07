#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int A[20], B[21];
pair<int, int> al[(1<<20)];

int main(void)
{
	int n, S, sz1 = 0, sz2 = 0;
	scanf("%d", &n);
	for(int i = 0;i < n/2;i++)
	{
		scanf("%d", &A[i]);
	}
	for(int i = n/2;i < n;i++)
	{
		scanf("%d", &B[i-n/2]);
	}
	scanf("%d", &S);
	sz1 = n/2; sz2 = n-n/2;
	int ctr = 0;
	for(int mask = 0;mask < (1<<sz1);mask++)
	{
		int tmp = 0;
		for(int i = 0;i < sz1;i++)
		{
			if(mask&(1<<i)) tmp += A[i];
		}
		al[ctr++] = make_pair(tmp, mask);
		//cout << tmp << " " << mask << "\n";
	}
	sort(al, al+(1<<sz1));

	for(int mask = 0;mask < (1<<sz2);mask++)
	{
		int tmp = 0;
		for(int i = 0;i < sz2;i++)
		{
			if(mask&(1<<i)) tmp += B[i];
		}
		if(lower_bound(al, al+(1<<sz1), make_pair(S-tmp, -1))->first == S-tmp)
		{
			int other = lower_bound(al, al+(1<<sz1), make_pair(S-tmp, -1))->second;
			//cout << mask << " " << other << "\n";
			for(int i = 0;i < sz1;i++) printf("%d", bool(other&(1<<i)));
			for(int i = 0;i < sz2;i++) printf("%d", bool(mask&(1<<i)));
			printf("\n");
			return 0;
		}
	}
}