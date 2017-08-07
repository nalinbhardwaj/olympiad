#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <fstream>
using namespace std;

typedef long long int lli;

const lli inf = 1707050900;

int main(void)
{
	ifstream fin("landscape.in");
	ofstream fout("landscape.out");

	lli n, x, y, z, res = 0;
	fin >> n >> x >> y >> z;
	vector<lli> A(n), B(n);
	for(int i = 0;i < n;i++) fin >> A[i] >> B[i];
	vector<int> less;
	for(int i = 0;i < n;i++)
	{
		if(A[i] < B[i]) less.push_back(i);
	}
	//for(auto it: less) cout << it << " ";
	//cout << "\n";
	//cout << "strt\n";
	for(int i = 0;i < n;i++)
	{
		while(A[i] > B[i])
		{
			lli M = inf;
			for(auto it: less)
			{
				if(abs(it-i) < abs(M-i) && A[it] < B[it]) M = it;
			}
			if(M == inf) break;
			if(z*abs(M-i) <= (x+y))
			{
				res += z*abs(M-i);
				//cout << M << " " << i << "\n";
				A[i]--; A[M]++;
			}
		}
	}

	for(int i = 0;i < n;i++)
	{
		if(A[i] < B[i])
		{
			res += x*(B[i]-A[i]);
		}
		else
		{
			res += y*(A[i]-B[i]);
		}
	}
	fout << res << "\n";
}