#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

// j -1
// p +1
// Number of p should be >= number of j

const int inf = 1707050917;

int maxn, P[int(1e6)+5], ans[int(1e6)+5], BIT[int(1e6)+5];
vector<int> deactivate[int(1e6)+5];

void upd(int idx, int v, int type)
{
	while(idx <= maxn)
	{
		if(type) BIT[idx] = max(BIT[idx], v);
		else BIT[idx] = min(BIT[idx], v);
		idx += (idx&-idx);
	}
}

int qry(int idx, int type)
{
	int res = inf;
	if(type) res *= -1;
	while(idx)
	{
		if(type) res = max(BIT[idx], res);
		else res = min(BIT[idx], res);
		idx -= (idx&-idx);
	}
	return res;
}

int main(void)
{
	int n;
	scanf("%d", &n);
	char S[n+1];
	scanf("%s", S);
	int res = (S[0] == 'p');
	vector<int> mapper(n+1);
	map<int, int> mp;
	for(int i = 1;i <= n;i++)
	{
		P[i] = P[i-1];
		if(S[i-1] == 'p') P[i]++;
		else P[i]--;
		mapper[i] = P[i];
	}
	sort(mapper.begin(), mapper.end());
	mapper.resize(int(unique(mapper.begin(), mapper.end())-mapper.begin()));
	int v = 2;
	for(vector<int>::iterator it = mapper.begin();it != mapper.end();it++) mp[*it] = v++;
	maxn = v+1;
	for(int i = 0;i <= maxn;i++) BIT[i] = n;

	for(int i = n;i >= 0;i--)
	{
		if(S[i] != 'j') ans[i+1] = qry(mp[P[i]]-1, 0);
		upd(mp[P[i]], i, 0);
	}
	//for(int i = 1;i <= n;i++) cout << i << " " << ans[i] << "\n";
	maxn++; v++;
	for(int i = 0;i <= maxn;i++) BIT[i] = 1;
	for(int i = 1;i <= n;i++)
	{
		deactivate[qry(v-mp[P[i]]-1, 1)].push_back(i);
		//cout << i << " " << qry(mp[P[i]]-1, 1) << " " << ans[i] << "\n";
		upd(v-mp[P[i]], i, 1);
	}

	set<int> X;
	for(int i = 1;i <= n;i++) X.insert(-i);

	for(int i = n;i > 0;i--)
	{

		if(X.lower_bound(-ans[i]) != X.end() && i != n && S[i-1] != 'j')
		{
			res = max(res, -(*X.lower_bound(-ans[i]))-i+1);
			//cout << i << " " << -(*X.lower_bound(-ans[i])) << " " << ans[i] << "\n";
		}
		for(vector<int>::iterator it = deactivate[i].begin();it != deactivate[i].end();it++) X.erase(-*it);
	}
	printf("%d\n", res);
}