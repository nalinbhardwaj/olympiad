#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e5)+5;

lli n, ans = lli(1e15)+5;
vector<lli> BIT;

void upd(lli idx)
{
	while(idx < maxn)
	{
		BIT[idx]++;
		idx += (idx&-idx);
	}
}

lli qry(lli idx)
{
	lli res = 0;
	while(idx)
	{
		res += BIT[idx];
		idx -= (idx&-idx);
	}
	return res;
}

void solve(vector<lli>& A, vector<lli>& B)
{
	BIT.clear(); BIT.resize(maxn);
	vector<lli> brev(n+1);
	for(lli i = 0;i < n;i++) brev[B[i]] = i+1;
	lli cur = 0;
	for(lli i = n-1;i >= 0;i--)
	{
		cur += qry(brev[A[i]]-1);
		upd(brev[A[i]]);
	}
	ans = min(ans, cur);

	for(lli i = n-1;i >= 0;i--)
	{
		brev[A[i]]--;
		cur -= n-brev[A[i]]-1;
		cur += brev[A[i]];
		ans = min(ans, cur);
	}
}

int main(void)
{
	ifstream fin("mincross.in");
	ofstream fout("mincross.out");
	fin >> n;
	vector<lli> A(n), B(n);
	for(lli i = 0;i < n;i++)
	{
		fin >> A[i];
	}
	for(lli i = 0;i < n;i++)
	{
		fin >> B[i];
	}

	solve(A, B);
	solve(B, A);
	fout << ans << "\n";
}