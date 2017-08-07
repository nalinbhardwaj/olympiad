#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

int main(void)
{
	ifstream fin("262144.in");
	ofstream fout("262144.out");
	int n, res = 0;
	fin >> n;
	vector<int> A(n);
	vector<vector<int>> range(2, vector<int>(n+2, -1));
	for(int i = 0;i < n;i++)
	{
		fin >> A[i];
		res = max(res, A[i]);
	}

	for(int k = 1;k <= 65;k++)
	{
		for(int i = 0;i < n;i++)
		{
			if(A[i] == k-1) range[0][i] = i;
		}
		for(int i = 0;i < n;i++)
		{
			if(range[0][i] != -1)
			{
				if(range[0][range[0][i]+1] != -1)
				{
					res = max(res, k);
					range[1][i] = range[0][range[0][i]+1];
				}
			}
		}
		range[0] = range[1];
		range[1].clear(); range[1].resize(n+2, -1);
	}
	fout << res << "\n";
}