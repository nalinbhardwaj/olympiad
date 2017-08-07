// Guess Which Cow

#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
using namespace std;

struct ppnode {
	int res = -1, childcnt = 0, leafcnt = 0;
	ppnode* child[3] = {NULL};
};

typedef ppnode* pnode;

int lookup[4] = {int('X'), int('Y'), int('Z')};

void trinsert(pnode& root, vector<int>& A, int idx, int v)
{
	root->leafcnt++;
	if(idx == int(A.size())) root->res = v;
	else
	{
		if(!root->child[A[idx]])
		{
			root->childcnt++;
			root->child[A[idx]] = new ppnode();
		}
		trinsert(root->child[A[idx]], A, idx+1, v);
	}
}

bool ask(int p, vector<int> q)
{
	printf("Q %d ", p+1);
	for(auto it: q)
	{
		printf("%c ", char(lookup[it]));
	}
	printf("\n");
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res;
}

int main(void)
{
	srand(time(NULL));
	int n, p;
	scanf("%d%d", &n, &p);
	pnode root = new ppnode();
	for(int i = 0;i < n;i++)
	{
		vector<int> s;
		for(int j = 0;j < p;j++)
		{
			string t;
			cin >> t;
			s.push_back(int(t[0]-'X'));
		}
		trinsert(root, s, 0, i);
	}

	pnode cur = root;
	for(int idx = 0;idx < p;idx++)
	{
		if(cur->childcnt == 1)
		{
			for(int i = 0;i < 3;i++)
			{
				if(cur->child[i])
				{
					cur = cur->child[i];
					break;
				}
			}
		}
		else if(cur->childcnt == 2)
		{
			int a = -1, b = -1;
			for(int i = 0;i < 3;i++)
			{
				if(cur->child[i])
				{
					if(a == -1) a = i;
					else b = i;
				}
			}
			if(ask(idx, {a})) cur = cur->child[a];
			else cur = cur->child[b];
		}
		else
		{
			pair<int, int> ans = {int(1e9)+5, -1};
			for(int i = 0;i < 3;i++)
			{
				int tmp = abs(cur->leafcnt-(cur->child[i]->leafcnt));
				ans = min(ans, {tmp, i});
			}
			if(ask(idx, {ans.second}))
			{
				cur = cur->child[ans.second];
			}
			else
			{
				int a = -1, b = -1;
				for(int i = 0;i < 3;i++)
				{
					if(i != ans.second)
					{
						if(a == -1) a = i;
						else b = i;
					}
				}
				if(ask(idx, {a})) cur = cur->child[a];
				else cur = cur->child[b];
			}
		}
	}
	printf("C %d\n", cur->res+1);
	fflush(stdout);
}