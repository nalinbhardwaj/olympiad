#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <set>
using namespace std;

typedef long long int lli;
typedef long double dbl;

const lli maxn = lli(1e5)+5;

lli A[maxn], B[maxn];

int main(void)
{
	ifstream fin("tallbarn.in");
	ofstream fout("tallbarn.out");
	lli n, k;
	set<pair<dbl, lli>> S;
	fin >> n >> k;
	for(lli i = 0;i < n;i++) fin >> A[i];

	if(n == 1)
	{
		fout << round(A[0]/k) << "\n";
		return 0;
	}

	for(lli i = 0;i < n;i++, k--)
	{
		B[i] = 1;
		S.insert({dbl(A[i])/(B[i]*B[i]+B[i]), i});
	}

	while(k)
	{
		pair<dbl, lli> top = *S.rbegin();
		S.erase(top);

		pair<dbl, lli> topp = *S.rbegin();
		while(top.first >= topp.first)
		{
			//cout << top.first << " " << topp.first << "\n";
			if(!k) break;
			B[top.second]++; k--;
			top = {dbl(A[top.second])/(B[top.second]*B[top.second]+B[top.second]), top.second};
		}
		S.insert(top);
	}

	dbl res = 0.00;
	for(lli i = 0;i < n;i++) res += dbl(A[i])/B[i];
	fout << lli(round(res)) << "\n";
}