#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

typedef long long int lli;

lli n, t;

inline lli lliMOD(lli a, lli b) { return ((a%b)+b)%b; }

void solve(vector<lli>& A, lli v)
{
	vector<lli> B(n);
	for(lli i = 0;i < n;i++) B[i] = A[lliMOD(i-(1ll<<v), n)]^A[lliMOD(i+(1ll<<v), n)];
	A = B;
}

int main(void)
{
	scanf("%lld%lld", &n, &t);
	string S;
	cin >> S;
	vector<lli> A(n);
	for(lli i = 0;i < n;i++) A[i] = lli(S[i]-'0');

	lli b = log2(t);
	for(lli x = b;x >= 0;x--)
	{
		if(t >= (1ll<<x))
		{
			solve(A, x);
			t -= (1ll<<x);
		}
	}
	for(lli i = 0;i < n;i++) printf("%lld", A[i]);
	printf("\n");
}