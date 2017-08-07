#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

const int inf = 17070509;

int t, a, b;
vector<vector<int> > memo;

int DP(int fullness, bool half)
{
	if(fullness > t) return -inf;
	else if(fullness == t) return t;
	else if(memo[fullness][half] != -1) return memo[fullness][half];
	else
	{
		int res = fullness;
		if(half)
		{
			res = max(res, max(DP(fullness+a, half), DP(fullness+b, half)));
		}
		else
		{
			res = max(res, max(DP(fullness+a, half), DP(fullness+b, half)));
			res = max(res, DP(fullness/2, !half));
		}
		memo[fullness][half] = res;
		return res;
	}
}

int main(void)
{
	ifstream fin("feast.in");
	ofstream fout("feast.out");
	fin >> t >> a >> b;
	memo.clear(); memo.resize(t, vector<int>(2, -1));
	fout << DP(0, 0) << "\n";
}