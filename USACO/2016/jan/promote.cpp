#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const int maxn = int(2e5)+10;

int BIT[maxn+1], start[maxn/2], en[maxn/2], P[maxn/2], res[maxn/2];
vector<int> dis, graph[maxn/2];

void upd(int idx)
{
	while(idx <= maxn)
	{
		BIT[idx]++;
		idx += (idx&-idx);
	}
}

int qry(int idx)
{
	int res = 0;
	while(idx)
	{
		res += BIT[idx];
		idx -= (idx&-idx);
	}
	return res;
}

void dfs(int node)
{
	start[node] = int(dis.size());
	dis.push_back(node);
	for(auto it: graph[node])
	{
		dfs(it);
	}
	en[node] = int(dis.size())-1;
}

int main(void)
{
	ifstream fin("promote.in");
	ofstream fout("promote.out");
	int n, u;
	fin >> n;
	vector<pair<int, int>> A;
	for(int i = 0;i < n;i++)
	{
		fin >> P[i];
		A.push_back({P[i], i});
	}
	for(int i = 1;i < n;i++)
	{
		fin >> u;
		u--;
		graph[u].push_back(i);
	}

	dis.push_back(-1);
	dfs(0);
	sort(A.rbegin(), A.rend());

	for(auto it: A)
	{
		res[it.second] = qry(en[it.second])-qry(start[it.second]);
		upd(start[it.second]);
	}

	for(int i = 0;i < n;i++) fout << res[i] << "\n";
}