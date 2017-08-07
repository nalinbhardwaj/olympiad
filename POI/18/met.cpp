#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

typedef long long int lli;

struct pnode {
	lli lz;
	pnode* l, *r;

	pnode(lli v = 0, pnode* ll = NULL, pnode* rr = NULL)
	{
		lz = v;
		l = ll;
		r = rr;
	}
};

typedef pnode* node;

int n, m, k;
node dummy, root[3*int(1e5)+5];
int P[3*int(1e5)+5], O[3*int(1e5)+5];
vector<int> sites[3*int(1e5)+5];

node upd(node root, int L, int R, int a, int b, int v)
{
	if(a > R || b < L) return root;
	else if(a <= L && R <= b)
	{
		return new pnode(root->lz+v, root->l, root->r);
	}
	else
	{
		return new pnode(root->lz, upd(root->l, L, (L+R)/2, a, b, v), upd(root->r, (L+R)/2+1, R, a, b, v));
	}
}

lli qry(node root, int L, int R, int idx)
{
	if(L == R) return root->lz;
	else
	{
		if(idx <= (L+R)/2) return root->lz+qry(root->l, L, (L+R)/2, idx);
		else return root->lz+qry(root->r, (L+R)/2+1, R, idx);
	}
}

lli calc(int x, int y)
{
	lli res = 0;
	for(vector<int>::iterator it = sites[y].begin();it != sites[y].end();it++)
	{
		res += qry(root[x], 0, m-1, *it);
	}
	return res;
}

int main(void)
{
	int L, R, A;
	scanf("%d%d", &n, &m);
	dummy = new pnode();
	dummy->l = dummy->r = dummy;

	for(int i = 0;i < m;i++)
	{
		scanf("%d", &O[i]);
		O[i]--;
		sites[O[i]].push_back(i);
	}

	for(int i = 0;i < n;i++) scanf("%d", &P[i]);

	scanf("%d", &k);
	root[0] = dummy;
	for(int i = 1;i <= k;i++)
	{
		scanf("%d%d%d", &L, &R, &A);
		L--; R--;
		if(L <= R)
		{
			root[i] = upd(root[i-1], 0, m-1, L, R, A);
		}
		else
		{
			node tmp = upd(root[i-1], 0, m-1, L, m-1, A);
			root[i] = upd(tmp, 0, m-1, 0, R, A);
		}
	}

	for(int i = 0;i < n;i++)
	{
		int L = 1, R = k, mid, ans = k+1;

		//cout << "tots: " << calc(k, i) << "\n";
		//cout << P[i] << "\n";
		//for(auto it: sites[i]) cout << it << " ";
		//cout << "\n\n";
		if(calc(R, i) < lli(P[i]))
		{
			printf("NIE\n");
			continue;
		}
		while(L <= R)
		{
			mid = (L+R)/2;
			if(calc(mid, i) < lli(P[i])) L = mid+1;
			else
			{
				ans = min(ans, mid);
				R = mid-1;
			}
		}
		printf("%d\n", ans);
	}
}