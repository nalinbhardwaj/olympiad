// Baltic Olympiad in Informatics 2016 Day 1 Problem 1

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
 
typedef long long int lli;
 
const lli maxn = lli(5e3)+5, inf = lli(5e14)+5;
 
lli n, D[maxn];
vector<lli> graph[maxn];
 
lli solve(lli node)
{
	queue<pair<lli, lli>> Q;
	for(lli i = 0;i < n;i++) D[i] = inf;
	D[node] = 0;
	Q.push({0, node});
	while(!Q.empty())
	{
		pair<lli, lli> top = Q.front();
		Q.pop();
 
		for(auto it: graph[top.second])
		{
			if(D[it] == inf)
			{
				D[it] = 1+D[top.second];
				Q.push({D[it], it});
			}
		}
	}
 
	lli ret = n;
	for(lli i = 0;i < n;i++)
	{
		ret += D[i];
		if(D[i] == inf) return inf;
	}
	//cout << "\n" << node << " " << " " << ret << "\n";
	return ret;
}
 
int main(void)
{
	lli p, x;
	scanf("%lld", &n);
	for(lli i = 0;i < n;i++)
	{
		scanf("%lld", &x);
		for(lli j = 0;j < x;j++)
		{
			scanf("%lld", &p);
			p--;
			graph[p].push_back(i);
		}
	}
 
	lli res = inf;
	for(lli i = 0;i < n;i++) res = min(res, solve(i));
	printf("%lld\n", res);
}
