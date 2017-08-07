#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = int(5e5)+5;

int A[maxn], st[4*maxn], res[maxn];
vector<int> val[maxn];
vector<pair<int, int>> query[maxn];
vector<pair<pair<int, int>, pair<int, int>>> updates;
vector<pair<pair<int, int>, int>> upd[maxn];

inline int left(int node) { return (node<<1); }
inline int right(int node)  { return (node<<1)+1; }

void updst(int node, int L, int R, int a, int b, int v)
{
	if(a > R || b < L) return;
	else if(a <= L && R <= b)
	{
		st[node] += v;
	}
	else
	{
		updst(left(node), L, (L+R)/2, a, b, v);
		updst(right(node), (L+R)/2+1, R, a, b, v);
	}
}

int qry(int node, int L, int R, int idx)
{
	if(L == R) return st[node];
	else
	{
		if(idx <= (L+R)/2) return qry(left(node), L, (L+R)/2, idx)+st[node];
		else return qry(right(node), (L+R)/2+1, R, idx)+st[node];
	}
}

int main(void)
{
	int n, q;
	scanf("%d%d", &n, &q);
	vector<int> S(n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d", &A[i]);
		S[i-1] = A[i];
	}
	sort(S.begin(), S.end());
	S.resize(int(unique(S.begin(), S.end())-S.begin()));

	map<int, int> mp;
	int maxv = 0;
	for(auto it: S) mp[it] = maxv++;
	for(int i = 1;i <= n;i++) A[i] = mp[A[i]];

	for(int i = 0;i < maxv;i++)
	{
		val[i].push_back(0);
	}
	for(int i = 1;i <= n;i++) val[A[i]].push_back(i);

	for(int i = 0;i < maxv;i++)
	{
		val[i].push_back(n+1);
		//cout << i << " " << int(val[i].size()) << "\n";
		for(int j = 1;j < int(val[i].size())-2;j++)
		{
			//cout << j << "\n";
			updates.push_back({{val[i][j-1], val[i][j]}, {val[i][j+1], val[i][j+2]}});
		}
	}

	for(auto it: updates)
	{
		//cout << it[0] << " " << it[1] << " " << it[2] << " " << it[3] << "\n";
		upd[it.first.first+1].push_back({{it.second.first, it.second.second-1}, 1});
		upd[it.first.second+1].push_back({{it.second.first, it.second.second-1}, -1});
	}

	int L, R;
	for(int i = 0;i < q;i++)
	{
		scanf("%d%d", &L, &R);
		query[L].push_back({R, i});
	}

	for(int i = 0;i <= n;i++)
	{
		//cout << i << ":\n";
		for(auto it: upd[i])
		{
			//cout << it[0] << " " << it[1] << " " << it[2] << "\n";
			updst(1, 0, n, it.first.first, it.first.second, it.second);
		}

		for(auto it: query[i])
		{
			res[it.second] = qry(1, 0, n, it.first);
		}
	}

	for(int i = 0;i < q;i++) printf("%d\n", res[i]);
}