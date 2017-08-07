// Deciphering the Mayan Writing

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int maxl = 200;

int cnt[maxl], realcnt[maxl];

int main(void)
{
	int res = 0, n, m;
	string g, s;
	cin >> n >> m >> g >> s;
	for(auto it: g) cnt[int(it)]++;
	set<int> cur;
	for(int i = 0;i < maxl;i++)
	{
		if(cnt[i] != realcnt[i]) cur.insert(i);
	}

	for(int i = 0;i < n;i++)
	{
		int idx = int(s[i]);
		if(cnt[idx] != realcnt[idx]) cur.erase(idx);
		realcnt[idx]++;
		if(cnt[idx] != realcnt[idx]) cur.insert(idx);
	}

	res += cur.empty();
	for(int i = n;i < m;i++)
	{
		int idx = int(s[i]);
		if(cnt[idx] != realcnt[idx]) cur.erase(idx);
		realcnt[idx]++;
		if(cnt[idx] != realcnt[idx]) cur.insert(idx);

		idx = int(s[i-n]);
		if(cnt[idx] != realcnt[idx]) cur.erase(idx);
		realcnt[idx]--;
		if(cnt[idx] != realcnt[idx]) cur.insert(idx);
		res += cur.empty();
	}
	printf("%d\n", res);
}