#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int maxn = int(3e3)+5;

int n, A[maxn][4];
pair<int, int> loc[maxn];
vector<pair<int, int> > start[maxn];

void solve(int type)
{
	set<pair<int, int> > active;
	for(int i = 0;i < n;i++)
	{
		start[i].clear();
		if(type) loc[i].second = -1;
		else loc[i].first = -1;
	}
	for(int i = 0;i < n;i++)
	{
		start[A[i][type]].push_back(make_pair(A[i][type+2], i));
	}

	for(int x = 0;x < n;x++)
	{
		for(vector<pair<int, int> >::iterator it = start[x].begin();it != start[x].end();it++) active.insert(*it);
		if(!active.empty())
		{
			while(!active.empty() && active.begin()->first < x) active.erase(active.begin());
			pair<int, int> top = *active.begin();
			active.erase(active.begin());
			if(type) loc[top.second].second = x;
			else loc[top.second].first = x;
		}
	}
}

void rekt()
{
	printf("NIE\n");
	exit(0);
}

int main(void)
{
	scanf("%d", &n);
	for(int i = 0;i < n;i++)
	{
		scanf("%d%d%d%d", &A[i][0], &A[i][1], &A[i][2], &A[i][3]);
		A[i][0]--, A[i][1]--, A[i][2]--, A[i][3]--;
	}

	solve(0); solve(1);

	for(int i = 0;i < n;i++)
	{
		if(loc[i].first == -1 || loc[i].second == -1) rekt();
	}
	for(int i = 0;i < n;i++)
	{
		printf("%d %d\n", loc[i].first+1, loc[i].second+1);
	}
}