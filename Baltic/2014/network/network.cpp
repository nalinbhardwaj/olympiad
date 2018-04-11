#include <iostream>
#include <cstdio>
#include <vector>
#include "network.h"
using namespace std;

const int maxn = int(1e3)+5;

int D[maxn];

void findRoute (int n, int a, int b)
{
	for(int i = 1;i <= n;i++)
	{
		if(i != b) D[i] = ping(b, i)+1;
		//cout << i << " " << D[0][i] << " " << D[1][i] << "\n";
	}

	int cur = a;
	while(cur != b)
	{
		for(int i = 1;i <= n;i++)
		{
			if(D[i] == D[cur]-1 && ping(cur, i) == 0)
			{
				travelTo(i);
				cur = i;
				break;
			}
		}
	}
}
