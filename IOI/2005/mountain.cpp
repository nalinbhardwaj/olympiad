// Mountain

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int inf = int(2e9)+5;

struct ppnode {
	int res, sum, lz;
	ppnode *l, *r;
	ppnode(int _res = 0, int _sum = 0, int _lz = -inf, ppnode*_l = NULL, ppnode*_r = NULL)
	{
		res = _res, sum = _sum, lz = _lz;
		l = _l, r = _r;
	}
};

typedef ppnode* pnode;

pnode root;

void shift(pnode& root, int L, int R)
{
	if(root->lz != -inf && L != R)
	{
		root->l->lz = root->r->lz = root->lz;
		root->l->sum = root->lz*((L+R)/2-L+1);
		root->r->sum = root->lz*(R-(L+R)/2);
		if(root->lz >= 0) root->l->res = root->l->sum, root->r->res = root->r->sum;
		else root->l->res = root->r->res = 0;
	}
	root->lz = -inf;
}

void upd(pnode& root, int L, int R, int a, int b, int d)
{
	if(a > R || b < L) return;
	else if(a <= L && R <= b)
	{
		root->lz = d;
		root->sum = d*(R-L+1);
		if(d >= 0) root->res = root->sum;
		else root->res = 0;
	}
	else
	{
		if(!root->l) root->l = new ppnode();
		if(!root->r) root->r = new ppnode();
		shift(root, L, R);
		upd(root->l, L, (L+R)/2, a, b, d), upd(root->r, (L+R)/2+1, R, a, b, d);
		root->sum = root->l->sum+root->r->sum;
		root->res = max(root->l->res, root->l->sum+root->r->res);
	}
}

int qry(pnode& root, int L, int R, int H)
{
	if(L == R) return L;
	if(!root->l) root->l = new ppnode();
	if(!root->r) root->r = new ppnode();
	shift(root, L, R);
	if(root->res <= H) return R;
	//cout << L << " " << (L+R)/2 << " " << root->l->res << "\n";
	if(root->l->res <= H) return qry(root->r, (L+R)/2+1, R, H-root->l->sum);
	else return qry(root->l, L, (L+R)/2, H);
}

int main(void)
{
	int n, a, b, d, h;
	string q;
	scanf("%d", &n);
	pnode root = new ppnode();
	while(true)
	{
		cin >> q;
		if(q[0] == 'E') break;
		if(q[0] == 'I')
		{
			scanf("%d%d%d", &a, &b, &d);
			upd(root, 0, n+1, a, b, d);
		}
		else
		{
			scanf("%d", &h);
			printf("%d\n", qry(root, 0, n+1, h)-1);
		}
	}
}