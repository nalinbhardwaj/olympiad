#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
using namespace std;

const int maxn = int(2e5)+5;

int q, A[maxn], res[maxn], P[maxn], sz[maxn], nhi[maxn], kahan[maxn];
vector<pair<int, int>> upd[maxn];
vector<pair<int, pair<int, int>>> edge;
vector<pair<int, int>> graph[maxn];
set<int> unanswered;

inline int root(int node)
{
	if(P[node] == node) return node;
	else
	{
		P[node] = root(P[node]);
		return P[node];
	}
}

void dsu(int x, int y)
{
	x = root(x), y = root(y);
	if(sz[x] < sz[y]) swap(x, y);
	P[y] = x;
	sz[x] += sz[y];
}

int next(int idx)
{
	auto ret = unanswered.lower_bound(idx);
	if(ret == unanswered.end()) return q;
	else return *ret;
}

int nextchange(int node, int idx)
{
	auto ret = lower_bound(upd[node].begin()+kahan[node], upd[node].end(), make_pair(idx+1, -1));
	kahan[node] = int(ret-upd[node].begin());
	if(ret == upd[node].end()) return q;
	else return ret->first;
}

int findcol(int node, int idx)
{
	int fidx = int(lower_bound(upd[node].begin(), upd[node].end(), make_pair(idx+1, -1))-upd[node].begin())-1;
	if(fidx < 0 || fidx >= int(upd[node].size())) return A[node];
	else return upd[node][fidx].second;
}

int main(void)
{
	ifstream fin("grass.in");
	ofstream fout("grass.out");
	int n, m, k, a, b, l, node, color;
	fin >> n >> m >> k >> q;
	edge.clear(); edge.resize(m);
	for(int i = 0;i < m;i++)
	{
		fin >> a >> b >> l;
		a--, b--;
		if(a > b) swap(a, b);
		graph[a].push_back({b, l});
		graph[b].push_back({a, l});
		edge[i] = {l, {a, b}};
	}

	for(int i = 0;i < n;i++)
	{
		fin >> A[i];
		P[i] = i, sz[i] = 1;
	}

	for(int i = 0;i < q;i++)
	{
		fin >> node >> color;
		res[i] = -1; unanswered.insert(i);
		node--;
		upd[node].push_back({i, color});
	}
	for(int i = 0;i < n;i++) sort(upd[i].begin(), upd[i].end());

	sort(edge.begin(), edge.end());
	int tmp = 0;
	for(auto it: edge)
	{
		if(root(it.second.first) != root(it.second.second))
		{
			nhi[tmp++] = 0;
			dsu(it.second.first, it.second.second);	
		}
		else nhi[tmp++] = 1;
	}
	tmp = 0;
	for(auto it: edge)
	{
		if(nhi[tmp++]) continue;
		int u = it.second.first, v = it.second.second, qryptr = 0;
		kahan[u] = kahan[v] = 0;

		while(qryptr < q)
		{
			qryptr = next(qryptr);
			if(qryptr == q) break;
			//cout << qryptr << " " << u+1 << " " << v+1 << " " << findcol(u, qryptr) << " " << findcol(v, qryptr) << "\n";
			if(findcol(u, qryptr) == findcol(v, qryptr))
			{
				int a = nextchange(u, qryptr), b = nextchange(v, qryptr);
				//cout << a << " " << b << "\n";
				qryptr = min(a, b);
			}
			else
			{
				//cout << "\n";
				res[qryptr] = it.first;
				unanswered.erase(qryptr);
			}
		}
	}
	for(int i = 0;i < q;i++) fout << res[i] << "\n";
}