#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;

int main(void)
{
	ifstream fin("bcount.in");
	ofstream fout("bcount.out");

	int n, q, tmp, a, b;
	fin >> n >> q;
	vector<vector<int> > pre(n, vector<int>(3, 0));
	for(int i = 0;i < n;i++)
	{
		fin >> tmp;
		if(i)
		{
			for(int j = 0;j < 3;j++) pre[i][j] += pre[i-1][j];
		}
		pre[i][tmp-1]++;
	}
	while(q--)
	{
		fin >> a >> b;
		b--; a-= 2;
		for(int i = 0;i < 3;i++)
		{
			fout << ((b>=0)?pre[b][i]:0)-((a>=0)?pre[a][i]:0);
			if(i < 2) fout << " ";
		}
		
		if(q)fout << "\n";
	}
}