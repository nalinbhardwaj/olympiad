#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi graph;
vi memo;

int dp(int i)
{
	if(memo[i] != -1)
		return memo[i];
	else
	{
		int tmp = 0;
		for(vi::iterator it = graph[i].begin();it != graph[i].end();it++)
		{
			tmp += dp(*it);
		}
		memo[i] = tmp;
		return tmp;
	}	
}

int main(void)
{
	int n, x, y;
	scanf("%d", &n);
	graph.clear(); graph.resize(n);
	memo.resize(n, -1);
	memo[0] = 1;
	scanf("%d%d", &x, &y);
	while(x != 0 && y != 0)
	{
		graph[y-1].push_back(x-1);
		scanf("%d%d", &x, &y);
	}

	int ans = dp(n-1);
	printf("%d\n", ans);
}