#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include "robots.h"
using namespace std;
 
const int maxn = int(1e6)+5, maxs = int(5e4)+5, inf = int(1e9)+5;
 
int t, a, b, X[maxs], Y[maxs];
pair<int, int> A[maxn];
 
bool f(int x)
{
	priority_queue<int> undone;
	int ptr = 0;
 
	for(int i = 0;i < a;i++)
	{
		while(ptr < t && A[ptr].first < X[i])
		{
			undone.push(A[ptr].second);
			ptr++;
		}
		if(ptr == t && undone.empty()) return 1;
 
		int tmp = x;
		while(!undone.empty() && tmp--) undone.pop();
	}
 
	while(ptr < t) undone.push(A[ptr++].second);
 
	vector<int> ffs;
	while(!undone.empty())
	{
		ffs.push_back(undone.top());
		undone.pop();
	}
	reverse(ffs.begin(), ffs.end());
 
	ptr = 0;
	for(int i = 0;i < b;i++)
	{
		int tmp = x;
		while(tmp-- && ptr < int(ffs.size()) && ffs[ptr] < Y[i]) ptr++;
		if(ptr == int(ffs.size())) return 1;
	}
	return (ptr == int(ffs.size()));
}
 
 
int putaway(int _A, int _B, int _T, int _X[], int _Y[], int _W[], int _S[])
{
	a = _A, b = _B, t = _T;
	for(int i = 0;i < t;i++) A[i] = {_W[i], _S[i]};
	for(int i = 0;i < a;i++) X[i] = _X[i];
	for(int i = 0;i < b;i++) Y[i] = _Y[i];
	sort(A, A+t), sort(X, X+a), sort(Y, Y+b);
 
	int L = 1, R = t+1, ans = inf;
	
	while(L <= R)
	{
		int mid = (L+R)/2;
		if(f(mid)) R = mid-1, ans = min(ans, mid);
		else L = mid+1;
	}
	return ((ans > t+1)?-1:ans);
}