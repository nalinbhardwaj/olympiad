#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "icc.h"
using namespace std;
 
const int maxn = 105, inf = int(1e9)+5;
 
int n, P[maxn];
pair<vector<int>, vector<int>> Q[10];
vector<int> vec[maxn];
 
inline int root(int node)
{
	return ((P[node] == node)?node:(P[node] = root(P[node])));
}
 
void dsu(int x, int y)
{
	x = root(x), y = root(y);
	P[y] = x;
}
 
/*void setRoad(int a, int b)
{
	cout << "SETROAD " << a << " " << b << "\n";
}
 
int query(int n, int m, int* a, int* b)
{
	cout << "ASKQUERY\n";
	cout << n << ": ";
	for(int i = 0;i < n;i++) cout << a[i] << " ";
	cout << "\n";
	cout << m << ": ";
	for(int i = 0;i < m;i++) cout << b[i] << " ";
	cout << "\n";
	int ret;
	cin >> ret;
	return ret;
}*/
 
bool ask(pair<vector<int>, vector<int>>& A)
{
	int a_sz = int(A.first.size()), b_sz = int(A.second.size());
	int q1[a_sz], q2[b_sz];
	for(int i = 0;i < a_sz;i++) q1[i] = A.first[i]+1;
	for(int i = 0;i < b_sz;i++) q2[i] = A.second[i]+1;
	return query(a_sz, b_sz, q1, q2);
}
 
int build(vector<int> todo, int ht)
{
	if(int(todo.size()) == 1) return ht;
	else
	{
		int mid = (int(todo.size())-1)/2;
		random_shuffle(todo.begin(), todo.end());
		vector<int> lef, righ;
 
		for(int i = 0;i <= mid;i++)
		{
			lef.push_back(todo[i]);
			for(auto it: vec[todo[i]]) Q[ht].first.push_back(it);
		}
		for(int i = mid+1;i < int(todo.size());i++)
		{
			righ.push_back(todo[i]);
			for(auto it: vec[todo[i]]) Q[ht].second.push_back(it);
		}
		return max(build(lef, ht+1), build(righ, ht+1));
	}
}
 
pair<int, int> precise(pair<vector<int>, vector<int>>& A)
{
	int L = 0, R = int(A.first.size())-2, ans = int(A.first.size())-1;
	while(L <= R)
	{
		int mid = (L+R)/2;
		pair<vector<int>, vector<int>> yolo;
		yolo.second = A.second;
		for(int i = 0;i <= mid;i++) yolo.first.push_back(A.first[i]);
		if(ask(yolo))
		{
			ans = min(ans, mid);
			R = mid-1;
		}
		else L = mid+1;
	}
	pair<int, int> ret = {A.first[ans], inf};
	swap(A.first, A.second);
	L = 0, R = int(A.first.size())-2, ans = int(A.first.size())-1;
	while(L <= R)
	{
		int mid = (L+R)/2;
		pair<vector<int>, vector<int>> yolo;
		yolo.second = A.second;
		for(int i = 0;i <= mid;i++) yolo.first.push_back(A.first[i]);
		if(ask(yolo))
		{
			ans = min(ans, mid);
			R = mid-1;
		}
		else L = mid+1;
	}
	ret.second = A.first[ans];
	swap(A.first, A.second);
	return ret;
}
 
void solve()
{
	vector<int> complet;
	for(int i = 0;i < n;i++) vec[i].clear();
	for(int i = 0;i < n;i++)
	{
		vec[root(i)].push_back(i);
		if(i == root(i)) complet.push_back(root(i));
	}
 
	int maxht = build(complet, 0);
 
	pair<int, int> res;
	for(int i = 0;i < maxht;i++)
	{
		if(Q[i].first.empty() || Q[i].second.empty()) continue;
		if(ask(Q[i]))
		{
			res = precise(Q[i]);
			break;
		}
	}
	dsu(res.first, res.second);
	setRoad(res.first+1, res.second+1);
 
	for(int i = 0;i < maxht;i++) Q[i].first.clear(), Q[i].second.clear();
}
 
void run(int N)
{
	srand(1234567890);
	n = N;
	for(int i = 0;i < n;i++) P[i] = i;
	for(int i = 1;i < n;i++) solve();
}
 
/*int main(void)
{
	int v;
	cin >> v;
 
	run(v);
}*/