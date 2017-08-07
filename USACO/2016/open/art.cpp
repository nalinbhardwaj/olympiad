#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

const int maxn = int(1e3)+5, inf = int(1e9)+5;

int n, A[maxn][maxn], candy[maxn*maxn+5];
pair<pair<int, int>, pair<int, int>> mark[maxn*maxn+5];

int main(void)
{
	ifstream fin("art.in");
	ofstream fout("art.out");
	fin >> n;
	int yep = 0;

	for(int i = 0;i <= n*n;i++) mark[i].first = mark[i].second = {inf, -1}, candy[i] = 1;

	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			fin >> A[i][j];
			if(A[i][j])
			{
				yep++;
				mark[A[i][j]].first.first = min(i, mark[A[i][j]].first.first);
				mark[A[i][j]].first.second = max(i, mark[A[i][j]].first.second);
				mark[A[i][j]].second.first = min(j, mark[A[i][j]].second.first);
				mark[A[i][j]].second.second = max(j, mark[A[i][j]].second.second);
			}
		}
	}
	if(yep == 0)
	{
		fout << "f" << "\n";
		exit(0);
	}

	int res = 0, ulta = 0;
	for(int color = 1;color <= n*n;color++)
	{
		if(mark[color].first.first == inf)
		{
			//cout << color << "\n";
			ulta++;
			continue;
		}

		for(int i = mark[color].first.first;i <= mark[color].first.second;i++)
		{
			for(int j = mark[color].second.first;j <= mark[color].second.second;j++)
			{
				if(A[i][j] != color)
				{
					candy[A[i][j]] = 0;
				}
			}
		}
	}
	if(ulta == n*n-1) res--;
	for(int i = 1;i <= n*n;i++)
	{
		//cout << candy[i] << "\n";
		res += candy[i];
	}

	fout << res << "\n";
}