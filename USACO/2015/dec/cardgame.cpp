#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <fstream>
using namespace std;

int main(void)
{
	ifstream fin("cardgame.in");
	ofstream fout("cardgame.out");

	int n;
	fin >> n;
	vector<int> A(n);
	vector<bool> taken(2*n+1);
	for(int i = 0;i < n;i++)
	{
		fin >> A[i];
		taken[A[i]] = true;
	}

	int res = 0;
	set<int> X, B;
	for(int i = 1;i <= 2*n;i++)
	{
		if(!taken[i])
		{
			if(int(X.size()) < n/2) X.insert(i);
			else B.insert(i);
		}
	}

	for(auto it: X) cout << it << " ";
	cout << "\n";
	for(auto it: B) cout << it << " ";
	cout << "\n";
	for(int i = 0;i < n/2;i++)
	{
		set<int>::iterator it = B.lower_bound(A[i]);
		if(it != B.end())
		{
			res++;
			B.erase(it);
		}
	}
	for(int i = n/2;i < n;i++)
	{
		set<int>::iterator it = X.lower_bound(A[i]);
		if(it != X.begin())
		{
			res++;
			X.erase(prev(it));
		}
	}

	fout << res << "\n";
}