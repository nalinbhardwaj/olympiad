#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> A;

inline int dist(int x, int y)
{
	return (A[x].first-A[y].first)*(A[x].first-A[y].first)+(A[x].second-A[y].second)*(A[x].second-A[y].second);
}

int main(void)
{
	int n;
	scanf("%d", &n);
	A.clear(); A.resize(n);
	for(int i = 0;i < n;i++) scanf("%d%d", &A[i].first, &A[i].second);

	vector<pair<int, pair<int, int>>> D;
	for(int i = 0;i < n;i++)
	{
		for(int j = i+1;j < n;j++)
		{
			if(i != j)
			{
				D.push_back({dist(i, j), {i, j}});
			}
		}
	}

	sort(D.rbegin(), D.rend());

	vector<vector<pair<int, int>>> val(n+1);
	for(int i = 0;i < n;i++) val[i].push_back({1, A[i].first*A[i].first+A[i].second*A[i].second}); 
	for(auto it: D)
	{
		//cout << it[0] << " " << it[1] << " " << it[2] << "\n";
		for(auto gt: val[it.second.second])
		{
			if(gt.second > it.first) val[it.second.first].push_back({gt.first+1, it.first});
		}
		sort(val[it.second.first].rbegin(), val[it.second.first].rend());
		for(int i = 1;i < int(val[it.second.first].size());i++)
		{
			if(val[it.second.first][i].second != val[it.second.first][i-1].second)
			{
				val[it.second.first][1] = val[it.second.first][i];
				val[it.second.first].resize(2);
				break;
			}
		}

		swap(it.second.first, it.second.second);

		for(auto gt: val[it.second.second])
		{
			if(gt.second > it.first) val[it.second.first].push_back({gt.first+1, it.first});
		}
		sort(val[it.second.first].rbegin(), val[it.second.first].rend());
		for(int i = 1;i < int(val[it.second.first].size());i++)
		{
			if(val[it.second.first][i].second != val[it.second.first][i-1].second)
			{
				val[it.second.first][1] = val[it.second.first][i];
				val[it.second.first].resize(2);
				break;
			}
		}
	}

	int res = 0;
	for(int i = 0;i < n;i++) res = max(res, val[i][0].first);
	printf("%d\n", res);
}