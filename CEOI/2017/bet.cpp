//Sure bet

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;
typedef long double dbl;

const lli rempow = lli(1e9), inf = lli(1e18)+5;

lli n;
vector<lli> A, B;

bool f(lli v)
{
	lli x, y = 0, suma = 0, sumb = 0;
	for(x = 0;x < n;x++)
	{
		suma += A[x];
		lli margin = (suma-v)/rempow;
		while(y < n && y < margin && B[y] > 0)
		{
			sumb += B[y++];
		}
		if((sumb-v)/rempow >= x+1)
		{
			//cout << v << " " << x << " " << y << " " << suma << " " << sumb << "\n";
			return true;
		}
	}
	return false;
}

int main(void)
{
	dbl tmpa, tmpb;
	scanf("%lld", &n);
	A.clear(); A.resize(n);
	B.clear(); B.resize(n);
	for(lli i = 0;i < n;i++)
	{
		scanf("%Lf%Lf", &tmpa, &tmpb);
		A[i] = lli(tmpa*dbl(rempow))-rempow;
		B[i] = lli(tmpb*dbl(rempow))-rempow;
		//cout << A[i] << " " << B[i] << "\n";
	}
	sort(A.rbegin(), A.rend()), sort(B.rbegin(), B.rend());
	//return 0;
	lli L = 0, R = inf, ans = 0;
	while(L <= R)
	{
		lli mid = (L+R)/2;
		//cout << L << " " << R << " "; 
		if(f(mid)) L = mid+1, ans = max(ans, mid);
		else R = mid-1;
		//cout << "\n";
	}
	dbl res = dbl(ans)/rempow;
	printf("%.4Lf\n", res);
}