#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int maxn = int(1e5)+5, maxlog = 18, inf = int(1e9)+5;

int n, sz[maxn], T[maxn][maxlog], vis[maxn];
pair<int,int> H[maxn][maxlog];
vector<pair<int, int>> qry;
pair<pair<int, int>, pair<int, int>> val[maxn];
set<int> graph[maxn];

void dfs1(int node, int par)
{
	sz[node] = 1;
	for(auto it: graph[node])
	{
		if(it != par)
		{
			dfs1(it, node);
			sz[node] += sz[it];
		}
	}
}

int dfs2(int node, int par, int lim)
{
	for(auto it: graph[node])
	{
		if(sz[it] > lim/2 && it != par) return dfs2(it, node, lim);
	}
	return node;
}

void dfs3(int node, int par, int lev, int dist, int id, int centroid)
{
	H[node][lev] = {dist, id}, T[node][lev] = centroid;
	for(auto it: graph[node])
	{
		if(it != par) dfs3(it, node, lev, dist+1, id, centroid);
	}
}

void decompose(int node, int lev)
{
	dfs1(node, -1);
	int centroid = dfs2(node, -1, sz[node]);
	vis[centroid] = 1;
	//cout << centroid << " " << lev << "\n";

	H[centroid][lev] = {0, centroid}, T[centroid][lev] = centroid;
	for(auto it: graph[centroid]) dfs3(it, centroid, lev, 1, it, centroid);

	for(auto it: graph[centroid])
	{
		//cout << it << "\n";
		graph[it].erase(centroid);
		decompose(it, lev+1);
	}
}

void activate(int node)
{
	for(int i = 0;i < maxlog;i++)
	{
		pair<int, int> v = H[node][i];
		int centroid = T[node][i];
		if(centroid < 0) break;

		if(val[centroid].first.first < v.first)
		{
			if(val[centroid].first.second != v.second) val[centroid].second = val[centroid].first;
			val[centroid].first = v;
		}
		else if(val[centroid].first.second != v.second && val[centroid].second.first < v.first) val[centroid].second = v;

		//cout << node << " " << centroid << " " << val[centroid].first.first << " " << val[centroid].first.second << "\n";
	}
}

int calc(int node)
{
	int res = 0;
	for(int i = 0;i < maxlog;i++)
	{
		pair<int, int> v = H[node][i];
		int centroid = T[node][i];
		if(centroid < 0) break;

		if(val[centroid].first.second != v.second) res = max(res, val[centroid].first.first+v.first);
		else if(val[centroid].second.second != v.second) res = max(res, val[centroid].second.first+v.first);
	
		//cout << node << " " << v.first << " " << v.second << "  " << i << " " << centroid << " " << val[centroid].first.first << " " << val[centroid].first.second << " : " << val[centroid].second.first << " " << val[centroid].second.second << "\n";
	}

	res = max(res, val[node].first.first);

	return res;
}

int main(void)
{
	ifstream fin("newbarn.in");
	ofstream fout("newbarn.out");

	int q, x;
	fin >> q;
	string S;
	int cnt = 0;
	for(int i = 0;i < q;i++)
	{
		fin >> S >> x;
		x--;
		if(S[0] == 'B')
		{
			if(x >= 0)
			{
				graph[x].insert(cnt), graph[cnt].insert(x);
				//cout << x << " " << cnt << "\n";
			}
			cnt++;
		}
		qry.push_back({bool(S[0] == 'B'), ((S[0] == 'B')?(cnt-1):x)});
	}

	n = cnt;
	for(int i = 0;i < n;i++)
	{
		val[i] = {{-inf, -inf}, {-inf, -inf}};
		for(int j = 0;j < maxlog;j++) T[i][j] = -inf, H[i][j] = {-inf, -inf};
	}


	for(int i = 0;i < n;i++)
	{
		if(!vis[i]) decompose(i, 0);
	}

	for(auto it: qry)
	{
		if(it.first) activate(it.second);
		else fout << calc(it.second) << "\n";
	}
}