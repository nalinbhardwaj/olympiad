/*
	PROG: COW
	LANG: C++
	ID: nibnalin
*/
//USACO February Contest
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

vector<vector<int> > grid;
vector< vector<long> > memtable;

int ans(long x, long y) {
	if(memtable[x][y] == INT_MIN)
	{
		long paths = 0;
		for(long i = (x-1);i >= 0;i--)
		{
			for(long j = (y-1);j >= 0;j--)
			{
				if(grid[x][y] != grid[i][j])
				{
					paths += ans(i, j);
				}
			}
		}
		memtable[x][y] = paths;
		return paths;
	}
	else
		return memtable[x][y];
}

int main(void)
{
	ifstream fin ("hopscotch.in");
	ofstream fout ("hopscotch.out");

	long r, c;
	fin >> r >> c;
	grid.clear();
	grid.resize(r, vector<int>(c));
	memtable.clear();
	memtable.resize(r, vector<long>(c, INT_MIN));
	for(int i = 0;i < r;i++)
	{
		string tmp;
		fin >> tmp;
		for(int j = 0;j < c;j++)
		{
			if(tmp[j] == 'R')
				grid[i][j] = 1;
			else
				grid[i][j] = 0;
		}
	}
	memtable[0][0] = 1;
	fout << ans(r-1, c-1) << endl; //Recurse, memoize
}