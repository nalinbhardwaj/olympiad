#include <iostream>
#include <cstdio>
#include <vector>
#include "cave.h"
using namespace std;
 
const int maxn = int(5e3)+5;
 
int n, val[maxn], conn[maxn];
 
int ask(int S[], int x)
{
	int ret = tryCombination(S);
	return (ret == -1 || ret > x);
}
 
bool f(int mark, int state, int x)
{
	int tmp[n];
	for(int i = 0;i < n;i++)
	{
		if(val[i] == -1) tmp[i] = ((i <= mark)?state:(!state));
		else tmp[i] = val[i];
	}
	int ret = ask(tmp, x);
	//cout << mark << " " << state << " " << x << " " << ret << "\n";
	return ret;
}
 
pair<int, int> solve(int x)
{
	pair<int, int> ret;
	int config[n];
	for(int i = 0;i < n;i++)
	{
		if(val[i] == -1) config[i] = 0;
		else config[i] = val[i];
	}
 
	if(ask(config, x)) ret.second = 0;
	else ret.second = 1;
 
	int L = 0, R = n-1;
	ret.first = n+1;
	while(L <= R)
	{
		int mid = (L+R)/2;
		if(f(mid, ret.second, x))
		{
			R = mid-1;
			ret.first = min(ret.first, mid);
		}
		else L = mid+1;
	}
	return ret;
}
 
void exploreCave(int _N) {
	n = _N;
	for(int i = 0;i < n;i++) val[i] = -1;
	for(int i = 0;i < n;i++)
	{
		pair<int, int> r = solve(i);
		//cout << r.first << " " << r.second << "\n";
		val[r.first] = r.second;
		conn[r.first] = i;
	}
	int S[n], D[n];
	for(int i = 0;i < n;i++) S[i] = val[i], D[i] = conn[i];
	answer(S, D);
}