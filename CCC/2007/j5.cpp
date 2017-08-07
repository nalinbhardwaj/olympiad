#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int meh[] = { 0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010,  7000 };
int A, B;
vector<int> val(meh, meh+14);
vector<int> memo;

int dp(int i)
{
	if(memo[i] != -1)
		return memo[i];
	else
	{
		if(val[i] == 7000)
		{
			memo[i] = 1;
			return 1;
		}
		int tmp = 0;
		for(int j = i+1;j < int(val.size()) && val[j]-val[i] <= B;j++)
		{
			if(val[j]-val[i] >= A)
			{
				tmp += dp(j);
			}
		}
		memo[i] = tmp;
		return memo[i];
	}
}

int main(void)
{
	scanf("%d%d", &A, &B);
	int t;
	scanf("%d", &t);
	val.resize(t+14);
	memo.resize(t+14, -1);
	for(int i = 0;i < t;i++)
		scanf("%d", &val[i+14]);
	sort(val.begin(), val.end());
	/*for(int i = 0;i < int(val.size());i++)
	{
		printf("%d ", val[i]);
	} */
	int ans = dp(0);
	printf("%d\n", ans);
}