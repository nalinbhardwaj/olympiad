#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

int main(void)
{
	ifstream fin("highcard.in");
	ofstream fout("highcard.out");

	int n;
	fin >> n;
	vector<bool> taken(2*n+1, false);
	vector<int> A(n);
	set<int> B;
	int res = 0;
	for(int i = 0;i < n;i++)
	{
		fin >> A[i];
		taken[A[i]] = true;
	}
	for(int i = 1;i <= 2*n;i++)
	{
		if(!taken[i]) B.insert(i);
	}

	for(int i = 0;i < n;i++)
	{
		set<int>::iterator it = B.lower_bound(A[i]);
		if(it != B.end())
		{
			res++;
			B.erase(it);
		}
	}
	fout << res << "\n";
}