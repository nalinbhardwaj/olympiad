#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int dist, t;
vector<int> val;
vector<int> memo;

int calculate(int d)
{
	if(memo[d] != -1)
		return memo[d];
	else
	{
		int tmp;
		if(val[0] < d)
			tmp = 1 + calculate(d-val[0]);
		else
			tmp = 10000000;
		for(int i = 1;val[i] <= d && i < int(val.size());i++)
		{
			tmp = min(tmp, 1 + calculate(d-val[i]));
		}
		memo[d] = tmp;
		return tmp;
	}
}

int main(void)
{
	int dist, t;
	scanf("%d", &dist);
	scanf("%d", &t);
	val.resize(t);
	for(int i = 0;i < t;i++)
		scanf("%d", &val[i]);
	sort(val.begin(), val.end());
	memo.resize(dist+1, -1);
	memo[0] = 0;
	int ans = calculate(dist);
	if(ans >= 10000000)
		printf("Roberta acknowledges defeat.\n");
	else
		printf("Roberta wins in %d strokes.\n", calculate(dist));
}