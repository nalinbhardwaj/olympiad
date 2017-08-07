// Day 1, Problem 3 - The Clever Typist

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>
using namespace std;

bool D[int(1e6)][7];
int pow10[8];

pair<int, int> op(int type, pair<int, int> cur)
{
	//cout << cur.first << " " << cur.second << " " << type << "\n";
	if(type == 0)
	{
		int dig = int(cur.first/pow10[5]);
		int v = int(cur.first/pow10[5-cur.second]);
		v %= 10;
		//cout << dig << " " << v << "\n";
		cur.first -= dig*pow10[5]+v*pow10[5-cur.second];
		cur.first += v*pow10[5]+dig*pow10[5-cur.second];
	}
	else if(type == 1)
	{	
		int dig = cur.first%10;
		int v = int(cur.first/pow10[5-cur.second]);
		v %= 10;
		cur.first -= dig+v*pow10[5-cur.second];
		cur.first += dig*pow10[5-cur.second]+v;
	}
	else if(type == 2)
	{
		int dig = int(cur.first/pow10[5-cur.second]);
		dig %= 10;
		if(dig != 9) cur.first += pow10[5-cur.second];
	}
	else if(type == 3)
	{
		int dig = int(cur.first/pow10[5-cur.second]);
		dig %= 10;
		if(dig) cur.first -= pow10[5-cur.second];
	}
	else if(type == 4)
	{
		if(cur.second != 5) cur.second++;
	}
	else
	{
		if(cur.second) cur.second--;
	}
	//cout << cur.first << " " << cur.second << "\n";
	return cur;
}

int main(void)
{
	int S, E;
	scanf("%d%d", &S, &E);
	memset(D, false, sizeof(D));

	pow10[0] = 1;
	for(int i = 1;i < 8;i++) pow10[i] = 10*pow10[i-1];

	queue<pair<pair<int, int>, int>> Q;
	Q.push({{S, 0}, 0});
	D[S][0] = 1;
	if(S == E)
	{
		printf("0\n");
		return 0;
	}
	pair<int, int> tmp;
	while(!Q.empty())
	{
		pair<pair<int, int>, int> top = Q.front();
		Q.pop();

		for(int i = 0;i < 6;i++)
		{
			tmp = op(i, top.first);
			if(tmp.first == E)
			{
				printf("%d\n", top.second+1);
				return 0;
			}
			if(!D[tmp.first][tmp.second])
			{
				Q.push({tmp, top.second+1});
				D[tmp.first][tmp.second] = 1;
			}
		}
	}
}