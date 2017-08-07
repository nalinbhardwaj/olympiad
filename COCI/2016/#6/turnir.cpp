#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int res[(1<<21)];
map<int, vector<int>> mp;

int main(void)
{
	int n, x;
	scanf("%d", &n);
	for(int i = 0;i < (1<<n);i++)
	{
		scanf("%d", &x);
		mp[x].push_back(i);
	}

	int val = 0;
	for(auto it: mp)
	{
		val += int(it.second.size());
		
		int level = 0;
		while((1<<level) <= val) level++;
		level--;
		//cout << it.first << " " << level << "\n";
		for(auto gt: it.second) res[gt] = n-level;
	}
	for(int i = 0;i < (1<<n);i++) printf("%d ", res[i]);
	printf("\n");
}