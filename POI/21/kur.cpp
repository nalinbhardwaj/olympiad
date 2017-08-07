#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct ppnode {
	int res;
	ppnode *l, *r;
	ppnode(int rrr = 0, ppnode* L = NULL, ppnode* R = NULL)
	{
		res = rrr;
		l = L;
		r = R;
	}
};

typedef ppnode* pnode;

int n;
pnode dummy;
int A[5*int(1e5)];
pnode root[5*int(1e5)];

pnode frequpd(pnode root, int L, int R, int idx)
{
	if(L == R)
	{
		return new ppnode(root->res+1, NULL, NULL);
	}
	else
	{
		if(idx <= (L+R)/2) return new ppnode(root->res+1, frequpd(root->l, L, (L+R)/2, idx), root->r);
		else return new ppnode(root->res+1, root->l, frequpd(root->r, (L+R)/2+1, R, idx));
	}
}

int freqqry(pnode root1, pnode root2, int L, int R, int idx)
{
	if(L == R) return root2->res-root1->res;
	else
	{
		if(idx <= (L+R)/2) return freqqry(root1->l, root2->l, L, (L+R)/2, idx);
		else return freqqry(root1->r, root2->r, (L+R)/2+1, R, idx);
	}
}

int st[2*int(1e6)];

inline int left(int node) { return node<<1; }
inline int right(int node) { return (node<<1)+1; }

void build(int node, int L, int R)
{
	if(L == R)
	{
		st[node] = A[L];
	}
	else
	{
		build(left(node), L, (L+R)/2);
		build(right(node), (L+R)/2+1, R);

		st[node] = 0;
		if(st[left(node)])
		{
			if(freqqry((L?root[L-1]:dummy), root[R], 1, n, st[left(node)]) > (R-L+1)/2) st[node] = st[left(node)];
		}
		if(st[right(node)])
		{
			if(freqqry((L?root[L-1]:dummy), root[R], 1, n, st[right(node)]) > (R-L+1)/2) st[node] = st[right(node)];
		}
	}
}

int qry(int node, int L, int R, int a, int b)
{
	if(a > R || b < L) return 0;
	else if(a <= L && R <= b)
	{
		if(freqqry((a?root[a-1]:dummy), root[b], 1, n, st[node]) > (b-a+1)/2) return st[node];
		else return 0;
	}
	else
	{
		return max(qry(left(node), L, (L+R)/2, a, b), qry(right(node), (L+R)/2+1, R, a, b));
	}
}

int main(void)
{
	int m, a, b;
	scanf("%d%d", &n, &m);
	for(int i = 0;i < n;i++) scanf("%d", &A[i]);

	dummy = new ppnode();
	dummy->l = dummy->r = dummy;

	root[0] = frequpd(dummy, 1, n, A[0]);
	for(int i = 1;i < n;i++)
	{
		root[i] = frequpd(root[i-1], 1, n, A[i]);
	}

	build(1, 0, n-1);
	int res = 0;
	while(m--)
	{
		scanf("%d%d", &a, &b);
		a --; b--;
		res = qry(1, 0, n-1, a, b);
		printf("%d\n", res);
	}
}