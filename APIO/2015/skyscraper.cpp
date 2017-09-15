#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

const int inf = int(1e9)+5, maxn = int(3e4)+5;

int B[maxn], P[maxn], D[maxn][2];
vector<int> graph[maxn], doge[maxn];
set<int> from[maxn];

// 0 => doge
// 1 => skyscraper

int main(void)
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++)
	{
		scanf("%d%d", &B[i], &P[i]), D[i][0] = inf;
		doge[B[i]].push_back(i);
		from[B[i]].insert(P[i]);
	}
	for(int i = 0;i < n;i++) D[i][1] = inf;

	set<pair<int, pair<int, int>>> Q;
	D[0][0] = 0;
	Q.insert({0, {0, 0}});

	while(!Q.empty())
	{
		pair<int, pair<int, int>> top = *Q.begin();
		Q.erase(Q.begin());
		//cout << top.second << "\n";
 
		if(top.second.second)
		{
			for(auto it: doge[top.second.first])
			{
				if(top.first < D[it][0])
				{
					if(D[it][0] != inf) Q.erase({D[it][0], {it, 0}});
					D[it][0] = top.first;
					Q.insert({D[it][0], {it, 0}});
				}
			}
		}
		else
		{
			for(auto it: graph[top.second.first])
			{
				if(top.first+it.second < D[it.first][1])
				{
					if(D[it.first][1] != inf) Q.erase({D[it.first][1], {it.first, 1}});
					D[it.first][1] = top.first+it.second;
					Q.insert({D[it.first][1], {it.first, 1}});
				}
			}
		}
	}

	printf("%d\n", (D[1][0] >= inf)?-1:D[1][0]);
}