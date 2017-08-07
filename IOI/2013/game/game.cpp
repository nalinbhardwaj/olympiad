#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "game.h"
using namespace std;
 
typedef long long int lli;
 
lli gcd2(lli X, lli Y) {
    lli tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}
 
struct ppnode0 {
    int key, prior;
    lli self, v;
    ppnode0 *l, *r;
    ppnode0(int _key = 0, lli _self = 0ll, lli _v = 0ll, ppnode0*_l = NULL, ppnode0*_r = NULL)
    {
        key = _key, self = _self, v = _v, l = _l, r = _r;
        prior = rand();
    }
};
 
typedef ppnode0* pnode0;
 
inline lli getv(pnode0 t)
{
    return (t?t->v:0ll);
}
 
void upd(pnode0& t)
{
    if(t) t->v = gcd2(t->self, gcd2(getv(t->l), getv(t->r)));
}
 
void split(pnode0 t, pnode0& L, pnode0& R, int k)
{
    if(!t)
    {
        L = R = NULL;
        return;
    }
    if(t->key <= k)
    {
        split(t->r, t->r, R, k);
        L = t;
    }
    else
    {
        split(t->l, L, t->l, k);
        R = t;
    }
    upd(t);
}
 
void merge(pnode0& t, pnode0 L, pnode0 R)
{
    if(!L || !R)
    {
        t = (L?L:R);
        return;
    }
    if(L->prior > R->prior)
    {
        merge(L->r, L->r, R);
        t = L;
    }
    else
    {
        merge(R->l, L, R->l);
        t = R;
    }
    upd(t);
}
 
lli findval(pnode0& t, int k)
{
    if(!t) return 0ll;
    if(t->key == k) return t->self;
    else if(t->key < k) return findval(t->r, k);
    else return findval(t->l, k);
}
 
struct ppnode1 {
    pnode0 v;
    ppnode1 *l, *r;
    ppnode1(pnode0 _v = NULL, ppnode1* _l = NULL, ppnode1* _r = NULL)
    {
        v = _v, l = _l, r = _r;
    }
};
 
typedef ppnode1* pnode1;
 
lli qry0(pnode0& root, int a, int b)
{
    if(!root) return 0;
    pnode0 part1 = NULL, part2 = NULL, part3 = NULL, part4 = NULL;
    split(root, part1, part2, b);
    split(part1, part3, part4, a-1);
    lli res = (part4?part4->v:0);
    merge(part1, part3, part4);
    merge(root, part1, part2);
    return res;
}
 
lli qry1(pnode1 root, int L, int R, int a, int b, int c, int d)
{
    if(a > R || b < L || !root) return 0ll;
    else if(a <= L && R <= b) return qry0(root->v, c, d);
    else return gcd2(qry1(root->l, L, (L+R)/2, a, b, c, d), qry1(root->r, (L+R)/2+1, R, a, b, c, d));
}
 
void upd0(pnode0& root, int idx, lli v)
{
    pnode0 part1 = NULL, part2 = NULL, part3 = NULL, part4 = NULL;
    split(root, part1, part2, idx);
    split(part1, part3, part4, idx-1);
    part4 = new ppnode0(idx, v, v, NULL, NULL);
    merge(part1, part3, part4);
    merge(root, part1, part2);
}
 
void upd1(pnode1 root, int L, int R, int a, int b, lli v)
{
    if(L == R) upd0(root->v, b, v);
    else
    {
        if(a <= (L+R)/2)
        {
            if(!root->l) root->l = new ppnode1();
            upd1(root->l, L, (L+R)/2, a, b, v);
        }
        else
        {
            if(!root->r) root->r = new ppnode1();
            upd1(root->r, (L+R)/2+1, R, a, b, v);
        }
 
        lli p = (root->l?findval(root->l->v, b):0ll), q = (root->r?findval(root->r->v, b):0ll);
        upd0(root->v, b, gcd2(p, q));
    }
    //cout << L << " " << R << " " << root->v->v << "\n";
}
 
int r, c;
pnode1 grid;
 
void init(int _R, int _C)
{
    //cout << "init\n";
    r = _R-1;
    c = _C-1;
    srand(time(NULL));
    grid = new ppnode1();
}
 
void update(int P, int Q, long long K)
{
    //cout << "update\n";
    upd1(grid, 0, r, P, Q, K);
}
 
long long calculate(int P, int Q, int U, int V)
{
    //cout << "calculate\n";
    return qry1(grid, 0, r, P, U, Q, V);
}
