#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct ppnode {
	int dep = 0, leaf = 0;
	ppnode* child[27] = {NULL};

};

typedef ppnode* pnode;

vector<pair<int, int>> ops;

void insert(pnode& root, string& S, int idx)
{
	if(idx == int(S.size()))
	{
		root->leaf = 1;
		return;
	}
	int c = int(S[idx]-'a');
	if(!root->child[c])
	{
		root->child[c] = new ppnode();
	}
	insert(root->child[c], S, idx+1);
	root->dep = max(root->dep, 1+root->child[c]->dep);
}

void dfs(pnode& root)
{
	pair<int, int> heavy = {-1, -1};
	for(int i = 0;i < 27;i++)
	{
		if(root->child[i]) heavy = max(heavy, {root->child[i]->dep, i});
	}

	if(root->leaf) ops.push_back({2, -1});

	for(int i = 0;i < 27;i++)
	{
		if(heavy.second != i && root->child[i])
		{
			ops.push_back({0, i});
			dfs(root->child[i]);
			ops.push_back({1, -1});
		}
	}
	if(heavy.second != -1)
	{
		ops.push_back({0, heavy.second});
		dfs(root->child[heavy.second]);
		ops.push_back({1, -1});
	}
}

int main(void)
{
	int n;
	string S;
	pnode root = new ppnode();
	scanf("%d", &n);
	for(int i = 0;i < n;i++)
	{
		cin >> S;
		insert(root, S, 0);
	}

	dfs(root);

	while(!ops.empty() && ops.back().first == 1) ops.resize(int(ops.size())-1); 

	printf("%d\n", int(ops.size()));
	for(auto it: ops)
	{
		if(it.first == 0) printf("%c\n", char(it.second+'a'));
		else if(it.first == 1) printf("-\n");
		else printf("P\n");
	}
}