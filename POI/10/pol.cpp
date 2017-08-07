#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int maxn = 105, maxq = int(1e4)+5, inf = int(1e9)+5;

int n, res[maxq] = {inf}, k[maxn];
vector<pair<int, int> > graph[maxn], cur[maxn];
vector<pair<int, pair<int, int> > > qry[maxn];

void dijkstra(int node)
{
	//cout << node << "\n";
	multiset<int> D[maxn];
	D[node].insert(0);
	multiset<pair<int, int> > Q;
	Q.insert(make_pair(0, node));

	while(!Q.empty())
	{
		pair<int, int> top = *Q.begin();
		Q.erase(Q.begin());
		//cout << top.first << " " << top.second << "\n";

		for(vector<pair<int, int> >::iterator it = graph[top.second].begin();it != graph[top.second].end();it++)
		{
			int dist = it->second+top.first, u = it->first, daaldo = 0;
			//cout << dist << " " << u << " " << *D[u].rbegin() << " " << k[node] << "\n";
			if(int(D[u].size()) < k[node]) daaldo = 1;
			else if(*D[u].rbegin() > dist)
			{
				daaldo = 1;
				Q.erase(Q.find(make_pair(*D[u].rbegin(), u)));
				D[u].erase(D[u].find(*D[u].rbegin()));
			}
			if(daaldo)
			{
				D[u].insert(dist);
				Q.insert(make_pair(dist, u));
			}
		}
	}

	for(vector<pair<int, pair<int, int> > >::iterator it = qry[node].begin();it != qry[node].end();it++)
	{
		cur[it->first].push_back(it->second);
	}

	for(int i = 0;i < n;i++)
	{
		if(cur[i].empty()) continue;
		sort(cur[i].begin(), cur[i].end());
		int ptr = 0, tmp = 0;
		for(multiset<int>::iterator it = D[i].begin();it != D[i].end();it++)
		{
			//cout << tmp << " " << ptr << "\n";
			while(cur[i][ptr].first == tmp)
			{
				//cout << ptr << "\n";
				res[cur[i][ptr].second] = *it;
				ptr++;
				if(ptr == int(cur[i].size())) break;
			}
			tmp++;
			if(ptr == int(cur[i].size())) break;
		}
		cur[i].clear();
	}
}

int main(void)
{
	int m, q, u, v, w, kk;
	scanf("%d%d", &n, &m);

	while(m--)
	{
		scanf("%d%d%d", &u, &v, &w);
		u--, v--;
		graph[u].push_back(make_pair(v, w));
	}

	scanf("%d", &q);
	for(int i = 0;i < q;i++)
	{
		scanf("%d%d%d", &u, &v, &kk);
		u--, v--, kk--;
		if(u == v) kk++;
		qry[u].push_back(make_pair(v, make_pair(kk, i)));
		k[u] = max(k[u], kk+1);
		res[i] = inf;
	}

	for(int i = 0;i < n;i++)
	{
		if(k[i]) dijkstra(i);
	}

	for(int i = 0;i < q;i++) printf("%d\n", ((res[i]==inf)?-1:res[i]));
}